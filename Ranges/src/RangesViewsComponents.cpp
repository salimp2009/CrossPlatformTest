#include "RangesHeaders.hpp"
#include "RangesViewsComponents.hpp"

#if defined __GNUG__  || defined _MSC_VER && !defined(__clang__)
void RangesView_Components()
{
	std::puts("---RangesView_Components---");

	std::vector vec{ 1,2,3,4,5,6,7,8,9 };
	std::ranges::iota_view iv{ 1,10 };

	// the arguments pass in std::views::all() has to be either a view or an lvalue range
	// temporary for && values cannot be used !
	[[maybe_unused]] auto v1 = std::views::all(vec);
	[[maybe_unused]] auto v2 = std::views::all(iv);
	[[maybe_unused]] auto v3 = std::views::all(std::views::take(vec, 3));
	
	// will not compile
	//auto v4 = std::views::all(std::move(vec));

	for (auto val : std::views::all(vec))
	{
		std::printf("%i ", val);
	}
	
	// std::views::all_t returns a std::ranges::ref_view<> of the type of passed range but
	// it only works with lvalue ranges or views; rvalues and temps (that are not views yet) are not acceptable
	// it has to be referencable
	[[maybe_unused]] std::views::all_t<decltype(vec)&>v5;
	[[maybe_unused]] std::views::all_t<std::vector<int>&> v6;

	// will not compile ; temporary values !!
	//std::views::all_t<std::vector<int>>;
	//std::views::all_t<std::vector<int>&&>;

	// The Conceot of viewable_range; can be used to check if it is OK to for all_t<> & all()

	static_assert(std::ranges::viewable_range<std::vector<int>> == false);
	static_assert(std::ranges::viewable_range<std::vector<int>&> == true);
	static_assert(std::ranges::viewable_range<std::vector<int>&&> == false);
	static_assert(std::ranges::viewable_range<std::ranges::iota_view<int>> == true);

	std::puts("");
}

void RangesView_Counted()
{
	std::puts("---RangesView_Counted---");

	// counted(begin, size) return different types of views depending on the type of passes range iterator
	// return std::span (as a view) if range is contigous_iterator; (std::vector, array, raw arrays...etc)
	// return ranges::subrange if it is random_access iterator ; std::deque
	// returns range::subrange of a counted_iterator with dummy sentinel of std::default_sentinel; it counts while iterating
	// for types std::list, associative containers, unordered containers(e.g.:hash tables)

	std::vector vec{ 1,2,3,4,5,6,7,89 };
	auto pos1 = std::ranges::find(vec, 4);
	// make sure position + count value <= container.size() so that you dont try to access beyond given range/container
	[[maybe_unused]] auto subVec = std::views::counted(pos1, 4);
	
	// this is a bug in gcc-11.1 ; current version of gcc returns the assert true; mvsvc and clang 13+ is ok
	// TODO : remove the preprocessor once i get gcc11-2 and also clang-11.3
	#if defined _MSC_VER
		static_assert(std::is_same_v<decltype(subVec), std::span<int>>);
	#endif // !

}


#endif