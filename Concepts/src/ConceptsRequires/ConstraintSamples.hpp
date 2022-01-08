#include "ConceptsPCH.hpp"


// try to avoid ad-hoc constraint; use concepts 
// order of constraints dont matter

template<typename T>
requires (sizeof(T) > 4) 
		&& requires { typename T::value_type; }
		&& std::contiguous_iterator<typename T::iterator>
void SampleAdHoc(T val)
{
	std::puts("SampleAdHoc Function 1");
}

template<typename T, std::size_t Sz>
requires (Sz>0)
constexpr void ArraySizeCheck()
{
	std::puts("ArraySizeCheck");
}





