#include "mainmenu.h"
#include "game.h"
#include "mainmenu.h"
#include "Framework\console.h"

void MainMenu()
{

	string Menu[4] = {"                                       PLAY", "                                    HIGHSCORES", "                                   INSTRUCTIONS", "                                       EXIT"}; // Variables in the Menu
	int pointer = 0;
	std::ifstream inData;
	string data;

	while(true)
	{
		system("cls");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		{																
			std::ifstream inData;								// Main Menu Header
			string data;
			inData.open ("Images/menuheader.txt"); 
			while (!inData.eof())
			{
				getline (inData, data);
				std::cout << data << std::endl;
			}
			inData.close();
		}

		std::cout << std::endl;

		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				std::cout << Menu[i] << std::endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				std::cout << Menu[i] << std::endl;
			}
		}

		while(true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)					// Up key input
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)			// Down key input
			{
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN))
			{
				switch (pointer)
				{
				case 0:
					{
						mainLoop();								// Brings player into game
					} break;
				case 1:
					{
						std::cout << std::endl;
						inData.open ("Images/highscore.txt");	// Brings player to highscore screen
						while (!inData.eof())
						{
							getline (inData, data);
							std::cout << data << std::endl;

						}
						system("pause");
						inData.close();	
						break;
					} 
				case 2:
					{
						std::cout << std::endl;

						inData.open ("Images/controls.txt"); 
						while (!inData.eof())
						{
							getline (inData, data);
							std::cout << data << std::endl;

						}
						system("pause");
						inData.close();
						break;
					}
				case 3:
					{
						exit(0);
					}
					break;
				}
				break;
			}
		}
		Sleep(150);
	}
}

void loseScreen()
{
	cls();
	std::ifstream inData;
	std::string data;

	inData.open ("Images/losescreen.txt"); 
	while (!inData.eof())
	{
		getline (inData, data);
		std::cout << data << std::endl;
	}
	inData.close();

	if (GetAsyncKeyState(VK_RETURN))
	{
		MainMenu();
	}

	Sleep(300);
}