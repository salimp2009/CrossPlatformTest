#pragma once

#include "CoroutinesHeader.hpp"

// operator new can be a template function; but return type must void, first paam is size and must have 2 more params
// https://en.cppreference.com/w/cpp/memory/new/operator_new


namespace CustomAlloc
{	
	struct arena
	{
		void* Allocate(std::size_t size) noexcept;
		void DeAllocate(void* p, std::size_t size) noexcept;

		static arena* GetFromPtr(void* ptr, std::size_t size);
	};

	void* arena::Allocate(std::size_t size) noexcept
	{
		auto objectsize = size;
		/* add the size of arena pointer so we can get the address of ptr
		   original size will be for data and added size for arena* ptr to be able to pass arnd */
		size += sizeof(arena*);

		// allocate memory
		char* ptr = new char[size];

		/* return the address of pointer ; Check if std::bit_cast can be used  https://en.cppreference.com/w/cpp/numeric/bit_cast */
		[[maybe_unused]] arena* aa = reinterpret_cast<arena*>(ptr + objectsize);

		/* every invocation will get a seperate arena/memory location*/
		aa = this;

		/* Not sure why this is needed ; for comparision of a & bthis is original location of pointer ; not the */
		arena* bb = reinterpret_cast<arena*>(ptr + objectsize);

		std::printf("custom allocate: object size: %zu, ptr: %p, address of instance: %p, address of the pointer(ptr+objectsize): %p\n", objectsize, ptr, this, bb);

		return ptr;
	}

	arena* arena::GetFromPtr(void* ptr, std::size_t size)
	{
		// this is to access the objects memory ptr and then call the right memory location to delete; used with Delete
		return reinterpret_cast<arena*>(static_cast<char*>(ptr) + size);
	}

	void arena::DeAllocate(void* ptr, std::size_t size) noexcept
	{
		std::printf("custom deallocation: size: %zu, from ptr: %p, this: %p\n", size, ptr, this);
		return delete[] static_cast<char*>(ptr);
	}

	template<typename T, typename G, bool InitialSuspend = true>
	struct promise_type_base
	{
		T mValue;

		auto yield_value(T value)
		{
			mValue = value;
			return std::suspend_always{};
		}

		auto initial_suspend()
		{
			if constexpr (InitialSuspend)
			{
				return std::suspend_always{};
			}
			else
			{
				return std::suspend_never{};
			}
		}

		auto final_suspend() noexcept { return std::suspend_always{}; }
		G get_return_object() { return G{ this }; }

		void unhandled_exception() { std::terminate(); }
		void return_void() {}

		template<typename... TArgs>
		[[nodiscard]] void* operator new(std::size_t size, arena& arenaPool, TArgs&&...) noexcept
		{
			std::printf("promise: call Arena for %zu bytes \n", size);
			return arenaPool.Allocate(size);
		}

		void operator delete(void* ptr, std::size_t size)
		{
			std::puts("promise:call DeAllocate!\n");
			arena::GetFromPtr(ptr, size)->DeAllocate(ptr, size);
		}

		static auto get_return_object_on_allocation_failure() { return G{ nullptr }; }
	};


	template<typename PT>
	struct iterator
	{
		using coro_handle = std::coroutine_handle<PT>;
		coro_handle mCoroHd1{};

		using RetType = decltype(mCoroHd1.promise().mValue);

		void resume() { mCoroHd1.resume(); }

		iterator() = default;
		iterator(coro_handle hco) : mCoroHd1{ hco } { resume(); }

		void operator++() { resume(); }

		bool operator==(const iterator&) const { return mCoroHd1.done(); }
		
		const RetType& operator*()  const& { return mCoroHd1.promise().mValue; }
		const RetType* operator->() const { return &(operator*()); }
	};


	template<typename T, bool InitialSuspend = true>
	struct generator
	{
		using promise_type = promise_type_base<T, generator, InitialSuspend>;
		using PromiseTypeHandle = std::coroutine_handle<promise_type>;
		using Iterator = iterator<promise_type>;

		Iterator begin() { return mCoroHd1; }
		Iterator end() { return {}; }

		generator(const generator&) = delete;
		generator(generator&& rhs) : mCoroHd1{ std::exchange(rhs.mCoroHd1, nullptr) } {}

		~generator() { if (mCoroHd1) mCoroHd1.destroy(); }

		T operator()()
		{
			T tmp{};
			// use swap for a potential move and defined / cleared state
			std::swap(tmp, mCoroHd1.promise().mValue);
			return tmp;
		}

	private:
		friend promise_type;
		explicit generator(promise_type* p) : mCoroHd1{ PromiseTypeHandle::from_promise(*p) } {}
	protected:
		PromiseTypeHandle mCoroHd1;
	};


	class DataStreamReader
	{
	public:
		DataStreamReader() = default;

		// disabling the move assignment operator ; this also disables the default copy operations
		DataStreamReader& operator=(DataStreamReader&&) noexcept = delete;

		struct Awaiter
		{
			Awaiter& operator=(Awaiter&&)    noexcept = delete;
			Awaiter(DataStreamReader& event) noexcept : mEvent{ event }
			{
				mEvent.mAwaiter = this;
			}

			bool await_ready() const noexcept
			{
				return mEvent.mData.has_value();
			}

			void await_suspend(std::coroutine_handle<> coroHd1) noexcept
			{
				mCoroHd1 = coroHd1;
			}

			std::byte await_resume() noexcept
			{
				//std::printf("Awaiter:await resume!\n");
				assert(mEvent.mData.has_value());
				return *std::exchange(mEvent.mData, std::nullopt);
			}

			void resume() { mCoroHd1.resume(); }

		private:
			DataStreamReader& mEvent;
			std::coroutine_handle<> mCoroHd1{};
		};

		auto operator co_await() noexcept { return Awaiter{ *this }; }

		void set(std::byte data)
		{
			mData.emplace(data);
			if (mAwaiter)
			{
				mAwaiter->resume();
			}
		}

	private:
		friend struct Awaiter;
		Awaiter* mAwaiter{};
		std::optional<std::byte> mData{};
	};

	using FSM = generator<std::string, false>;

	static const std::byte ESC{ 'H' };
	static const std::byte SOF{ 0x10 };


	// the stream is passed by reference into the parse; 
	// need to make sure lifetime of stream is longer than Parse
	FSM Parse(arena& ar, DataStreamReader& stream)
	{
		while (true)
		{
			// wait for the stream
			std::byte bb = co_await stream;
			std::string frame{};

			if (ESC == bb)
			{
				bb = co_await stream;
				if (SOF != bb)
				{
					continue; // not a start sequence ; this will skip the while loop goback  to outer while loop
				}

				// try to capture the full frame
				while (true)
				{
					bb = co_await stream;
					if (ESC == bb)
					{
						// skip this byte look at the next one!
						bb = co_await stream;
						if (SOF == bb)
						{
							// if end of frame then return the result
							co_yield frame;
							break;
						}
						else if (ESC != bb)
						{
							// out of sync !!!
							break;
						}
					}

					frame += static_cast<char>(bb);
				}
			}
		}
	}

	/* std::vector is by copy on purpose because of lifetime issues; as coroutine may live longer that original data
		but the call site can use std::move ; in case you are sure the container lives longer than the coroutine than pass by const&
		; e.g. we are simulation parsing signals on TCP then those might not live longer you pass by copy & move semantics will be applied by compiler
	*/
	// this simulates a network that sends signal until it is disconnected; coroutine send the value of signal into promise_type_base
	generator<std::byte> send(arena& ar, std::vector<std::byte> fakeBytes)
	{
		for (const auto& signal : fakeBytes)
		{
			co_yield signal;
		}
	}

	void HandleFrame(std::string_view frame)
	{
		std::printf("%s \n", frame.data());
	}

} // end of namespace CustomAlloc


inline void CustomAllocator_Corotn()
{
	std::printf("\n--CustomAllocator_Corotn--\n");
	std::vector<std::byte> network1{ 0x70_B, 0x24_B, ESC, SOF, ESC,'H'_B, 'e'_B, 'l'_B, 'l'_B, 'o'_B,ESC, SOF, 0x7_B, ESC, SOF };

	// simulate another  network connection
	std::vector<std::byte> network2{ 'W'_B, 'o'_B, 'r'_B, 'l'_B, 'd'_B, ESC, SOF, 0x99_B };

	CustomAlloc::arena a1{};
	CustomAlloc::arena a2{};

	auto stream1 = CustomAlloc::send(a1, std::move(network1));
	CustomAlloc::DataStreamReader dataReader{};

	auto parseStreamData = CustomAlloc::Parse(a2, dataReader);

	for (const auto& data : stream1)
	{
		dataReader.set(data);

		if (auto result = parseStreamData(); result.length())
		{
			CustomAlloc::HandleFrame(result);
		}
	}

	auto stream2 = CustomAlloc::send(a1, std::move(network2));
	for (const auto& data : stream2)
	{
		dataReader.set(data);

		if (auto result = parseStreamData(); result.length())
		{
			CustomAlloc::HandleFrame(result);
		}
	}
}
