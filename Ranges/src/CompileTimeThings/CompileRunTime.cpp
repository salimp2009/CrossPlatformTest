#include "RangesHeaders.hpp"
#include "CompileRunTime.hpp"

void CompileTimevsRunTime()
{
	std::puts("--CompileTimevsRunTime--");
	constexpr char name[]{ "Didoski" };
	constexpr auto length = StrLength(name);
	std::printf("String Length without null character: %zu \n", length);
}

void SetPointsCompileTime()
{
	std::puts("--SetPointsCompileTime--");

	constexpr Point p1 = movePoint({ .x=45.55, .y=65.78 }, 20.5, 45.67);

	std::printf("x=%f, y=%f", p1.GetX(), p1.GetY());

};

	