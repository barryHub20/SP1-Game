#ifndef _ENEMY_H
#define _ENEMY_H

#include "Framework\timer.h"
#include <vector>
using std::vector;

//enemy
struct enemy
{
	bool active;//check if coorosponding unit is active
	bool mobile;//if not mobile, if false, fire bullet
	COORD spawnLocation;//store the spawn location of each unit
	COORD location;//store corrosponding X and Y locations of each enemy unit's body
	vector<COORD> point;//preset target point
	double time;//enemy velocity (time)
	bool fire;//check ready to engage status (every 5 sec)
	int count;//number of points to reach
	int level;//this stores the level for each unit, 0 = mechanized trooper, 1 = mechanized robot, 2 = dual-turrent cyborg
};


//animate enemy unit function
void enemyMovement(vector<enemy>&, double, COORD, int, int, double);
void printEnemy(COORD);
void enemyUnitAi(double, enemy&, double, int);
void targetPoint(vector<enemy>&, int);//set the target points
//check if enemy is true
double isEnemyAlive(double, vector<enemy>&, int, int);

#endif