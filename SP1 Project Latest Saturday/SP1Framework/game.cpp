// This is the main file for the game logic and function
//
//
#include "powerUp.h"
#include "game.h"
#include "bullet.h"
#include "playerZone.h"
#include "Framework\console.h"
#include "enemy.h"
#include "mainmenu.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "mainmenu.h"
#include "wall.h"

double elapsedTime;
double deltaTime;
double velocity = 0.5;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;
COORD playerDirection;
int enemySize = 8;
int points;
int waveCounter;
vector<enemy> unit(enemySize);
double gapPlayer;
double playerbullet;
double EnemyBullet;
double EnemyGap;
zone playerZone;
int ammoSize = 40;
int bulletCounter;
double bulletSpeed;
double fireRate;
double reload;
vector<projectile> ak47(ammoSize);

void init()
{
	srand (time(NULL));//random seed generator
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"no name");

    // Sets the console size, this is the biggest so far.
    setConsoleSize(80, 45);//original: X 79  Y 28

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = consoleSize.X / 2;
    charLocation.Y = consoleSize.Y - 1;

    elapsedTime = 0.0;

	points = 20;
	enemySize = 8;
	playerZone.Y = 30;
	waveCounter = 0;
	bulletCounter = 0;
	bulletSpeed = 3;
	fireRate = 0.5;
	reload = 0;
	//initialize enemy unit spawn points first time round (total of 7 enemy units), read from text file
	//set all enemy units to true first time round
	for(int i=0; i<enemySize; ++i)
	{
		unit[i].active = false;
		unit[i].spawnLocation.Y = -1;//each unit Y is -1 to hide it from the top of the map when at spawn waiting to be deployed
		unit[i].location.Y = unit[i].spawnLocation.Y;
		unit[i].mobile = true;
		unit[i].time = 0;
		//set 15 target points for each unit
		for(int j=0; j<points; ++j)
		{
			unit[i].point.push_back(charLocation);//push in char location to populate vector first
		}
	}

	//set the spawn location for now
	unit[0].spawnLocation.X = 5;
	unit[1].spawnLocation.X = 25;
	unit[2].spawnLocation.X = 45;
	unit[3].spawnLocation.X = 65;
	unit[4].spawnLocation.X = 15;
	unit[5].spawnLocation.X = 35;
	unit[6].spawnLocation.X = 55;
	unit[7].spawnLocation.X = 75;

	for(int i=0; i<enemySize; ++i)
	{
		unit[i].location.X = unit[i].spawnLocation.X;
		unit[i].count = 0;//set counter to 0
	}

	//preset target location
	targetPoint(unit, points, consoleSize);

	//set number of ammo per shot
	/**
	//initialize the timer for buffs
	powerupBullet.timer = 0.0;
	healthPack.timer = 0.0;
	**/

}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
}

void update(double dt)
{

	// timer for buffs
	powerupBullet.timer += dt;
	
   // get the delta time
    elapsedTime += dt;
    deltaTime = dt;
	gapPlayer += dt;
	playerbullet += dt;
	EnemyBullet += dt;
	EnemyGap += dt;

    // Updating the location of the character based on the key press
  if (keyPressed[K_LEFT] && charLocation.X > 1)
    {
        charLocation.X-=3;
    }

    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 4)
    {
        charLocation.X+=3;
    }
 
	//player direction
    if (keyPressed[K_LEFT] && playerDirection.X >= 0)
    {
		playerDirection.X = charLocation.X - 1;
		playerDirection.Y = charLocation.Y;
    }
    else if (keyPressed[K_DOWN] && playerDirection.Y < consoleSize.Y - 1)
    {
        playerDirection.X = charLocation.X - 1;
		playerDirection.Y = charLocation.Y;
    }
    else if (keyPressed[K_RIGHT] && playerDirection.X < consoleSize.X - 1)
    {
		playerDirection.X = charLocation.X + 1;
		playerDirection.Y = charLocation.Y;
    }
    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true; 

	if((int)elapsedTime % 999 == 0)
	{
	for(int a = 0; a < MAXWALL; a++) //load the walls FIRST
		{

			thewall[a].loadwall();	

		}
		for(int a = 0; a < MAXWALL; a++)// check the wall coordinates
		{
			for(int b = 0; b < MAXWALL; b++)
			{
				if(a != b)
				{
					if((thewall[a].x - thewall[b].x < 5) && (thewall[a].x - thewall[b].x > -5) )//if they are overlapping
					{
						thewall[b].loadwall();//re-random
						a = 0;
						b = 0;
					}
				}
			}
		}
	}

	//health();

	//powerup();

	//fires and updates bullets
	if(reload < fireRate)
	{
		reload += deltaTime;
	}


	if (keyPressed[K_SPACE])//Player Presses Space
	{
		if(bulletCounter == ammoSize - 1)
		{
			bulletCounter = 0;//reset back to 0, by now bullet 0 has hit target
		}

		if(reload >= fireRate)
		{
			ak47[bulletCounter].active = true;
			ak47[bulletCounter].location.X = charLocation.X;
			ak47[bulletCounter].location.Y = charLocation.Y;
			++bulletCounter;
		}
		
		if(reload == fireRate)
		{
			reload = 0;
		}
		else if(reload > fireRate)
		{
			reload -= fireRate;
		}
	}

	//updates active bullet location
	bulletActive(ak47, ammoSize, bulletSpeed, deltaTime);

	//updates enemy movement, parameter is enemy unit, double elapsedTime, COORD consoleSize
	enemyMovement(unit, elapsedTime, consoleSize, enemySize, points, waveCounter, velocity, deltaTime);

	//checks if touched player zone
	ifTouched(deltaTime, playerZone, unit);
}

void render()
{
     // clear previous screen
    colour(0x0F);
	cls();

    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0/deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

	// score appearing on screen
	gotoXY(60, 0);
	colour(0xffffff00);
	std::cout << "Score: " << score() << " ";

	for (int i = 0; i < MAXWALL; i++)
	{
		thewall[i].renderwall();
	}

	
	//player character
	gotoXY(charLocation);
    colour(0x0C);
	user player ;//Player direction
	player.front = (char)192;
	player.back = (char)191;
	player.left = (char)170;
	player.right = (char)169;
	player.body =(char)233;

    gotoXY(charLocation);
    colour(0x0C);
	std::cout << player.body;

	if (GetAsyncKeyState(VK_LEFT) != 0)
	{
		gotoXY(playerDirection);
		std::cout << player.left;
	}
        else if (GetAsyncKeyState(VK_RIGHT) != 0)
        {
                gotoXY(playerDirection);
                std::cout << player.right;
        }
        else if (GetAsyncKeyState(VK_UP) == 0 || GetAsyncKeyState(VK_UP) != 0)//by default face up
        {
                std::cout << player.front;
        }

	
    //render the game
	for(int i=0; i<enemySize; ++i)
	{
		//psss in the X and Y coor. of each unit
		if(unit[i].active == true && unit[i].location.Y != -1)//do not display waiting characters
		{
			printEnemy(unit[i].location);
		}
	}	

	for(int i=0; i<ammoSize; ++i)
	{
		if(ak47[i].active == true)
		{
			printBullet(ak47[i].location);
		}
	}
	//printPowerUp();


	//printHealth();
}


int score()
{
	int currentscore = 0;
	int points = 10;

	//while (g_quitGame !=true)
	//{
	//	if (insert bullet hitting enemy function here)
	//	{
	//		 score += points;
	//	}
	//	std::cout << "Score: " << currentscore << " ";
	//}

	return currentscore;
}

int highscore()
{
	std::string data;
	int a;
	int b = score();
	int higherscore;

	std::ifstream inData;
	inData.open ("Images/highscore.txt");
	inData >> a;

	if (a > b)
	{
		higherscore = a;
	}
	else
	{
		higherscore = b;
	}

	std::ofstream highscore;
	highscore.open ("Images/highscore.txt");
	highscore << higherscore;
	highscore.close();
	return 0;
}
