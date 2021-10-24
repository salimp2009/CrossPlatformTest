#pragma once

#include "CoroutinesHeader.hpp"


#if _GLIBCXX_RANGES || ! defined(__clang__)

namespace AsyncStreamParserV2
{

	constinit static std::byte ESC{ 'H' };
	constinit static std::byte SOF{ 0x10 };

	std::byte operator""_B(char c)
	{
		return static_cast<std::byte>(c);
	}

	std::byte operator""_B(unsigned long long c)
	{
		return static_cast<std::byte>(c);
	}

	template<typename T, typename G, bool InitialSuspend=true>
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
	};

	template<typename PT>
	struct iterator
	{
		using coro_handle = std::coroutine_handle<PT>;

		coro_handle mCoroHd1{ nullptr };
		bool		mDone{ true };

		using RetType = decltype(mCoroHd1.promise().mValue);

		void resume()
		{
			mCoroHd1.resume();
			mDone = mCoroHd1.done();
		}

		iterator() = default;

		iterator(coro_handle hco) : mCoroHd1{ hco } { resume(); }

		iterator& operator++()
		{
			resume();
			return *this;
		}

		bool operator==(const iterator& other) const { return mDone == other.mDone; }

		const RetType& operator*()  const& { return mCoroHd1.promise().mValue; }
		const RetType* operator->() const { return &(operator*()); }
	};

	template<typename T, bool InitialSuspend = true>
	struct generator
	{
		using promise_type = promise_type_base<T, generator, InitialSuspend>;
		using PromiseTypeHandle = std::coroutine_handle<promise_type>;
		using Iterator = iterator<promise_type>;

		Iterator begin()	{ return { mcoroHandle }; }
		Iterator end()		{ return {}; }

		generator(const generator&) = delete;
		generator(generator&& other) : mcoroHandle{std::exchange(other.mcoroHandle, nullptr)} {}
		~generator()
		{
			if (mcoroHandle)
			{
				mcoroHandle.destroy();
			}
		}

		T operator()()
		{
			T temp{};
			// return the value and leaves the mValue in a clear state
			std::swap(temp, mcoroHandle.promise().mValue);
			return temp;
		}

	private:
		friend promise_type;
		explicit generator(promise_type* p) : mcoroHandle{PromiseTypeHandle::from_promise(*p)} {}
	protected:
		PromiseTypeHandle mcoroHandle;

	};

	// stream reader will be awaiter
	class DataStreamReader
	{
	public:
		DataStreamReader() = default;

		// deleting move assignment diable copy and move operations
		DataStreamReader& operator=(DataStreamReader&&) noexcept = delete;

		struct Awaiter
		{
			Awaiter& operator=(Awaiter&&) noexcept = delete;
			Awaiter(DataStreamReader& event) noexcept : mEvent{event} 
			{
				mEvent.mAwaiter = this;
			}

			bool await_ready() const noexcept { return mEvent.mData.has_value(); }
			
			void await_suspend(std::coroutine_handle<> handle) noexcept { mCoroHandle = handle; }
			
			std::byte await_resume() noexcept
			{
				assert(mEvent.mData.has_value());
				return *(std::exchange(mEvent.mData, std::nullopt));
			}

			void resume() { mCoroHandle.resume(); }

		private:
			DataStreamReader& mEvent;
			std::coroutine_handle<> mCoroHandle;
		};

		//making DataStreamReader an awaiter; before we used await_transform for the promise type
		auto operator co_await() noexcept { return Awaiter{ *this }; }

		void set(std::byte b)
		{
			mData.emplace(b);
			if (mAwaiter)
			{
				mAwaiter->resume();
			}
		}

	private:
		friend struct Awaiter;
		Awaiter* mAwaiter;
		std::optional<std::byte> mData;
	};

	// the false parameter determines to suspend or run till the first co_xxx statement
	using FSM = generator<std::string, false>;

	FSM Parse(DataStreamReader& stream)
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
					continue; // not a start sequence 
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

	generator<std::byte> send(std::vector<std::byte> fakeBytes)
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


	inline void AysncStreamParserV2_Corotn()
	{
		std::printf("\n--AsyncByteStreamParserV2--\n");
		std::vector<std::byte> fakeBytes1{
		0x70_B, 0x24_B, ESC, SOF, ESC,
		'H'_B, 'e'_B, 'l'_B, 'l'_B, 'o'_B,
		ESC, SOF, 0x7_B, ESC, SOF };

		// simulate first network connection but it will be disconnected first 
		auto stream1 = send(std::move(fakeBytes1));
		// create a reader
		auto dataReader = DataStreamReader();
		
		// datareader will get the data from stream and parser will handle that 
		auto parser = Parse(dataReader);

		for (const auto& data : stream1)
		{
			dataReader.set(data);

			if (auto result = parser(); result.length())
			{
				HandleFrame(result);
			}
		}

		// reconnect to netwrok get the rest of the data; 
		// Parser coroutine is suspended when disconneand will know where it was 

		std::vector<std::byte>fakeBytes2{ 'W'_B, 'o'_B, 'r'_B, 'l'_B, 'd'_B, ESC, SOF, 0x99_B };
		auto stream2 = send(std::move(fakeBytes2));
		
		for (const auto& data : stream2)
		{
			dataReader.set(data);

			if (auto result = parser(); result.length())
			{
				HandleFrame(result);
			}
		}

		std::puts("");
	}

}// end of namespace AsyncStreamParserV2

#endif