#include "RangesHeaders.hpp"
#include "NTTP.hpp"
#include "NTTPUtils.hpp"
#include "NTTPFixedString.hpp"



void NTTP_floatingPoints()
{
	std::puts("---NTTP_floatingPoints---");

	// Intellisense is wrong; it compiles both in GCC and MSVC
	static_assert(not std::is_same_v<NTTPDouble<0.6 - 0.2>, NTTPDouble<0.4>>);

	NTTPDouble<+0.6 - 0.2> mydouble1{};
	std::printf("%f ",mydouble1.data);

	// Intellisense is wrong; it compiles both in GCC and MSVC
	static_assert(not std::is_same_v < NTTPDouble<+0.1>, NTTPDouble<-0.1>>);
	static_assert(std::is_same_v<NTTPDouble<+0.1+0.1>, NTTPDouble<0.2>>);

	std::puts("");

}

#if defined (__GNUG__)  || !defined _MSC_VER && !defined(__clang__)
void NTTP_FixedString()
{
	std::puts("---NTTP_FixedString---");
	constexpr fixedString fsTest{ "hello didokimin" };

	FormatString<"%s %s \n"> fstr1{};
	// MSC_V complain with %li
	std::printf("%li", fstr1.numArgs);
	std::puts("");
	print(fstr1, "hello", "oops");

	fixedStringContainer<"yow yow!!"> fsc{};
	fsc.print();

	std::puts("");
	int myVal = 5;
	int* p = &myVal;
	// intellisense gives false errors; it compiles and works :)
	print("%s\n"_fs, "does this work ???");
	print("%s %d %a %p \n"_fs, "Didoski is my Queen", 20, 40.50, p);

	auto myPrincess = "my princess is Didemoski !!";
	print("%s %i \n"_fs, "Didoski is my Queen", 455);

	// this is the case where user forgets the _fs literal to specify the identifiers as formatString
	// It will not Compile on purpose
	//print("%s %i \n", "Didoski is my Queen", 455);
}
#endif