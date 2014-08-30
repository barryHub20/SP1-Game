#include "Framework\console.h"
#include "powerUp.h"
#include "game.h"
#include "mainmenu.h"
#include <iostream>	

void powerupMovement()
{
	if (powerupBullet.active = true)
	{
		powerupBullet.placeForBuffs.X++;
		powerupBullet.placeForBuffs.Y = 10;
	}

	if (powerupBullet.placeForBuffs.X > 45)
	{
		powerupBullet.active = false;
	}

	//if (playerbullet coordinates == powerupBullet.placeForBuffs)
	//{
	//	powerupBullet.active = false;
	//	if (NoOfBulletsShoot < 4)
	//	{
	//		NoOfBulletsShoot++;
	//	}
	//}

}

void powerupPrint()
{
	if (powerupBullet.active == true)
	{
		gotoXY(powerupBullet.placeForBuffs.X, powerupBullet.placeForBuffs.Y);
		std::cout << "P";
	}

	if (powerupBullet.active == false)
	{
		gotoXY(powerupBullet.placeForBuffs.X, powerupBullet.placeForBuffs.Y);
		std::cout << " ";
	}
}

