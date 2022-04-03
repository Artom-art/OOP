#include "Car.h"

std::vector<Border> SpeedBorders()
{
	std::vector<Border> result;
	result.push_back({0, 20});
	result.push_back({0, 500});
	result.push_back({0, 30});
	result.push_back({20, 50});
	result.push_back({30, 60});
	result.push_back({40, 90});
	result.push_back({50, 150});
	return result;
}

int GearNumber(Gear gear)
{
	switch (gear)
	{
		case Gear::Rear:
			return -1;
		case Gear::Neutral:
			return 0;
		case Gear::First:
			return 1;
		case Gear::Second:
			return 2;
		case Gear::Third:
			return 3;
		case Gear::Fourth:
			return 4;
		default:
			return 5;
	}
}

Car::Car()
{
	engineOn = false;
	nowGear = Gear::Neutral;
	nowSpeed = 0;
	nowDirection = Direction::Stop;
	speedBorders = SpeedBorders();
}

bool Car::TurnOnEngine()
{
	engineOn = true;
	return true;
}

bool Car::TurnOffEngine()
{
	if (nowSpeed == 0 && nowGear == Gear::Neutral)
	{
		engineOn = false;
		return true;
	}
	return false;
}

bool Car::IsTurnedOn() const
{
	return engineOn;
}

Direction Car::GetDirection() const
{
	return nowDirection;
}

float Car::GetSpeed() const
{
	return (nowSpeed < 0) ? -nowSpeed : nowSpeed;
}

int Car::GetGear() const
{
	return GearNumber(nowGear);
}

bool Car::SetGear(int gear)
{
	if (gear < -1 || gear > 5)
	{
		return false;
	}
	// Переставить на нейтральную передачу можно всегда.
	if (gear == 0)
	{
		nowGear = Gear::Neutral;
		return true;
	}

	// Если двигатель заглушен, не переключаем передачу.
	if (!engineOn)
	{
		return false;
	}
	
	if (nowSpeed == 0)
	{
		if (gear == 1)
		{
            nowGear = Gear::First;
			return true;
		}
		if (gear == -1) 
		{
			nowGear = Gear::Rear;
			return true;
		}
	}

	int prevGear = GearNumber(nowGear);
	Border prevBorder = speedBorders[prevGear + 1];
	Border nextBorder = speedBorders[gear + 1];

	if (prevGear <= gear)
	{	
		// Перестановка скорости вверх
		if (nowSpeed <= prevBorder.max && nowSpeed >= nextBorder.min && nowSpeed <= nextBorder.max
			 && prevGear != -1)
		{
			switch (gear)
			{
				case 1:
					nowGear = Gear::First;
					break;
				case 2:
					nowGear = Gear::Second;
					break;
				case 3:
					nowGear = Gear::Third;
					break;
				case 4: 
					nowGear = Gear::Fourth;
					break;
				case 5:
					nowGear = Gear::Fifth;
					break;
			}	
			return true;
		}
	}
	else if (gear != -1)
	{
		if (nowSpeed <= nextBorder.max && nowSpeed >= prevBorder.min)
		{
			switch (gear)
			{
				case 1:
					nowGear = Gear::First;
					break;
				case 2:
					nowGear = Gear::Second;
					break;
				case 3:
					nowGear = Gear::Third;
					break;
				case 4:
					nowGear = Gear::Fourth;
					break;
			}
			return true;
		}
	}

	return false;
}

bool Car::SetSpeed(float speed)
{
	if (!engineOn)
	{
		return false;
	}

	bool changed = false;
	if (nowSpeed < 0)
	{
		nowSpeed = -nowSpeed;
		changed = true;
	}

	int nowGearNumber = GearNumber(nowGear);
	if (speed >= speedBorders[nowGearNumber + 1].min && speed <= speedBorders[nowGearNumber + 1].max)
	{
		if (nowGearNumber != 0)
		{
			if (nowGearNumber == -1)
			{
				nowSpeed = -speed;
				nowDirection = (speed != 0) ? Direction::Back : Direction::Stop;
				return true;
			}
			nowSpeed = speed;
			nowDirection = (speed != 0) ? Direction::Forward : Direction::Stop;
			return true;
		}
		else if (nowSpeed > speed)
		{
			nowSpeed = speed;
			nowDirection = (speed == 0) ? Direction::Stop : nowDirection;
			return true;
		}
	}

	nowSpeed = (changed) ? -nowSpeed : nowSpeed;
	return false;
}