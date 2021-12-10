#include "RangesHeaders.hpp"

void MetaProgramming_Test();
void MetaProgLinearSearch();

// included in C++20 as std::type_identity
template<typename T>
struct TypeIdentity { using type = T; };

template<typename T>
using TypeIdentity_t = typename TypeIdentity<T>::type;

// to avoid bugs in std::void_t ; alternative implementation 
template<typename T, typename...>
struct First : TypeIdentity<T> {};

//alias template
template<class...Ts>
using Void_t = typename First<void, Ts...>::type;

// Example helpers to test custom Void_t implementation
struct One { using x = int; };
struct Two { using y = int; };

template<typename T, Void_t<typename T::x>* = nullptr>
void func() { static_assert(std::is_same_v<T, decltype(One())>); }

template<typename T, Void_t<typename T::y>* = nullptr>
void func() { static_assert(std::is_same_v<T, decltype(Two())>);  }


// This does not compile ; it is C++ internal bug; therefore use custom Void_t
//template<typename T, std::void_t<typename T::x>* = nullptr>
//void func2() { }
//
//template<typename T, std::void_t<typename T::y>* = nullptr>
//void func2() { }

// Second Example where std::void_t was supposed to fail due to C++ standart internal bug
// But it does not; !!!!
template<typename T, typename U> struct BartSimpson;
template<typename T, typename U, typename = void> struct BartFart {} ;

// TODO; check this example std::void_t was supposed to fail but it compiles
template<typename T, typename U> 
//struct BartFart<T, U, std::void_t<decltype(BartSimpson<T, U>::value)>> { };
struct BartFart<T, U, Void_t<decltype(BartSimpson<T, U>::value)>> { };

// TODO; check this example std::void_t was supposed to fail but it compiles
template<typename T, typename U> 
//struct BartFart<T, U, std::void_t<decltype(T::zz), decltype(U::yy)>> { };
struct BartFart<T, U, Void_t<decltype(T::zz), decltype(U::yy) >> { };

struct TType { int zz{}; };
struct UType { float yy{}; };

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

template<typename TargetT, typename... Ts>
struct recursive_IsInPack : std::false_type {};

template<typename TargetT, typename... RestTs>
struct recursive_IsInPack<TargetT, TargetT, RestTs...>: std::true_type{ };

template<typename TargetT, typename TFirst, typename... RestTs>
struct recursive_IsInPack<TargetT, TFirst, RestTs...>: recursive_IsInPack<TargetT, RestTs...> { };

// TODO; test this 
template<typename... Args>
//using recursive_pack = recursive_IsInPack<std::type_identity_t<Args>...>;
using recursive_pack = recursive_IsInPack<TypeIdentity_t<Args>...>;

template<typename... Args>
consteval decltype(auto) packArgs(Args... args) 
{
	return recursive_pack<Args...>{}.value;
}


template<std::size_t N, bool TCond=true>
requires( N<=std::numeric_limits<unsigned char>::max())
constexpr auto packNArgs()
{
	return [&]<std::size_t... Idx>(std::index_sequence<Idx...>) 
	{
		if constexpr(TCond)
			return recursive_pack<int, decltype(static_cast<char>(Idx))..., int>{}.value;
		else
			return recursive_pack<int, decltype(static_cast<char>(Idx))...>{}.value;
	// the test numbers is limitted to 255 ; to increase multiply N by 2 or 3 ...etc which can be a template parameter 
	// if the total number template instantiation exceeds 900; it will fail; you have to use "-ftemplate-depth=number" as compile time def.
	// this is only meant to test otherwise use ranges
	}(std::make_index_sequence<N>{});
}


namespace detail
{
// Example to test std::void_t and Void_t; Both compiles with GCC ; TODO ; test with Clang, MSVC
// e.g: if the type T can be incremented t.operator++() should return T&
template<typename T, std::void_t<decltype(++std::declval<T&>())>* = nullptr>
T& blarg_impl(T& t) { return ++t; }

} // end of namespace detail

inline constexpr auto blargLamda = [](auto& x) ->decltype(detail::blarg_impl(x))
{ return detail::blarg_impl(x); };

struct Bar {};