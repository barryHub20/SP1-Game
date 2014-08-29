#include "Framework\console.h"
#include "powerUp.h"
#include "game.h"
#include <iostream>

void powerup()
{

	if (powerupBullet.timer > 20)
	{
		powerupBullet.placeForBuffs.X = rand() % 80;	//spawns the icon at a random x coordinate
		powerupBullet.placeForBuffs.Y = 0;			    //spawns icon at top of screen
		powerupBullet.timer = 0;
	}

	if (powerupBullet.timer++)
	{
		powerupBullet.placeForBuffs.Y--;
	}
}

void health()
{

	if (healthPack.timer > 50)
	{
		healthPack.placeForBuffs.X = rand() % 100;
		healthPack.placeForBuffs.Y = 0;
		healthPack.timer = 0;
	}

	if (healthPack.timer++)
	{
		healthPack.placeForBuffs.Y--;
	}

}

void printPowerUp ()
{
	gotoXY(powerupBullet.placeForBuffs);
	std::cout << "P";
}

void printHealth()
{
	gotoXY(healthPack.placeForBuffs);
	std::cout << (char)3;
}