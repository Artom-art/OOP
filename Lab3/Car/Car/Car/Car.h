#pragma once
#include <vector>

struct Border
{
	float min;
	float max;
};

enum class Gear
{
	Rear = -1,
	Neutral,
	First,
	Second,
	Third,
	Fourth,
	Fifth
};

enum class Direction
{
	Back = -1,
	Stop,
	Forward
};

class Car
{
public:
	Car();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(float speed);
	bool IsTurnedOn() const;
	Direction GetDirection() const;
	float GetSpeed() const;
	int GetGear() const;

private:
	bool engineOn;
	Gear nowGear;
	float nowSpeed;
	Direction nowDirection;
	std::vector<Border> speedBorders;
};
