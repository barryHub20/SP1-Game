#ifndef _BULLET_H
#define _BULLET_H

#include "Framework\timer.h"
#include <vector>
using std::vector;

struct projectile
{
	bool pressed; //Check if spacebar is pressed
	bool ready; //check if player can fire a gun
	COORD bulletCoordinate; //Get coordinate of bullet
};

void bulletMovement(projectile&);
void abletoshootsatu(vector<projectile>&);
void abletoshootdua(vector<projectile>&);
void showbullet(short, short, vector<projectile>&);

#endif