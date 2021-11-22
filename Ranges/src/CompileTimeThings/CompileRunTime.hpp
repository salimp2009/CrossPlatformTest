#pragma once


void CompileTimevsRunTime();
void SetPointsCompileTime();
void ThrowinConstExprFunction();


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
