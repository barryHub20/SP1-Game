#ifndef _POWERUP_H
#define _POWERUP_H

#include "Framework\timer.h"

//struct for buffs
struct buffsForPlayer
{
	bool active;
	double timer;
	COORD placeForBuffs;
};

namespace
{
	buffsForPlayer powerupBullet;
}

//moving of the buffs
void powerupMovement();

//printing of powerup
void powerupPrint();

#endif