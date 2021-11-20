#include "RangesHeaders.hpp"
#include "CompileRunTime.hpp"

void CompileTimevsRunTime()
{
	std::puts("--CompileTimevsRunTime--");
	constexpr char name[]{ "Didoski" };
	constexpr auto length = StrLength(name);
	std::printf("String Length without null character: %zu \n", length);

}
