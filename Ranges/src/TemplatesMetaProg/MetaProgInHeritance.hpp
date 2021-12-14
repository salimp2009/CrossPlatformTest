#include "RangesHeaders.hpp"


	// Already defined MetaProgramBasics.hpp
	//template<typename T> struct TypeIdentity {};

// Check thru Pointers
	template<typename T>
	static constexpr std::true_type check(const TypeIdentity<T>*);

	template<typename T>
	static constexpr std::false_type check(const void*);

	template<typename... Ts>
	struct IsInPackImpl : TypeIdentity<Ts>... {};

	template<typename Target, typename...Ts>
	using inherit_checkPtr_IsInPack = decltype(check<Target>(static_cast<IsInPackImpl<Ts...>*>(nullptr)));

// Check 

	

