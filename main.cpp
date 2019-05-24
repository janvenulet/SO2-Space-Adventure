#include<ncurses.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <thread>
#include "Enemy.h"
#include "Player.h"



#define KEY_LEFT 75
#define KEY_RIGHT 77


bool runningLoop;
int windowX, windowY;
std::vector <Enemy> enemies;
Player player; 

void renderScreen()
{
	while (runningLoop)
	{
		clear();
        player.draw();
		// for (int i = 0; i < enemies.size(); i++)
		// {
		// 	mvprintw(balls[i]->getY(), balls[i]->getX(), "o");	
		// }
		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
}

void keyboardHandling()
{
    while (runningLoop)
    {
		char key = getch();
		if (key == '\n')
	    	runningLoop = false;
        if (key == KEY_LEFT)
            player.move(-1,0);
        if (key == KEY_RIGHT)
            player.move(1,0);
    }
}



int main(int argc, char const * argv [])
{
    srand (time(NULL));
	initscr();
	curs_set(0);

    std::thread renderScreeenThread(renderScreen);
    std::thread keyboardHandlingThread(keyboardHandling);

    renderScreeenThread.join();
    keyboardHandlingThread.join();


    return 0; 
}