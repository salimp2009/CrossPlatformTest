#include "RangesHeaders.hpp"
#include "Span/SpanTest.hpp"
#include "RangesBasic.hpp"
#include "RangesViewsComponents.hpp"
#include "RangesCompileTimeSize.hpp"
#include "NTTP/NTTP.hpp"
#include "CompileTimeThings/CompileRunTime.hpp"
#include "Views/ViewTests.hpp"
#include "CompileTimeThings/ConstEvalUseCases.hpp"
#include "TemplatesMetaProg/MetaProgramBasics.hpp"
#include "NTTP/NamedTupple.hpp"

int main()
{
	
	std::puts("Hello Ranges\n");
#if defined __GNUG__  || defined _MSC_VER && !defined(__clang__)

	//SpanConstness_Test();
	//RangesBasics();
	//RangesSort_Test();
	//RangesViews_Filter();
	//RangeAdoptors();
	//IsConstEvaluated_Test();
	//CustomTakeView_Test();
	//RangesSort_Strings();
	//RangesSentinels_NullTermin();
	//RangesSubRanges_Sentinels();
	//RangesSentinels_EndValue();
	//Ranges_BeginCount();
	//Ranges_Projections();
	RangesSort_Strings();
	RangesAdaptors_all();
	Ranges_LazyEval();
	RangesViews_WriteAccess();
	Ranges_BorrowedIterator();
	Ranges_ShallowConstantness();
	Ranges_MakeRangeConst();
	Ranges_GenericMaxValue();
	RangesView_Components();
	RangesView_Counted();
	RangesView_CommonAdaptor();
	RangesCompileTimeSize();
#if defined (__GNUG__)
	LambdaVariadicCapture_ContEval();
#endif
	Ranges_CountedIterator();
	Ranges_CommonIterator();
	NTTP_floatingPoints();
	
	CompileTimevsRunTime();
	SetPointsCompileTime();
	//ThrowinConstExprFunction();
#endif
#if defined (__GNUG__)  || !defined _MSC_VER && defined(__clang__)
	// MC_VER has a bug fixed VS2022 toolset
	NTTP_FixedString();
	ByteSwap_CompileRunTime();

	// gives non constexpression but it is constexpr ; bug fixed in VS2022
	CustomFormatter_WithConstEval();
#endif
	CompileTime_VirtualMembers();
	JoinViewTest1();
	AsConst_ConstEval_Test();
	MetaProgramming_Test();
	NamedTupple_Test();
	NamedTupple_Test2();
	MetaProgLinearSearch();
}