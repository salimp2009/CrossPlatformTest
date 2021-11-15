#include "RangesHeaders.hpp"
#include "NTTP.hpp"
#include "NTTPUtils.hpp"
#include "NTTPFixedString.hpp"



void NTTP_floatingPoints()
{
	std::puts("---NTTP_floatingPoints---");

	// Intellisense is wrong; it compiles both in GCC and MSVC
	static_assert(not std::is_same_v<NTTPDouble<0.6 - 0.2>, NTTPDouble<0.4>>);

	NTTPDouble<+0.6 - 0.2> mydouble1{};
	std::printf("%f ",mydouble1.data);

	// Intellisense is wrong; it compiles both in GCC and MSVC
	static_assert(not std::is_same_v < NTTPDouble<+0.1>, NTTPDouble<-0.1>>);
	static_assert(std::is_same_v<NTTPDouble<+0.1+0.1>, NTTPDouble<0.2>>);

	std::puts("");

}

void NTTP_FixedString()
{
	std::puts("---NTTP_FixedString---");
	constexpr fixedString fsTest{ "hello didokimin" };

	fixedStringContainer<"yow yow!!"> fsc{};

	fsc.print();
}