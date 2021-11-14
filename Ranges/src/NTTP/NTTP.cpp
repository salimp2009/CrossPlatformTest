#include "RangesHeaders.hpp"
#include "NTTP.hpp"
#include "NTTPUtils.hpp"



void NTTP_floatingPoints()
{
	std::puts("---NTTP_floatingPoints---");

	// Intellisense is wrong; it compiles both in GCC and MSVC
	static_assert(not std::is_same_v<NTTPDouble<0.6 - 0.2>, NTTPDouble<0.4>>);

	NTTPDouble<+0.6 - 0.2> mydouble1{};
	std::printf("%f ",mydouble1.data);

}