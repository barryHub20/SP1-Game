#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <vector>
#include <string>

extern StopWatch g_timer;
extern bool g_quitGame;
using std::string;

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_SPACE,
    K_COUNT
};

void mainLoop();
void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

//player
struct user
{
	char direction;
	char front;
	char back;
	char left;
	char right;
	char body;
};


//score count
int score();
int highscore();
#endif // _GAME_H