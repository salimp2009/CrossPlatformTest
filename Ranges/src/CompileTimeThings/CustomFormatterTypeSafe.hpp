#include "RangesHeaders.hpp"
#include "ConstexprString.hpp"
#include <charconv>

constexpr string itoa(int num, int base = 10)
{
	if (num == 0) { return { '0' }; }

	string value{};

	while (num > 0)
	{
		const char sub = static_cast<char>(num % base);
		num /= base;

		const char v = sub + '0';
		value.append(&v, 1);
	}
	string ret{};
	std::string_view rv{ value };

	// TODO ; check if creating a temporary string_view and copying it to another string and then
	// return that string that copies data from it !! Sounds OK since we copied before it is destroyed
	for (auto i{ rv.size() }; i > 0; --i)
	{
		ret.append(rv.substr(i - 1, 1));
	}

	return ret;
}

template<typename T, class... Args>
constexpr void Formatter(string& buffer, std::string_view v, const T& t, const Args&... args)
{
	using PT = std::remove_cv_t<T>;

	if constexpr(std::is_same_v<int, PT>)
	{
		if ('d' != v[0]) { throw int{ 3 }; }
		buffer.append(itoa(t));
	}
	else if constexpr (std::is_convertible_v<PT, std::string_view>)
	{
		if ('s' != v[0]) { throw int{ 4 }; }
		buffer.append(t);
	}
	else
	{
		throw int{ 6 };
	}
	
	v.remove_prefix(1);
	if constexpr (sizeof...(Args) > 0)
	{
		Formatter<Args...>(buffer, v, args...);
		// this works too
		//Formatter(buffer, v, args...);
	}
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


// std::type_identity<T> creates the member typedef type that names T
// https://en.cppreference.com/w/cpp/types/type_identity
// std::type_identy lets us to call basic_format_string with the type of the first of Args
// the remainder of Args will be converted to type of the first one as long as they can be converted
template<typename... Args>
using format_string = basic_format_string<std::type_identity_t<Args>...>;

// this will give compile error since the type of Args are not same
//using format_string = basic_format_string <Args... > ;

template<class... Args>
string  format(format_string<Args...> fmt, const Args&... args)
{
	string out{};
	Formatter(out, fmt.str, args...);

	return out;
}