#include "RangesHeaders.hpp"

void NamedTupple_Test();

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
	//	std::copy_n(str, N+1, data);
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
fixed_string(const char(&)[N])->fixed_string<char, N>;




