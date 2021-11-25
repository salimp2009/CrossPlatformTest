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