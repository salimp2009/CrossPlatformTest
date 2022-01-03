#include "ConceptsPCH.hpp"
#include <experimental/type_traits>

//template<typename T>



// the signatures of the overloaded function should match
// otherwise the more constrained version for floating point will not be selected
template<std::floating_point T, ContainerType<T> Coll>
void addValue(Coll& cont, T value)
{
	cont.push_back(value);
}

// if the function signatures needs to be different than the T should have contraint Not to Have Floating Point
template<typename T, ContainerType<T> Coll>
requires (!std::floating_point<T>)
void addValue(Coll& cont, T&& value)
{
	cont.push_back(std::forward<T>(value));
}


