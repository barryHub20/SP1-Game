//This part is player.h
#ifndef _PLAYER_H
#define _PLAYER_H
 
#include "Framework\timer.h"
#include <vector>
using std::vector;
 

struct projectile
{
	projectile() //Constructor - Initializes, giving them default
	{
		pressing = false;  //Set the Pressing to be false at the start. It will change if spacebar is pressed.
	}
	    int xCoordinate;
		int yCoordinate;
        bool pressing; //Check if spacebar is pressed
        //bool ready; //check if player can fire a gun
        //int bulletcount; //Check number of bullets fired
		//You do no need bulletcount, don't try to keep track of bullets. You check if pressing = true -> check if it collided
		//and then you erase the vector. No need to use a variable for it. You use it and you let it go.
        //COORD bulletCoordinate; //Get coordinate of bullet
};
 


 
void bulletmovement(vector<projectile>& , COORD);
void abletoshootsatu(vector<projectile>&);
//void abletoshootdua(vector<projectile>&);
//void showbullet(short, short, vector<projectile>&);
void movebullet(vector<projectile>&);
void showBullet(vector<projectile>&);
#endif