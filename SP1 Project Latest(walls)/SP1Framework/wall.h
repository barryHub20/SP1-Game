#ifndef _WALL_H
#define _WALL_H
#include "powerUp.h"
#include "game.h"
#include "bullet.h"
#include "Framework\console.h"
#include "enemy.h"
#include "mainmenu.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#define MAXWALL 3
using std::string;

struct walls{ 
	int x;
	int y;
	
	void loadwall() 
	{
		x = rand()%50+10; //77
		y = rand()%9+1; //10
	}

	void renderwall()
	{
		gotoXY(x, y);
		const char* wall = "WALL";
		colour(0x6C);
		std::cout << wall;
	}

};

walls thewall[MAXWALL];

#endif