#include "RangesHeaders.hpp"

#include <experimental/iterator>

void NamedTupple_Test();
void NamedTupple_Test2();


template<typename TChar, std::size_t N>
struct fixed_string
{
	TChar data[N]{};
	static constexpr std::size_t size = N;

	//constexpr explicit(false) fixed_string(const TChar(&str)[N])
	//{
	//	std::copy_n(str, N, data);
	//}

	// Used in the original example ; the above method is nicer to me :)
	// if you use both then compiler error for ambigiues overloading
	constexpr explicit(false) fixed_string(const TChar* str)
	{
		std::copy_n(str, N, data);
	}

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
	constexpr auto operator=(const T& val)
	{
		return arg<Name, T>{.value = val};
	}

};


// This is copy/paste from Kris Cusiak code ; used for testing to resolve the problems with 
// nametuple class operator[](T) does not compile; tried to test if it was std::any was the problem
// but this one still fails :(
struct any : std::any {
	any() = default;
	template <class T>
	explicit(false) any(const T& a)
		: std::any{ a },
		print{ [](std::ostream& os, const std::any& a) -> std::ostream& 
		{
			if constexpr (requires { os << std::any_cast<T>(a); }) 
			{
				os << std::any_cast<T>(a);
			}
			else if constexpr (requires 
					{
							 std::begin(std::any_cast<T>(a));
							 std::end(std::any_cast<T>(a));
					}) 
			{
				auto obj = std::any_cast<T>(a);
				std::copy(std::begin(obj), std::end(obj), std::experimental::make_ostream_joiner(os, ','));
			}
			else 
			{
				os << a.type().name();
			}
			return os;
		} } {}
		
		template <class T>
		constexpr explicit(false) operator T() const {
			return std::any_cast<T>(*this);
		}
		
		friend std::ostream& operator<<(std::ostream& os, const any& a) {
			return a.print(os, a);
		}
		
		private:
			std::ostream& (*print)(std::ostream&, const std::any&) {};
};


// this is to test during implementation ; will be revised afterwards
template<fixed_string Name>
constexpr auto operator""_ts()
{
	return arg<Name, any>{};
}

template<typename... Ts>
struct namedtuple : Ts...
{
	constexpr explicit(true) namedtuple(Ts... ts): Ts{ts}... {}

	template<fixed_string Name, class TValue>
	[[nodiscard]] constexpr decltype(auto) get(arg<Name, TValue>&& t)
	{
		return (t.value);
	}

	// TODO: Find out why these dont work as presented 
	template<class T>
	[[nodiscard]] constexpr auto operator[](T) ->decltype(get<T::name>(*this))
	{
		
		return get<T::name>(*this);
	}
	
	// TODO: Find out why these dont work as presented
	//template<class T>
	//[[nodiscard]] constexpr auto operator[](T) const& ->decltype(get<T::name>(*this))
	//{
	//	return get<T::name>(*this);
	//}

};

// as of C++20 this might not be needed 
template<typename...Ts>
namedtuple(Ts... ts)->namedtuple<Ts...>;
 











