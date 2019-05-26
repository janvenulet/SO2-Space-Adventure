#include <ncurses.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <thread>
//#include "Enemy.h"
#include "Player.h"



//#define KEY_LEFT 75
//#define KEY_RIGHT 77


bool runningLoop = true; 
int windowX, windowY;
int mutexX = windowX/4;
int mutexY = windowY/2;
//std::vector <Enemy> enemies;	
Player * player;

void renderScreen()
{
	while (runningLoop)
	{
		clear();
        player->draw();

		// for (int i = 0; i < enemies.size(); i++)
		// {
		// 	mvprintw(balls[i]->getY(), balls[i]->getX(), "o");	
		// }
		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
}

void keyboardHandling()
{
    while (runningLoop)
    {
		char key = getchar();
		if (key == 13)
	    	runningLoop = false;
        if (key == 97)
            player->move(-1,0);
        if (key == 100)
            player->move(1,0);
        if (key == 32)
            
    }
}



int main(int argc, char const * argv [])
{
    srand (time(NULL));
	initscr();
	curs_set(0);

    getmaxyx(stdscr, windowY, windowX);
    mutexX = windowX/2.5;
    mutexY = windowY/1.05;
    
    player = new Player(10,2, mutexX, mutexY); 
    
    std::thread renderScreeenThread(renderScreen);
    std::thread keyboardHandlingThread(keyboardHandling);

    // getmaxyx(stdscr, windowY, windowX);	
	// int mutexX = windowX/4;
	// int mutexY = windowY/2;
	// mvaddstr(mutexY, mutexX, "__________");

    renderScreeenThread.join();
    keyboardHandlingThread.join();

    endwin();
    return 0; 
}