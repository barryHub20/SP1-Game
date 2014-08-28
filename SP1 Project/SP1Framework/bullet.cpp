//This part is Player.cpp
#include "game.h"
#include "bullet.h"
#include "Framework\console.h"
#include <dos.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
using std::vector;
 
/*void bulletmovement(vector<projectile>& bullet, COORD consoleSize)
{
        abletoshootsatu(bullet); //Check if the player can shoot
 
        /*for (int c = 0; c < bullet.size(); c++)
        {
                if (bullet[c].bulletCoordinate.Y >= 0)//If bullet never touch screen keep moving up
                {
                        bullet[c].bulletCoordinate.Y--;
                }
                else if (bullet[c].bulletCoordinate.Y == 1)//If bullet touch screen maker it false to stop redndering it
                {
                        bullet[c].pressing = false;
                        //bullet[c].bulletcount -= 1;
                }
        }
}
 
void abletoshootsatu(vector<projectile>& bullet)
{
	for (int b = 0; b < bullet.size(); b++)
	{
		if (bullet[b].pressing = false)//Check if Spacebar is pressed
		{
			bullet[b].ready == true; //state how many bullet can player fire
		}
	}
}
 
void showbullet (short X, short Y, vector<projectile>& bullet)
{      
        //for (int c = 0; c < bullet.size(); c++)
        //{
	gotoXY(X,Y);
	std::cout << (char)94;
                        //bullet[c].bulletcount += 1;
        //}
}


//Step 1
This code will run if Spacebar is pressed, it will generate the bullet and put it inside the vector.

std::vector<projectile> Bullets; //This creates a vector that stores projectiles.
press space ->generate bullet -> true
void generateBullet()
{
projectile AddBullet; //Creates the projectile that will be addedd to the Bullets Vector above.
AddBullet.xCoordinate = charLocation.X;
AddBullet.yCoordinate = Y location of your character - 1; //Since it is higher, then starting y coordinate of it will be -1
AddBullet.pressing = true; //The Player has pressed it :D
Bullets.push_back(AddBullet); //Puts the AddBullet and the properties just set inside the vector
}*/


//Step 2
/*At this point, the bullet has been generated, but it needs to move now right :D*/

void moveBullet(vector<projectile>& bullet)
{
	for (int x = 0; x<bullet.size(); ++x) //Checks all Bullets inside the vector
	{
		if (bullet[x].pressing == true) //If it is pressed :D
		{
			//Bullets[x].xCoordinate will remain the same only y will change.
			bullet[x].yCoordinate -= 1;
		}
	}
}
//YEHEY!! NOW THE BULLETS WILL MOVE IF WE SENSE THAT IT HAS BEEN PRESSED/GENERATED


//Step 3
/* You will use this code in the Render Function. */

void showBullet(vector<projectile>& bullet)
{
	for (int x = 0; x< bullet.size(); x++)
	{
		if (bullet[x].pressing == true)
		{
			gotoXY(bullet[x].xCoordinate,bullet[x].yCoordinate);//Goes to your Bullet Location that has been shot
			std::cout<<" ";//Clears the Bullet Location to make sure that it doesnt overwrite anything
			std::cout << (char)94;//Prints the bullet at the location.
		}
	}
}
	