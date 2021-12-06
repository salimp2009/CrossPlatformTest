#include "RangesHeaders.hpp"

void MetaProgramming_Test();

// included in C++20
template<typename T> 
struct TypeIdentity { using type = T; };

template<typename T>
using TypeIdentity_t = typename TypeIdentity<T>::type;


//primary template that handles the case there is no type member 
template<class, class = void>
struct HasTypeMember: std::false_type{};

template<class T>
struct HasTypeMember<T, std::void_t<typename T::type>> : std::true_type{};

// experimental; trying to use type_identiy to add member to struct A called type which is the type of
// Args passed in struct A; e.g : A<int>
template<typename... Args>
struct A {};

template<typename... Args>
using typeA =A<TypeIdentity_t<Args>...>;


template<typename T, typename=void>
struct Add_Lvalue_reference: TypeIdentity<T>{ };

template<typename T>
struct Add_Lvalue_reference<T, std::void_t<T&>>: TypeIdentity<T&>{ };

template<typename T>
using Add_Lvalue_reference_t = typename Add_Lvalue_reference<T>::type;

// to avoid bugs in std::void_t ; alternative implementation 
template<typename T, typename...>
struct First : TypeIdentity<T> {};

//alias template
template<class...Ts>
using Void_t = typename First<void, Ts...>::type;

template<typename TargetT, typename... Ts>
struct recursive_IsInPack : std::false_type {};

template<typename TargetT, typename... RestTs>
struct recursive_IsInPack<TargetT, TargetT, RestTs...>: std::true_type{};

template<typename TargetT, typename TFirst, typename... RestTs>
struct recursive_IsInPack<TargetT, TFirst, RestTs...>: recursive_IsInPack<TargetT, RestTs...> { };

