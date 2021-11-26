#include "RangesHeaders.hpp"


struct Car
{
	virtual ~Car() = default;
	virtual int speed() const = 0;
};


struct Audi :Car
{
	virtual int speed() const override { return 4; }
};

struct Mercedes :Car
{
	virtual int speed() const override { return 5; }
};

struct Hyundai :Car
{
	virtual int speed() const override { return 6	; }
};


using CarType = std::variant<Audi, Mercedes, Hyundai>;

template<typename... Bases>
struct Overload : Bases...
{
	using Bases::operator()...;
};

template<typename...Bases>
Overload(Bases...)->Overload<Bases...>;

// myversion to Test
CarType CreateCar2(int val)
{
	switch (val)
	{
		case 0: return CarType{ Mercedes() };
		case 1: return CarType{ Audi() };
		case 2: return CarType{ Hyundai() };
	}
	return {};
}

// the book version
Car* CreateCar(int val)
{
	switch (val)
	{
		case 0: return new Mercedes{};
		case 1: return new Audi{};
		case 2: return new Hyundai{};
	}
	return nullptr;
}
