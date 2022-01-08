#include "ConceptsPCH.hpp"
#include "ConceptRequires.hpp"
#include "OverloadResolution.hpp"
#include "OverloadResOLD.hpp"
#include "ConstraintSamples.hpp"



void ConceptsRequirest_Test()
{
	std::puts("--ConceptsRequirest_Test--");

	constexpr int val1 = 42;
	constexpr int val2 = 77;
	
	constexpr auto result = maxxValue(val1, val2);
	std::printf("result maxxVal: %i\n", result);
	// Will not compile since the concept has a requirement not to have raw pointers !!
	//maxxValue(&val1, &val2);

	constexpr auto result2 = minnVal(val1, val2);
	std::printf("minnVal: %i\n", result2);
	minnVal(&val1, &val2);

	const int*  p1 = &val1;
	const int*  p2 = &val2;
	
	std::printf("minVal2: %i \n", minnVal2(p1, p2));

	auto result3 = minnVal3(p1, p2);
	std::printf("minVal3; pointer version: %i \n", result3);
	std::printf("minVal3: pointer, ref version: %i \n", minnVal3(p1, &val1));

	static_assert(std::is_pointer_v<decltype(p1)>);
	static_assert(IsPointer<decltype(p1)>);
	
	constexpr std::array val3 = {"sdad"};
	const auto* p3 = &val3;
	// this wont compile as expected since it does not match requires clause that it has to 3 way comparable !!
	//minnVal3(p1, p3);

}

void RequirementExpression_Test()
{
	std::puts("--ConceptsRequirest_Test--");
	std::vector vec1 = { 1,2,3,4 };
	constexpr std::array arr1 = { 1,2,3,4,5 };
	
	static_assert(ContainerType2<std::remove_cvref_t<decltype(vec1)>>);
	static_assert(!ContainerType2<std::remove_cvref_t<decltype(arr1)>>);

	add(vec1, 5);
	// will not compile since it is not same as the type of vector; if std::is_convertible_t is used then floating point passes to due implicit conversion !!!
	//add(vec1, 5.4f);
	
	// std::array does not have push_back() member function therefore will not compile
	//add(arr1, 10);

}


void OverloadResolution_Concepts()
{
	std::puts("--OverloadResolution_Concepts--");

	std::vector vec1 = { 1,2,3 };
	std::vector<double> vec2;
	addValue(vec1, 5);
	addValue(vec2, 0.5f);
	std::printf("floating point added: %f \n", vec2.back());

	// example that does not allow narrowing; it allows implicit conversion but No Narrawing
	addValue2(vec1, 25);
	//this will not compile as it does not match the No Narrowing Criteria
	//addValue2(vec1, 25.5);

	addValue3(vec1, 25);
	addValue4(vec2, 45.5);

	std::array arr1 = { 45, 56, 67 };
	addMultiValues(vec1,arr1);
	std::printf("%i \n", vec1.back());

	std::array arr2 = { 45.f, 125.3f, 35.f };
	// this does not compile since it will not satisfy the ConvertswithoutNarrowing concept
	//addMultiValues(vec1, arr2);

	std::set<int> setint = { 1,22,355,45 };
	addMultiValues(setint, arr1);

	// this does not compile since it will not satisfy the ConvertswithoutNarrowing concept
	//addMultiValues(setint, arr2);
}

void OverloadResol_BeforeCPP20()
{
	std::puts("--OverloadResol_BeforeCPP20--");
	std::vector vec1 = { 1,2,3 };
	addOLDWay(vec1, 5);
	std::printf("vec1 back: %i \n", vec1.back());

	std::set<int> setint = { 1,22,355,45 };
	addOLDWay(setint, 566);
	std::printf("setint added value: %i \n", *setint.find(566));

	// example for using enable_if so NO floating point
	addOLDWay2(vec1, 234);
	
	//will not compile
	//addOLDWay2(vec1, 24.5);

	// using std::void_t instead of enable_if to accept std::integral
	// std::void_t corner case it does not work ; second function should not work 
	addOLDWay3(vec1, 455);
	addOLDWay3(vec1, 455.56);
}

void ConstraintsWithRequires()
{
	std::puts("--ConstraintsWithRequires--");
	std::array<int, 5> arr1 = { 1,2,3,4 };
	SampleAdHoc(arr1);
	
	std::contiguous_iterator<decltype(arr1)::iterator>;
	static_assert(sizeof(arr1) > 4);
	std::is_same_v<typename decltype(arr1)::value_type, int>;
	

}
