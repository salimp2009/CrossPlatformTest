#include "ConceptsPCH.hpp"


// way to overlaod function for different functionality
// not a preferable way; use std::enable_if or std::void_t
template<typename Coll, typename T>
auto addOLDWay(Coll& cont, T&& value) -> decltype(cont.push_back(value))
{
	return cont.push_back(value);
}

template<typename Coll, typename T>
auto addOLDWay(Coll& cont, T&& value) -> decltype(cont.insert(value))
{
	return cont.insert(value);
}


template<typename Coll, typename T, typename = std::enable_if_t<!std::floating_point<T>>>
auto addOLDWay2(Coll& cont, T&& value)
{
	cont.push_back(value);
}

template<typename Coll, typename T, std::void_t<typename std::is_integral<T>::type>* =nullptr>
auto addOLDWay3(Coll& cont, T&& value)
{
	cont.push_back(value);
}



