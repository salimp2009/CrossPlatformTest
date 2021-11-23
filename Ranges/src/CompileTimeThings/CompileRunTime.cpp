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

	std::printf("x=%f, y=%f \n", p1.GetX(), p1.GetY());
};

void ThrowinConstExprFunction()
{
	std::puts("--ThrowinConstExprFunction--");
	// this is compile time and will not allow divider to be 0 because it becomes a run-time function since it throws
	constexpr auto divResult1 = divideInt(3, 5);
	std::printf("%lf \n", divResult1);

	try 
	{
		// this is runtime since division by zero throws in the function; same function can be used as runtime or compile time
		auto divResult2 = divideInt(2, 0);
	}
	catch (const std::exception& e)
	{
		std::printf("%s \n", e.what());
	}
	catch (...)
	{
		std::puts("Runtime unknow error !!\n");
	}

	// the constexpr function throws during compile time if true is passed otherwise works ok !
	static_assert(!FunCheckWithConstExpr(false));
	// this will not compile because there is throw if it true is passed ; therefore cannot be used for compile time check
	//static_assert(FunCheckWithConstExpr(true));

	// this is OK becausealthough it throws it is used at runtime
	try
	{
		auto val = FunCheckWithConstExpr(true);
	}
	catch (const std::exception& e)
	{
		std::printf("%s \n", e.what());
	}
	catch (...)
	{
		std::puts("Runtime unknow error !!");
	}

	// using std::is_constant_evulated() to
	auto val = Fun();
}

	