//This part is player.h
#ifndef _BULLET_H
#define _BULLET_H
 
#include "Framework\timer.h"
#include "game.h"
#include "enemy.h"
#include <vector>
using std::vector;

/**
semi-auto pistol: 1 shot per second
automatic pstol: 2 shot per second
smg: full unlimited burst/**/

struct projectile{
	double fireTimer;//fire rate of each bullet, changes with each type of weapo
	int ammoCount;//counts to see if reach last ammo, reset
	COORD location;//location of current bullet
	bool active;//if true, bullet is fired, if not true, 
};

void bulletActive(vector<projectile>&, int, double, double);
void playerFire(projectile&, double);
void printBullet(COORD);

#endif