#include "RangesHeaders.hpp"


struct Car
{
	virtual ~Car() 
	{ 
		std::puts("Car destructed!!\n"); 
	};
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

// TODO; check if optional is better since we have only one pointer to one type;
using CarType = std::variant<Mercedes, Audi, Hyundai>;

// not used; it was for an idea to use std::visit and variant
template<typename... Bases>
struct Overload : Bases...
{
	using Bases::operator()...;
};

// in case used this might not be needed in C++20
template<typename...Bases>
Overload(Bases...)->Overload<Bases...>;

// myversion to Test; 
// TODO; check if optional is better since we have only one pointer to one type;
std::optional<Car*> CreateCar2(int val)
{
	switch (val)
	{
		case 0: return new Mercedes{}; 
		case 1: return new Audi{};
		case 2: return new Hyundai{};
	}
	return {};
}

// the book version
inline Car* CreateCar(int val)
{
	switch (val)
	{
		case 0: return new Mercedes{};
		case 1: return new Audi{};
		case 2: return new Hyundai{};
	}
	return nullptr;
}

inline int FastestCar()
{
	int MaxSpeed = -1;
	int MaxID = -1;

	for (auto i : std::views::iota(1, 3))
	{
		auto car = CreateCar2(i);
		if (car.has_value())
		{
			if ((*car)->speed() > MaxSpeed)
			{
				MaxSpeed = (*car)->speed();
				MaxID = i;
			}

			car.reset();
		}
		
	}

	return MaxID;
}
