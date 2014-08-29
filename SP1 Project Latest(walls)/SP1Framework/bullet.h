//This part is player.h
#ifndef _BULLET_H
#define _BULLET_H
 
#include "Framework\timer.h"
#include "game.h"
#include "enemy.h"
#include <vector>
using std::vector;
 
//player

struct projectile
{
	projectile()
	{
		pressing = false;  //Set the Pressing to be false at the start. It will change if spacebar is pressed.
	}
	    int xCoordinate;
		int yCoordinate;
        bool pressing;
};

struct laser
{
	laser()
	{
		shooting = false;
	}
	int XC; //The x coordinate
	int YC; // The Y coordinate
	bool shooting;
};

void moveBullet(vector<projectile>&, vector<enemy>&);
void showBullet(vector<projectile>&);
void collision(vector<projectile>&, vector<enemy>&);

void MoveEnemyBullet(vector<laser>&);
void ShowEnemyBullet(vector<laser>&);
void EnemyBulletCollision(vector<laser>&);

#endif