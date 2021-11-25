#pragma once
#include "NTTP/NTTPFixedString.hpp"

void CompileTimevsRunTime();
void SetPointsCompileTime();
void ThrowinConstExprFunction();
void ByteSwap_CompileRunTime();



consteval std::size_t StrLength(const char* str)
{
	return *str ? 1 + StrLength(str + 1) : 0;	
}


struct Point
{
	double x{};
	double y{};

	//constexpr explicit(true) Point(double xval, double yval) noexcept : x{xval}, y{yval} { }
	constexpr auto GetX() const noexcept{ return x; }
	constexpr auto GetY() const noexcept { return y; }

	constexpr void SetX(double xval) noexcept { x = xval; }
	constexpr void SetY(double yval) noexcept { y = yval; }
};

constexpr Point movePoint(Point p, double x, double y)
{
	// SetX function returns void ; C++20 allows constexpr void funct(..) ; this was not allowed before :)
	p.SetX(p.GetX() + x);
	p.SetY(p.GetY() + y);

	return p;
}

constexpr double divideInt(int divide, int divisor)
{
	if (0==divisor)
	{
		// if this runtime it is OK to use in constexpr but if divisor is compile time known argument 
		// than compile time error !
		throw std::overflow_error("Divide by Zero Not Allowed !");
	}

	return static_cast<double>(divide)/divisor;
}

constexpr bool FunCheckWithConstExpr(bool b)
{
	if (b) 
	{ 
		throw int(45); 
	}

	return false;
}
template<typename... Args>
constexpr void Log(std::string_view fmt, Args&&...args)
{
	if (not std::is_constant_evaluated())
	{
		// checking the argument size; need to check argument type match identifiers!! 
		auto fmtView = std::views::counted(fmt.data(), fmt.size());
		auto numArgs = std::ranges::count(fmtView, '%');
		assert(numArgs == sizeof...(Args));
		printf(fmt.data(), args...);
	}
}

constexpr bool Fun()
{
	using namespace std::string_view_literals;
	Log("Logging : %s"sv, "hope it works");
	return true;
}
