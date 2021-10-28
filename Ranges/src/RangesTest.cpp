#include "RangesHeaders.hpp"
#include "Span/SpanTest.hpp"
#include "RangesBasic.hpp"
#include "RangesUseCases.hpp"




int main()
{
	std::puts("Hello Ranges\n");

	SpanConstness_Test();
	RangesBasics();
	RangesSort_Test();
	RangesViews_Filter();
	RangeAdoptors();
	IsConstEvaluated_Test();
	CustomTakeView_Test();
	RangesSort_Strings();

	//
}