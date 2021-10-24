#pragma once

#include <coroutine>
#include <memory>
#include <cstdio>




#if _GLIBCXX_RANGES ||  !defined(__clang__)

template<typename T>
struct EagerFuture
{
	std::shared_ptr<T> value;
	EagerFuture(std::shared_ptr<T> p) : value(p) { std::puts("	EagerFuture::Eager Future Constructor"); }
	~EagerFuture() { std::puts("	EagerFuture::Eager Future Destructor"); }
	T get()
	{
		std::puts("");
		return (*value);
	}

	struct promise_type
	{
		std::shared_ptr<T> ptr = std::make_shared<T>();
		~promise_type() = default;
		EagerFuture<T> get_return_object()
		{
			return ptr;
		}

		void return_value(T v) { *ptr = v; } /* since this is eager; not suspending!*/

		std::suspend_never initial_suspend() { return {}; }
		std::suspend_never final_suspend() noexcept { return {}; }

		void unhandled_exception() { std::exit(1); }
	};
};

EagerFuture<int> createFuture(int val)
{
	co_return val;
}

#endif
