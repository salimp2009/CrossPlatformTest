#include "RangesHeaders.hpp"

template<typename T>
static constexpr std::string_view nameof()
{
	return std::string_view( __PRETTY_FUNCTION__ );
	
#if defined(_MSC_VER) and not defined(__clang__)
		return { &__FUNCSIG__[120], sizeof(__FUNCSIG__) - 128 };
	#elif defined(__clang_analyzer__)
		return { &__PRETTY_FUNCTION__[57], sizeof(__PRETTY_FUNCTION__) - 59 };
	#elif defined(__clang__) and (__clang_major__ >= 12) and not defined(__APPLE__)
		return { &__PRETTY_FUNCTION__[34], sizeof(__PRETTY_FUNCTION__) - 36 };
	#elif defined(__clang__)
		return { &__PRETTY_FUNCTION__[70], sizeof(__PRETTY_FUNCTION__) - 72 };
	#elif defined(__GNUC__) || defined (__GNUG__)
		return { __PRETTY_FUNCTION__ };
		// this is from Kris Jusiak s tuple implementation !!
		//return { &__PRETTY_FUNCTION__[85], sizeof(__PRETTY_FUNCTION__) - 136 };
	#endif
}

template<typename... Ts>
struct PackImpl
{
	// Fn is a function pointer tht return a string_view and takes no arguments
	using Fn = std::string_view(*)();

	static constexpr Fn ids[sizeof...(Ts)] = { nameof<Ts>... };
	static constexpr bool contains(Fn target)
	{
		for (auto&& id : ids)
		{
			if (id == target) 
			{ 
				return true; 
			}
		}

		return false;
	}
};