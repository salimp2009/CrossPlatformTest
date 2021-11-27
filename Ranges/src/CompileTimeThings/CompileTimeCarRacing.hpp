#include "RangesHeaders.hpp"
#include "ConstexprUniquePtr.hpp"


struct Car
{
	constexpr virtual ~Car() = default;
	constexpr virtual int speed() const = 0;
};

struct Audi :Car
{
	constexpr virtual int speed() const override { return 4; }
};

struct Mercedes :Car
{
	constexpr virtual int speed() const override { return 5; }
};

struct Hyundai :Car
{
	constexpr virtual int speed() const override { return 6	; }
};


constexpr uniquePtr<Car> CreateCar(int val)
{
	switch (val)
	{
		case 0: return new Mercedes{};
		case 1: return new Audi{};
		case 2: return new Hyundai{};
	}
	return nullptr;
}

constexpr int FastestCar()
{
	int MaxSpeed = -1;
	int MaxID = -1;

	for (auto i : std::views::iota(0, 3))
	{
		auto car = CreateCar(i);
		if (car == nullptr) { return MaxID; }
		if ( car->speed() > MaxSpeed)
		{
			MaxSpeed = car->speed();
			MaxID = i;
		}
	}

	return MaxID;
}
