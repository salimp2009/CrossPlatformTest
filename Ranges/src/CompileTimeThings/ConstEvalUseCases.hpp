#include "RangesHeaders.hpp"
#include "CustomFormatterTypeSafe.hpp"

void AsConst_ConstEval_Test();
void CustomFormatter_WithConstEval();


constexpr int ExpensiveCalculation(int base)
{
	return base + 1;
}


consteval auto as_constant(auto value)
{
	return value;
}