//This part is Player.cpp
#include "game.h"
#include "enemy.h"
#include "bullet.h"
#include "Framework\console.h"
#include <dos.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
using std::vector;

void bulletActive(vector<projectile>& bullet, int bulletCounter, double bulletSpeed, double deltaTime)
{
	for(int i=0; i<bulletCounter; ++i)
	{
		if(bullet[i].active == true)
		{
			playerFire(bullet[i], bulletSpeed);
		}
	}
}

void playerFire(projectile& bullet, double bulletSpeed)
{
	//if not reach the end
	if(bullet.location.Y == 0)
	{
		bullet.active = false;
	}

	if(bullet.location.Y >= 0)
	{
		bullet.location.Y -= bulletSpeed;
	}
}


void printBullet(COORD bulletLocation)
{
	//print bullet/s
	gotoXY(bulletLocation.X, bulletLocation.Y);
	std::cout << (char)54;

}
