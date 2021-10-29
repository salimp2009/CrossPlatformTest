#pragma once
#include "RangesHeaders.hpp"



//std::ranges::view is a concept in rangers header 
template<std::ranges::view R>
class custom_take_view :public std::ranges::view_interface<custom_take_view<R>>
{
private:
	R mBase{};
	std::ranges::range_difference_t<R> mCount{};

public:
	custom_take_view() = default;
	constexpr custom_take_view(R base, std::ranges::range_difference_t<R> count): mBase{std::move(base)}, mCount{count} { }

	// view interface members; 
	// TODO; check if we have to USE const R& return type for the const& version
	constexpr R base() const&	{ return mBase; }
	constexpr R base() &&		{ return std::move(mBase); }
	
	constexpr auto begin()	{ return std::ranges::begin(mBase); }
	constexpr auto end()	{ return std::ranges::next(std::ranges::begin(mBase), mCount); }
};

// template argument deduction guide is required
template<std::ranges::range R>
custom_take_view(R&&, std::ranges::range_difference_t<R>)->custom_take_view <std::ranges::views::all_t<R>>;

// Range Adaptor for custom_take_view; this needed to turn a range into a view (e.g: custom_take_view)
// this is needed to pipelining by using an overload operator |

namespace details
{
	// this is a helper to create custom_take_range-adaptor; will be called by the adaptor; see below 
	// could be implemented as a lambda as well
	template<std::integral T>
	struct custom_take_range_adaptor_closure
	{
		T mCount;
		constexpr custom_take_range_adaptor_closure(T count) : mCount{ count } {}

		// To allow this to be called with a range
		template<std::ranges::viewable_range R>
		constexpr auto operator()(R&& r) const
		{
			return custom_take_view(std::forward<R>(r), mCount);
		}
	};

	struct custom_take_range_adaptor
	{
		template<typename... Args>
		constexpr auto operator()(Args&&... args) 
		{
			if constexpr(sizeof...(Args) == 1)
			{
				return custom_take_range_adaptor_closure{ args... };
			}
			else
			{
				return custom_take_view{ std::forward<Args>(args)...};
			}
		}
	};

	template<std::ranges::viewable_range R, std::invocable<R> Adaptor>
	constexpr auto operator | (R&& r, const Adaptor adaptor)
	{
		return adaptor(std::forward<R>(r));
	}

} // end of namespace details

namespace view
{
	// if constexpr is used below then range adaptor operator() has to be const as well !
	// check if constexpr is beneficial ; which it should be
	inline details::custom_take_range_adaptor custom_take;

}
