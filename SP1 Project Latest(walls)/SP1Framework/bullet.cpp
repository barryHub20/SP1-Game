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



void moveBullet(vector<projectile>& bullet, vector<enemy>& unit)
{
	for (int x = 0; x < bullet.size(); ++x) //Checks all Bullets inside the vector
	{
		if (bullet[x].pressing == true) //If it is pressed 
		{
			collision(bullet, unit);	
		}
	}
}

void showBullet(vector<projectile>& bullet)
{
	for (int x = 0; x< bullet.size(); x++)
	{
		if (bullet[x].pressing == true)
		{
			gotoXY(bullet[x].xCoordinate,bullet[x].yCoordinate);//Goes to your Bullet Location that has been shot
			std::cout<<" ";//Clears the Bullet Location to make sure that it doesnt overwrite anything
			std::cout << (char)94;//Prints the bullet at the location.
		}
	}
}
	
void collision (vector<projectile>& bullet, vector<enemy>& unit)
{
	for (int a = 0; a < bullet.size(); ++a) //Checks all Bullets inside the vector
	{
		if (bullet[a].yCoordinate != 0) //if bullet never hit the border move up
		{
			bullet[a].yCoordinate --;
		}

		if (bullet[a].yCoordinate == 0)//if bullet hits the border delete it
		{
			
			bullet.erase(bullet.begin() + a);
			//a--;
			break;//since the bullet is "dead" no longer need to check for now
		}

		//if (bullet[a].yCoordinate == (char)54)//iff bullet hit enemy delete it
		//{
		for (int u = 0; u < 8; u++)
		{
			if (bullet[a].yCoordinate == unit[u].location.Y  )
			{
				if (bullet[a].xCoordinate == unit[u].location.X)
				{
			//bullet[a].pressing = false;
				bullet.erase(bullet.begin() + a);
				unit[u].active = false;
				break;
				}
			}
		}
		//}

		/*if (bullet[a].yCoordinate == WALL)
		{
			bullet[a].pressing = false;
			//make wall lose health or delete it?
		}
		*/
	}
}


void MoveEnemyBullet(vector<laser>& EB)
{
	for (int x = 0; x < EB.size(); ++x) //Checks all Bullets inside the vector
	{
		if (EB[x].shooting == true) //If it is pressed 
		{
			EnemyBulletCollision(EB);	
		}
	}
}

void ShowEnemyBullet (vector<laser>& EB)
{
	for (int x = 0; x< EB.size(); x++)
	{
		if (EB[x].shooting = true && EB[x].YC != 25)
		{
			//if (
			gotoXY(EB[x].XC,EB[x].YC);//Goes to your Bullet Location that has been shot
			std::cout<<" ";//Clears the Bullet Location to make sure that it doesnt overwrite anything
			std::cout << (char)179;//Prints the bullet at the location.
		}
	}
}

void EnemyBulletCollision(vector<laser>& EB)
{
	for (int a = 0; a < EB.size(); ++a) //Checks all Bullets inside the vector
	{
		if (EB[a].YC != 25) //if bullet never hit the border move up
		{
			EB[a].YC ++;
		}

		if (EB[a].YC == 25)//if bullet hits the border delete it
		{
			EB.erase(EB.begin() + a);
			break;//since the bullet is "dead" no longer need to check for now
		}
	}
}
