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

//enemy passed in by reference so that updated X and Y coor. is updated to unit.X[i] and unit.Y[i]
void enemyMovement(vector<enemy>& unit, double elapsedTime, COORD consoleSize, int size, int points, double velocity, double frameTime)
{
	 //check if enemy is still alive and pass in spawn time to check if the unit's wave period has expired, also pass in unit to edit its active status
	//waves starts when spawnTime is 4
	
		
	double spawnTime = isEnemyAlive(elapsedTime, unit, size, points);//get the new spawn time
	//wave 1
	if(elapsedTime >=spawnTime)
	{
		for(int i=0; i<size/2; ++i)
		{
			if(unit[i].active == true)//if the unit is active
			{
				enemyUnitAi(elapsedTime, unit[i], velocity, points, frameTime);//calls enemyAi and update its direction(pass as pointer)
			}
		}
	}
	//wave 2
	if(elapsedTime >= spawnTime + 4)
	{
		for(int i=size / 2; i<size; ++i)
		{
			if(unit[i].active == true)//if the unit is active
			{
				enemyUnitAi(elapsedTime, unit[i], velocity, points, frameTime);//calls enemyAi and update its direction(pass as pointer)	
			}
		}
	}

}

void enemyUnitAi(double elapsedTime, enemy& unit, double velocity, int numberOfPoints, double frameTime)
{
	/**
	if(unit.location.Y != unit.point[unit.count].Y && elapsedTime >= unit.time)
 	{
 		unit.time = elapsedTime + velocity;
 		unit.location.Y++;
 	}/**/
	if(unit.time < velocity)
	{
		unit.time += frameTime;//frameTime is deltaTime, counts time for each frame so is accurate with FPS
	}

	if(unit.location.Y != unit.point[unit.count].Y && unit.time >= velocity)
	{
		unit.location.Y++;
	}

	//if reached the X coor but not the Y coor of the target point and not the player line
	//if not reach the X coor of the target point and not reach player line
	if(unit.location.X != unit.point[unit.count].X && unit.location.Y == unit.point[unit.count].Y)
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
	if(unit.location.X == unit.point[unit.count].X  && unit.location.Y == unit.point[unit.count].Y)
	{
		//unit.mobile = false;//if false, can fire bullets
		//unit.stop_Timer = time + (rand() % 3 + 1);//can stop from 1 to 3 seconds;
		if(unit.count < numberOfPoints - 1)//while unit count does not access out of range of struct of vector
		{
			++unit.count;//increment the counter to refer to another preset target point
		}
	}

	//reset unit.time back to 0 or remainder
	if(unit.time == velocity)
	{
		unit.time = 0;
	}
	else if(unit.time > velocity)
	{
		unit.time -= velocity;
	}

}

double isEnemyAlive(double currentTime, vector<enemy>& unit, int size, int points)
{
	//simulate if all enemy unit died when reach Y = 30 (add score function to count score)
	//for enemy to die, make sure THAT UNIT.ACTIVE IS TRUE, even if false, units are initialiszed in their respective spawn points and if bullets hit it, scores
	for(int i=0; i<size; ++i)
	{
		if(unit[i].location.Y >= 30)
		{
			unit[i].active = false;
		}
	}


	static double respawn = 2;//set to 4 first
	
	bool reset = true;//if true, reset all x and y of units (all units died)

	for(int i=0; i<size; ++i)
	{
		if(unit[i].active == true)//if a unit is true
		{
			reset = false;
			break;//break since still got one unit alive
		}
	}


	//if reset true, all units are dead and reset their spawn points
	if(reset == true)
	{
		for(int i=0; i<size; ++i)
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
		for(int i=0; i<size; ++i)
		{
			unit[i].count = 0;//set counter to 0
		}
		targetPoint(unit, points);
		respawn = currentTime + 2;//respawn time reset for further references
	}

	return respawn;//return start spawn time
}

void targetPoint(vector<enemy>& unit, int points)
{
	int gridX = consoleSize.X / 8;//the length of each grid
	//loop through all units, 8 units
	for(int i=0; i<unit.size(); ++i)
	{
		int X = unit[i].spawnLocation.X + gridX / 2;//X is the rightmost point of the grid of the respective enemy unit
		unit[i].point[0].X = rand() % 9 + (X - 9);//does not need
		unit[i].point[0].Y = rand() % 5 + 1;//everytime set new target point, enemy unit will move 5 pixels towards player
		//store the target point for each enemy unit
		for(int j = 1; j<points; ++j)//modify to set 7 preset points
		{
			unit[i].point[j].X = rand() % 8 + (X - 9);//does not need
			unit[i].point[j].Y = (unit[i].point[j - 1]).Y + 3;//everytime set new target point, enemy unit will move 5 pixels towards player
		}
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
