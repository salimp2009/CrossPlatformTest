#pragma once
#include <cmath>

template<double Value>
struct NTTPDouble
{
	double data = Value;
};

template<double Vat>
int addTax(int value)
{
	return static_cast<int>(std::round(value * (1 + Vat)));
}
