#include "RangesHeaders.hpp"
#include "ConstexprString.hpp"
#include <charconv>

constexpr string itoa(int num, int base = 10)
{
	if (num == 0) { return { '0' }; }

	while (num > 0)
	{
		const char sub = static_cast<char>(num % base);
		num /= base;

		const char v = sub + '0';
		
		return {};
	}

}

template<typename T, class... Args>
constexpr void Formatter(string& buffer, std::string_view v, const T& t, const Args&... args)
{
	using PT = std::remove_cv_t<T>;

	if constexpr(std::is_same_v<int, PT>)
	{
		if ('d' != v[0]) { throw int{ 3 }; }
	}
	buffer.append(itoa(t));
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
string  format(format_string<Args...> fmt, const Args&... args)
{
	string out{};
	Formatter(out, fmt.str, args...);

	return out;
}