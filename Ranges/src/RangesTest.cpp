#include "Span/SpanTest.hpp"
#include "RangesBasic.hpp"



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
	RangesSentinels_NullTermin();
	RangesSubRanges_Sentinels();
	RangesSentinels_EndValue();
}