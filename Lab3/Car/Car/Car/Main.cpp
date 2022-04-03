#include <iostream>
#include <string>

#include "Car.h"

std::string GetInfo(Car &car)
{
	std::string result;
	if (car.IsTurnedOn()) { result = "On "; }
	else { result = "Off ";	}

	Direction dir = car.GetDirection();
	switch (dir)
	{
		case Direction::Back: 
			result = result + "Back ";
			break;
		case Direction::Stop:
			result = result + "Stop ";
			break;
		case Direction::Forward:
			result = result + "Forward ";
			break;
	}

    result = result + std::to_string(car.GetSpeed()) + " ";
	result = result + std::to_string(car.GetGear());

    return result;
}

void DriveCar(Car &customerCar)
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		if (line == "Info")
		{
			std::cout << GetInfo(customerCar) << std::endl;
		}
		if (line == "EngineOn")
		{
			if (customerCar.TurnOnEngine())
				std::cout << "The engine is started." << std::endl;
			else
				std::cout << "Failed to start the engine." << std::endl;
		}
		if (line == "EngineOff")
		{
			if (customerCar.TurnOffEngine())
				std::cout << "The engine is turned off." << std::endl;
			else
				std::cout << "Failed to turn off the engine." << std::endl;
		}
		if (line.substr(0, line.find(" ")) == "SetGear")
		{
			int gear = std::stoi(line.substr(line.find(" ")));
			if (!customerCar.SetGear(gear))	{ std::cout << "Failed to switch gear." << std::endl; }
		}
		if (line.substr(0, line.find(" ")) == "SetSpeed")
		{
			float speed = std::stof(line.substr(line.find(" ")));
			if (!customerCar.SetSpeed(speed)) {	std::cout << "Failed to switch speed." << std::endl; }
		}
	}
}

int main()
{
	Car customerCar;
	DriveCar(customerCar);
	return 0;
}