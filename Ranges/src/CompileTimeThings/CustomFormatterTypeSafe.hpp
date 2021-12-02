#include "RangesHeaders.hpp"
#include "ConstexprString.hpp"

template<typename T, class... Args>
constexpr void Formatter(string& buffer, std::string_view v, const T& t, const Args&... args)
{

}


template<typename... Args>
struct basic_format_string
{
	std::string_view str;  

	// Alternative is to use std::is_constructible_v to allow explicit convertible types
	// std::is_convertible_t is only for implicitly covertible types
	template<class T>
	requires std::is_convertible_v<T&, std::string_view>
	consteval basic_format_string(const T& s): str{s} 
	{
		string out{};
		Formatter(out, str, Args{}...);
	}
};



template<typename... Args>
using format_string = basic_format_string<std::type_identity_t<Args>...>;


template<class... Args>
string  format(format_string<Args...> fmt, const Args&... args);