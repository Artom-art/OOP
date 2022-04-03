#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"

#include "../Car/Car.h"

SCENARIO("Turn on and turn off car")
{
	Car custCar;
	WHEN("Starting a stalled machine.")
	{
		REQUIRE(custCar.TurnOnEngine() == true);
	}
	WHEN("Shut down a running machine")
	{
		custCar.TurnOnEngine();
		REQUIRE(custCar.TurnOffEngine() == true);
	}
	WHEN("Start a car that's already started")
	{
		custCar.TurnOnEngine();
		REQUIRE(custCar.TurnOnEngine() == true);
	}
	WHEN("Shut down an unfinished car")
	{
		REQUIRE(custCar.TurnOffEngine() == true);
	}
	WHEN("It is impossible to turn off the engine not in neutral gear")
	{
		custCar.TurnOnEngine();
		custCar.SetGear(1);
		REQUIRE(custCar.TurnOffEngine() == false);
	}
}

SCENARIO("Gear shifting")
{
	Car custCar;
	WHEN("Setting the first gear")
	{
		custCar.TurnOnEngine();
		REQUIRE(custCar.SetGear(1) == true);
	}
	WHEN("Setting the reverse gear")
	{
		custCar.TurnOnEngine();
		REQUIRE(custCar.SetGear(-1) == true);
	}
	WHEN("Setting the first gear with turn off engine")
	{
		REQUIRE(custCar.SetGear(1) == false);
	}
	WHEN("Setting the neutral gear with turn off engine")
	{
		REQUIRE(custCar.SetGear(0) == true);
	}
	WHEN("You cannot install a non-existent transfer")
	{
		custCar.TurnOnEngine();
		custCar.SetGear(-1);
		custCar.SetSpeed(20);
		REQUIRE(custCar.SetGear(-2) == false);
		
		custCar.SetSpeed(0);
		custCar.SetGear(1);
		custCar.SetSpeed(20);
		custCar.SetGear(2);
		custCar.SetSpeed(50);
		custCar.SetGear(5);
		custCar.SetSpeed(100);
		REQUIRE(custCar.SetGear(6) == false);
	}
	WHEN("It is impossible to switch from reverse gear to any forward gear at speed")
	{
		custCar.TurnOnEngine();
		custCar.SetGear(-1);
		custCar.SetSpeed(10);
		REQUIRE(custCar.SetGear(1) == false);
		REQUIRE(custCar.SetGear(2) == false);
		REQUIRE(custCar.SetGear(3) == false);
		REQUIRE(custCar.SetGear(4) == false);
		REQUIRE(custCar.SetGear(5) == false);
	}
	WHEN("It is impossible to switch from the first gear to the rear at speed")
	{
		custCar.TurnOnEngine();
		custCar.SetGear(1);
		custCar.SetSpeed(15);
		REQUIRE(custCar.SetGear(-1) == false);
		custCar.SetSpeed(20);
		custCar.SetGear(2);
		REQUIRE(custCar.SetGear(-1) == false);
	}
	WHEN("It is impossible to switch from neutral gear to reverse at speed")
	{
		custCar.TurnOnEngine();
		custCar.SetGear(1);
		custCar.SetSpeed(20);
		REQUIRE(custCar.SetGear(0) == true);
		REQUIRE(custCar.SetGear(-1) == false);
	}
	WHEN("You can switch from neutral gear to front if the speed allows")
	{
		custCar.TurnOnEngine();
		custCar.SetGear(1);
		custCar.SetSpeed(25);
		custCar.SetGear(0);
		REQUIRE(custCar.SetGear(2) == true);

		REQUIRE(custCar.SetGear(1) == true);
		custCar.SetSpeed(0);
		custCar.SetGear(-1);
		custCar.SetSpeed(20);
		custCar.SetGear(0);
		REQUIRE(custCar.SetGear(2) == false);
	}
}

SCENARIO("Set different speeds")
{
	Car custCar;
	WHEN("Set more speed than now in neutral gear")
	{
		REQUIRE(custCar.SetSpeed(10) == false);
	}
	WHEN("Set speed when engine is off")
	{
		custCar.SetGear(1);
		REQUIRE(custCar.SetSpeed(10) == false);
	}
	WHEN("Set speed in not neutral gear")
	{
		custCar.TurnOnEngine();
		custCar.SetGear(1);
		REQUIRE(custCar.SetSpeed(15) == true);
	}
	WHEN("Setting the speed outside the range")
	{
		custCar.TurnOnEngine();
		custCar.SetGear(1);
		REQUIRE(custCar.SetSpeed(35) == false);
		custCar.SetSpeed(0);
		custCar.SetGear(-1);
		REQUIRE(custCar.SetSpeed(21) == false);
		REQUIRE(custCar.SetSpeed(-1) == false);
		custCar.SetGear(0);
		REQUIRE(custCar.SetSpeed(15) == false);
	}
}

SCENARIO("Get info about car")
{
	Car custCar;
	WHEN("Get engine info")
	{
		custCar.TurnOnEngine();
		REQUIRE(custCar.IsTurnedOn() == true);

		custCar.TurnOffEngine();
		REQUIRE(custCar.IsTurnedOn() == false);
	}
	WHEN("Get gear info")
	{
		custCar.TurnOnEngine();
		custCar.SetGear(-1);
		REQUIRE(custCar.GetGear() == -1);
		custCar.SetGear(0);
		REQUIRE(custCar.GetGear() == 0);
		custCar.SetGear(1);
		REQUIRE(custCar.GetGear() == 1);
		custCar.SetSpeed(25);
		custCar.SetGear(2);
		REQUIRE(custCar.GetGear() == 2);
		custCar.SetSpeed(35);
		custCar.SetGear(3);
		REQUIRE(custCar.GetGear() == 3);
		custCar.SetSpeed(45);
		custCar.SetGear(4);
		REQUIRE(custCar.GetGear() == 4);
		custCar.SetSpeed(55);
		custCar.SetGear(5);
		REQUIRE(custCar.GetGear() == 5);
	}
	WHEN("Get speed info") 
	{
		custCar.TurnOnEngine();
		custCar.SetGear(-1);
		custCar.SetSpeed(10);
		REQUIRE(custCar.GetSpeed() == 10);
		custCar.SetGear(0);
		custCar.SetSpeed(0);
		REQUIRE(custCar.GetSpeed() == 0);
		custCar.SetGear(1);
		custCar.SetSpeed(10);
		REQUIRE(custCar.GetSpeed() == 10);
		custCar.SetSpeed(25);
		custCar.SetGear(2);
		REQUIRE(custCar.GetSpeed() == 25);
		custCar.SetSpeed(35);
		custCar.SetGear(3);
		REQUIRE(custCar.GetSpeed() == 35);
		custCar.SetSpeed(45);
		custCar.SetGear(4);
		REQUIRE(custCar.GetSpeed() == 45);
		custCar.SetSpeed(55);
		custCar.SetGear(5);
		REQUIRE(custCar.GetSpeed() == 55);
	}
	WHEN("Get direction info") 
	{
		custCar.TurnOnEngine();
		custCar.SetGear(1);
		custCar.SetSpeed(10);
		REQUIRE(custCar.GetDirection() == Direction::Forward);
		custCar.SetGear(0);
		custCar.SetSpeed(0);
		REQUIRE(custCar.GetDirection() == Direction::Stop);
		custCar.SetGear(-1);
		custCar.SetSpeed(10);
		REQUIRE(custCar.GetDirection() == Direction::Back);
		custCar.SetGear(0);
		custCar.SetSpeed(0);
		REQUIRE(custCar.GetDirection() == Direction::Stop);
		custCar.SetGear(1);
		custCar.SetSpeed(10);
		REQUIRE(custCar.GetDirection() == Direction::Forward);
		custCar.SetSpeed(25);
		custCar.SetGear(2);
		REQUIRE(custCar.GetDirection() == Direction::Forward);
		custCar.SetSpeed(35);
		custCar.SetGear(3);
		REQUIRE(custCar.GetDirection() == Direction::Forward);
		custCar.SetSpeed(45);
		custCar.SetGear(4);
		REQUIRE(custCar.GetDirection() == Direction::Forward);
		custCar.SetSpeed(55);
		custCar.SetGear(5);
		REQUIRE(custCar.GetDirection() == Direction::Forward);
	}
}