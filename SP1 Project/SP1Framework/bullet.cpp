#include "game.h"
#include "bullet.h"
#include "Framework\console.h"
#include <dos.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
using std::vector;


/**
void bulletmovement(vector<projectile>& bullet, COORD consoleSize)
{
	abletoshootsatu(bullet); //Check if the player can shoot

	for (int c = 0; c < bullet.size(); c++)
	{
		if (bullet[c].bulletCoordinate.Y >= 0)//If bullet never touch screen keep moving up
		{
			bullet[c].bulletCoordinate.Y--;
		}
		else if (bullet[c].bulletCoordinate.Y == 1)//If bullet touch screen maker it false to stop redndering it
		{
			bullet.erase (bullet.begin());
			//bullet[c].bulletcount -= 1;
		}
	}
}

void abletoshootsatu(vector<projectile>& bullet)
{
	for (int b = 0; b < bullet.size(); b++)
	{
		if (bullet[b].notpressing = false)//Check if Spacebar is pressed
		{
			bullet[b].notready == false; //state how many bullet can player fire
		}
	}
}

void showbullet (short X, short Y, vector<projectile>& bullet)
{	
	for (int c = 0; c < bullet.size(); c++)
	{
		if (bullet[c].notready == false)
		{
			gotoXY(X,Y);
			std::cout << (char)94;
			//bullet[c].bulletcount += 1;
		}
	}
}/**/