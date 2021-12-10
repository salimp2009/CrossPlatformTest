#include "RangesHeaders.hpp"

void NamedTupple_Test();
void NamedTupple_Test2();


template<typename TChar, std::size_t N>
struct fixed_string
{
	TChar data[N]{};
	static constexpr std::size_t size = N;

	constexpr explicit(false) fixed_string(const TChar(&str)[N])
	{
		std::copy_n(str, N, data);
	}

	// Used in the original example ; the above method is nicer to me :)
	// if you use both then compiler error for ambigiues overloading
	//constexpr explicit(false) fixed_string(const TChar* str)
	//{
	//	std::copy_n(str, N, data);
	//}

	constexpr explicit(false) operator std:: string_view() const
	{
		return { data, N-1 };
	}

	//constexpr explicit(false) operator const auto*() const
	//{
	//	return data;
	//}
};

template<std::size_t N>
fixed_string(const char*)->fixed_string<char, N>;

template<fixed_string Name>
constexpr auto operator""_t()
{
	return Name;
}


template<fixed_string Name, class TValue>
struct arg
{
	static constexpr auto name = Name;
	TValue value{};
	
	template<typename T>
	[[nodiscard]] constexpr auto operator=(const T& val) const
	{
		return arg<Name, T>{.value = val};
	}

	// added this to get rid of some of the errors in the constexpr test but it does not help since std::any in not constexpr 
	constexpr ~arg() = default;
};



// this is to test during implementation ; will be revised afterwards
template<fixed_string Name>
constexpr auto operator""_ts()
{
	return arg<Name, std::any>{};
}

template<typename... Ts>
struct namedtuple : Ts...
{
	// C++17 added this ; not used in the original implementation ??
	//using Ts::operator()...;
	constexpr explicit(true) namedtuple(Ts... ts): Ts{ts}... {}


	template<fixed_string Name, typename TValue>
	[[nodiscard]] constexpr decltype(auto) get(arg<Name, TValue>&& t)
	{
		return (t.value);
	}


	template<class T>
	[[nodiscard]] constexpr auto operator[](T) ->decltype(get<T::name>(*this)) 
	{
		return get<T::name>(*this);
	}
	
	//template<class T>
	//[[nodiscard]] constexpr const auto operator[](T) const& ->decltype(get<T::name>(*this)) 
	//{
	//	return get<T::name>(*this);
	//}

};

// as of C++20 this might not be needed 
template<typename...Ts>
namedtuple(Ts... ts)->namedtuple<Ts...>;









