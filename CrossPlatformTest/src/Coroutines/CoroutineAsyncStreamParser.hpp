#pragma once

#include "CoroutinesHeader.hpp"


#if _GLIBCXX_RANGES || ! defined(__clang__)

constinit static std::byte ESC{ 'H'};
constinit static std::byte SOF{ 0x10 };

std::byte operator""_B(char c)
{
	return static_cast<std::byte>(c);
}

std::byte operator""_B(unsigned long long c)
{
	return static_cast<std::byte>(c);
}

template<typename T, typename G, typename... Bases>
struct promise_type_base : public Bases...
{
	T mValue;

	G get_return_object() { return G{ this }; }

	auto initial_suspend()			{ return std::suspend_always{}; }
	auto final_suspend() noexcept	{ return std::suspend_always{}; }

	auto yield_value(T value)
	{
		mValue = value;
		return std::suspend_always{};
	}

	void return_void() {}
	void unhandled_exception() { std::terminate(); }
};

template<typename T>
struct awaitable_promise_type_base
{
	std::optional<T> mRecentSignal;

	struct awaiter
	{
		std::optional<T>& mRecentSignal;

		bool await_ready() const noexcept { return mRecentSignal.has_value(); }
		void await_suspend(std::coroutine_handle<>) { }

		T await_resume()
		{
			assert(mRecentSignal.has_value());
			auto tmp = *mRecentSignal;
			mRecentSignal.reset();
			return tmp;
		}
	};

	[[nodiscard]] awaiter await_transform(T) { return awaiter{ mRecentSignal }; }

};

template<typename T, typename U>
struct [[nodiscard]] async_generator
{
	using promise_type = promise_type_base<T, async_generator, awaitable_promise_type_base<U> >;
	using PromiseTypeHandle = std::coroutine_handle<promise_type>;

	// this gets the value
	T operator()()
	{
		// move clears the value of promise but leave it undefined state
		auto tmp{ std::move(mCoroHd1.promise().mValue) };
		// set the promise to a defined state ; clear() is std::string member function used HasClear concept to make sure it exists !
		mCoroHd1.promise().mValue.clear();

		return tmp;
	}

	// this sender for signal 
	void SendSignal(U signal)
	{
		mCoroHd1.promise().mRecentSignal = signal;
		if (not mCoroHd1.done()) { mCoroHd1.resume(); }
	}

	async_generator(const async_generator&) = delete;
	async_generator(async_generator&& rhs) : mCoroHd1{ std::exchange(rhs.mCoroHd1, nullptr) } {}

	~async_generator() { if (mCoroHd1) mCoroHd1.destroy(); }

private:
	friend promise_type;
	explicit async_generator(promise_type* p) : mCoroHd1(PromiseTypeHandle::from_promise(*p)) {}

	PromiseTypeHandle mCoroHd1;
};

using FSM = async_generator<std::string, std::byte>;

FSM Parse()
{
	while (true)
	{
		std::byte bb = co_await std::byte{};

		std::string frame{};

		if (ESC == bb)
		{
			bb = co_await std::byte{};
			if (SOF != bb)
			{
				continue; // not a start sequence 
			}

			while (true)  // try to capture the full frame
			{
				bb = co_await std::byte{};
				if (ESC == bb)
				{
					// skip this byte look at the next one!
					bb = co_await std::byte{};
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

template<typename PT>
struct iterator
{
	using coroHandle = std::coroutine_handle<PT>;

	coroHandle mCoroHandle{ nullptr };
	bool mDone = true;

	using RetType = decltype(mCoroHandle.promise().mValue);

	iterator() = default;
	iterator(coroHandle h) : mCoroHandle{ h } { resume(); }
	
	void resume()
	{
		mCoroHandle.resume();
		mDone = mCoroHandle.done();
	}

	iterator& operator++()
	{
		resume();
		return *this;
	}

	bool operator==(const iterator& other) const { return mDone == other.mDone; }
	// Alternative for operator== ; TEST if it works !!
	//bool operator==(const iterator&) const = default;

	const RetType& operator*()	const { return mCoroHandle.promise().mValue; }
	const RetType* operator->()	const { return &(operator*()); }
	
};


template<typename T>
struct generator
{
	using promise_type			= promise_type_base<T, generator>;
	using PromiseTypeHandle		= std::coroutine_handle<promise_type>;
	using iteratorType			= iterator<promise_type>;

	iteratorType begin()	{ return mCoroHandle; }
	iteratorType end()		{ return {}; }

	generator(const generator&) = delete;
	generator(generator&& rhs) : mCoroHandle{ std::exchange(rhs.mCoroHandle, nullptr)} {}
	~generator() { if (mCoroHandle) mCoroHandle.destroy(); }

private:
	friend promise_type;
	explicit generator(promise_type* p) : mCoroHandle{ PromiseTypeHandle::from_promise(*p) } {}
	PromiseTypeHandle mCoroHandle;
};


inline generator<std::byte> send(std::vector<std::byte> fakeBytes)
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

inline void ProcessStream(generator<std::byte>& stream, FSM& parse)
{
	for (const auto& signal : stream)
	{
		parse.SendSignal(signal); // send signal for the waiting Parse coroutine
	}

	if (const auto& result = parse(); result.length()) 
	{
		HandleFrame(result); 
	}
}

inline void CoroutineAsyncStreamParser()
{
	std::printf("\n----CoroutineAsyncStreamParser---\n");

	// simulate networks connection
	std::vector<std::byte> fakeBytes1{
	0x70_B, 0x24_B, ESC, SOF, ESC,
	'H'_B, 'e'_B, 'l'_B, 'l'_B, 'o'_B,
	ESC, SOF, 0x7_B, ESC, SOF };

	auto stream1 = send(std::move(fakeBytes1));

	auto parser = Parse();

	ProcessStream(stream1, parser);

	//simulate another  network connection
	std::vector<std::byte> fakeBytes2{
	'W'_B, 'o'_B, 'r'_B, 'l'_B, 'd'_B, ESC, SOF, 0x99_B };

	auto stream2 = send(std::move(fakeBytes2));
	// create a coroutine and store the promise in the coroutine_handle
	// Process the bytes
	ProcessStream(stream2, parser);

}

#endif