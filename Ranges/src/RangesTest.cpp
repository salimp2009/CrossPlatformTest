#include "Span/SpanTest.hpp"
#include "RangesBasic.hpp"



int main()
{
	std::puts("Hello Ranges\n");
#if defined __GNUG__  || defined _MSC_VER && !defined(__clang__)

	SpanConstness_Test();
	RangesBasics();
	RangesSort_Test();
	RangesViews_Filter();
	RangeAdoptors();
	IsConstEvaluated_Test();
	CustomTakeView_Test();
	RangesSort_Strings();
	RangesSentinels_NullTermin();
	RangesSubRanges_Sentinels();
	RangesSentinels_EndValue();
	Ranges_BeginCount();
	Ranges_Projections();
	RangesSort_Strings();
	RangesAdaptors_all();
	Ranges_LazyEval();

#endif
}