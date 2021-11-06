#include "RangesHeaders.hpp"
#include "RangesViewsComponents.hpp"

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
	// it only works with lvalue ranges or views; rvalues and temps are not acceptable
	// it has to be referencable
	[[maybe_unused]] std::views::all_t<decltype(vec)&>v5;
	[[maybe_unused]] std::views::all_t<std::vector<int>&> v6;

	// will not compile ; temp value !!
	//std::views::all_t<std::vector<int>>;
	//std::views::all_t<std::vector<int>&&>;
}