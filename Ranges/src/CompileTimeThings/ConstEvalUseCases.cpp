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