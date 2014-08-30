#ifndef _PLAYERZONE_H
#define _PLAYERZONE_H

#include "Framework\timer.h"
#include "enemy.h"
#include <vector>
using std::vector;

struct zone{
	short Y;//stores its Y location
	double timer;//counts down to 0
	double breech;//trashold, time taken to breech
	int count;//counts number of enemy units at player zone
};//the player zone;

#endif