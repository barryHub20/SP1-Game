// This is the main file for the game logic and function
//
//
#include "game.h"
#include "enemy.h"
#include "bullet.h"
#include "Framework\console.h"
#include <dos.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <float.h>
using std::vector;
extern COORD consoleSize;
extern vector<enemy> unit;


//enemy passed in by reference so that updated X and Y coor. is updated to unit.X[i] and unit.Y[i]
void enemyMovement(vector<enemy>& unit, double elapsedTime, COORD consoleSize)
{
	//pattern for waves, spawn 4 followed by 3 ...
	 //check if enemy is still alive and pass in spawn time to check if the unit's wave period has expired, also pass in unit to edit its active status
	//waves starts when spawnTime is 4
	if(elapsedTime > 4)
	{
		
		double spawnTime = isEnemyAlive(elapsedTime, unit);//get the new spawn time
		//wave 1
		if(elapsedTime >=spawnTime)
		{
			for(int i=0; i<4; ++i)
			{
				if(unit[i].active == true)//if the unit is active
				{
					enemyUnitAi(elapsedTime, unit[i]);//calls enemyAi and update its direction(pass as pointer)
				
				}
			}
		}
		//wave 2
		if(elapsedTime >= spawnTime + 4)
		{
			for(int i=4; i<8; ++i)
			{
				if(unit[i].active == true)//if the unit is active
				{
					
					enemyUnitAi(elapsedTime, unit[i]);//calls enemyAi and update its direction(pass as pointer)
					
				}
			}
		}
	}
}

void enemyUnitAi(double time, enemy& unit)
{
	/**
	//if touch player line(bottom of screen, Y coor) or sides of console(X coor)
	int num = rand() % 2;//generate a number between 0 and 1

	if(num == 0)
	{
		if(body.Y <= 21)//if body is not reach
		{
			body.Y+=2;
		}
	}

	else if(num == 1)
	{
		int num2 = rand() % 2;//generate a number between 0 and 1 to move left or right
		//collision detection with other enemy units
		if(num2 == 0 && body.X <= 75 && body.Y <= 21)//move right
		{
			body.X++;
			body.Y++;
		}
		else if(num2 == 1  && body.X >= 5 && body.Y <= 21)//move left
		{
			body.X--;
			body.Y++;
		}
	}/**/
	/** if not reach the 7th preset point yet **/

	if(unit.location.Y != unit.point[unit.count].Y && unit.count < 10)
	{
		unit.location.Y++;
	}

	//if reached the X coor but not the Y coor of the target point and not the player line
	//if not reach the X coor of the target point and not reach player line
	if(unit.location.X != unit.point[unit.count].X && unit.location.Y == unit.point[unit.count].Y && unit.count < 10)
	{
		//if the target point X coor is bigger than the spawn point X coor
		if(unit.location.X < unit.point[unit.count].X)
		{
			unit.location.X++;
		}
		if(unit.location.X > unit.point[unit.count].X )
		{
			unit.location.X--;
		}
	}

		//if reached target point, call to set new target point and not reach player line
	if(unit.location.X == unit.point[unit.count].X  && unit.location.Y == unit.point[unit.count].Y && unit.count < 10)
	{
		unit.mobile = false;//if false, can fire bullets
		//unit.stop_Timer = time + (rand() % 3 + 1);//can stop from 1 to 3 seconds;
		unit.count++;//increment the counter to refer to another preset target point
	}
}

double isEnemyAlive(double currentTime, vector<enemy>& unit)
{
	//simulate if all enemy unit died when reach Y = 30 (add score function to count score)
	//for enemy to die, make sure THAT UNIT.ACTIVE IS TRUE, even if false, units are initialiszed in their respective spawn points and if bullets hit it, scores
	for(int i=0; i<8; ++i)
	{
		if(unit[i].location.Y >= 30)
		{
			unit[i].active = false;
		}
	}


	static double respawn = 2;//set to 4 first
	
	bool reset = false;//if true, reset all x and y of units (all units died)

	for(int i=0; i<8; ++i)
	{
		if(unit[i].active == false)//if unit is false
		{
			reset = true;
		}
		else if(unit[i].active == true)//else if unit is true
		{
			reset = false;
			break;//break since still got one unit alive
		}
	}

	//if reset true, all units are dead and reset their spawn points
	if(reset == true)
	{
		for(int i=0; i<8; ++i)
		{
			//if wave preiod ended and unit died before
			//reset enemy active to true
			unit[i].active = true;
			//reset each enemy unit spawn point Y
			unit[i].location.Y = unit[i].spawnLocation.Y;
			//reset each enemy unit spawn point X
			unit[i].location.X = unit[i].spawnLocation.X;
		}
		//reset the target points (including the Y coor individually)
		for(int i=0; i<8; ++i)
		{
			unit[i].count = 0;//set counter to 0
		}
		targetPoint(unit);
		respawn = currentTime + 2;//respawn time reset for further references
	}

	return respawn;//return start spawn time
}

void targetPoint(vector<enemy>& unit)
{
	int gridX = consoleSize.X / 8;//the length of each grid
	//loop through all units, 8 units
	for(int i=0; i<8; ++i)
	{
		static int three = rand() % 5 + 1;//set each time advance down 3 pixel
		int X = unit[i].spawnLocation.X + gridX / 2;//X is the rightmost point of the grid of the respective enemy unit
		//store the target point for each enemy unit
		for(int j = 0; j<10; ++j)//modify to set 7 preset points
		{
			unit[i].point[j].X = rand() % 9 + (X - 10);//does not need
			unit[i].point[j].Y = three;//everytime set new target point, enemy unit will move 5 pixels towards player
			three += 3;
		}

		three = 3;//set back to 3
	}
}

void printEnemy(COORD body)
{
	//print body
	gotoXY(body.X, body.Y);
	std::cout << (char)54;

	//print right wing
	gotoXY(body.X - 1, body.Y);
	std::cout << (char)195;

	//print left wing
	gotoXY(body.X + 1, body.Y);
	std::cout << (char)180;
}
