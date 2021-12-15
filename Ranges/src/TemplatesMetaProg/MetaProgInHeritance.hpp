#include "RangesHeaders.hpp"


	// Already defined MetaProgramBasics.hpp
	//template<typename T> struct TypeIdentity {};

// Check thru Pointers
	template<typename T>
	static constexpr std::true_type check(const TypeIdentity<T>*);

	template<typename T>
	static constexpr std::false_type check(const void*);

	template<typename... Ts>
	struct IsInPackImpl : TypeIdentity<Ts>... 
	{
	};

	template<typename Target, typename...Ts>
	using inherit_checkPtr_IsInPack = decltype(check<Target>(static_cast<IsInPackImpl<Ts...>*>(nullptr)));

// Check thru Instances; Note this is less performant than the pointer version
// Prefer the pointer implementation for larger data sets
	template<typename T>
	static constexpr bool check(TypeIdentity<T>) { return true; }
	
	template<typename T>
	static constexpr bool check(...) { return false; }

	template<typename Target, typename...Ts>
	using inherit_Instance_IsInPack = std::bool_constant<check<Target>(IsInPackImpl<Ts...>{})>;

// Check using struct 
	template<typename... Ts>
	struct IsInPackImplS : TypeIdentity<Ts>...
	{
		template<typename T>
		static constexpr std::true_type check(const TypeIdentity<T>);

		template<typename T>
		static constexpr std::false_type check(...);
	};

	template<typename Target, typename...Ts>
	using inherit_StructInst_IsInPack = decltype(IsInPackImplS<Ts...>::template check<Target>(IsInPackImplS<Ts...>{}));

	// TODO : check to get the correct result !
	template<typename Target, typename...Ts>
	static constexpr bool inherit_IsBaseOf = std::is_base_of_v < Target, IsInPackImpl<Ts...>>;