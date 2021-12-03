#include "RangesHeaders.hpp"
#include "ConstEvalUseCases.hpp"

void AsConst_ConstEval_Test()
{
	std::puts("--AsConst_ConstEval_Test--");
	
	// this is calculated at compile time since function as_constant has specifier consteval
	// and val2 is not a constant value and can be used at runtime
	auto val2 = as_constant(ExpensiveCalculation(2));

	static_assert(as_constant(ExpensiveCalculation(2) ==3));
	
	++val2;

}

#if defined (__GNUG__)  || !defined _MSC_VER && defined(__clang__)
void CustomFormatter_WithConstEval()
{
	std::puts("--CustomFormatter_WithConstEval--");
	// the specfiers "ds" are checked against types of arguments during compile time; NOT the values
	// the actual returned value (string) is runtime since we are using new to create a new string and 
	// not deleting it during compile time because we use it in runtime 
	auto str = format("ds", 12547, "hello");

	// now we can use the result of format in runtime
	std::printf("%s \n", str.data());
	
}

#endif