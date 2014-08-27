#ifndef _BULLET_H
#define _BULLET_H

#include "Framework\timer.h"
#include <vector>
using std::vector;

struct projectile
{
	bool notpressing; //Check if spacebar is pressed
	bool notready; //check if player can fire a gun
	int bulletcount; //Check number of bullets fired
	COORD bulletCoordinate; //Get coordinate of bullet
};

void bulletmovement(vector<projectile>& , COORD);
void abletoshootsatu(vector<projectile>&);
void abletoshootdua(vector<projectile>&);
void showbullet(short, short, vector<projectile>&);

#endif