#include <ncurses.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <thread>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"


int timeInterval = 5;
bool runningLoop = true;
int numberOfEnemies = 1; 
int windowX, windowY;
int mutexX = windowX/4;
int mutexY = windowY/2;

std::vector <std::thread> bulletsThreads;
std::vector <std::thread> enemiesThreads;

std::vector <Enemy *> enemies;
std::vector <Bullet *> bullets;	
Player * player;

void renderScreen()
{
	while (runningLoop)
	{
		clear();
        player->draw();

		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->getMissed()) continue; 
            mvprintw(bullets[i]->getY(), bullets[i]->getX(), "o");	
	    }

		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->draw();
	    }
		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
}


void bulletThreadFunction(int bulletId)
{
    bool collision = false;
    while (runningLoop && !collision)
    {
        if (bullets[bulletId]->hitWall()) break;
        //enemies.hit(bullet); warunek czy trafilo
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->pointInside(bullets[bulletId]->getX(), bullets[bulletId]->getY()))
            {
                bullets[bulletId]->setMissed(true);
                collision= true;
            }
	    }
        
        bullets[bulletId]->move();
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }
}

void keyboardHandling()
{
    int bulletId = 0;
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
        {
            bullets.push_back(player->shoot());
            bulletsThreads.push_back(std::thread(bulletThreadFunction, bulletId));
            bulletId++; 
        }

    }
}

void enemyThreadFunction()
{
    //movement of enemy
}

void generateEnemies()
{
    getmaxyx(stdscr, windowY, windowX);
	for (int i = 0 ; i < numberOfEnemies; i++) 
	{
		enemies.push_back(new Enemy(6, 3, windowX/2, windowY/3));
        //enemies.push_back(new Enemy());
		//enemiesThreads.push_back(std::thread(enemyThreadFunction, i));
		if (!runningLoop) break;
		//    std::this_thread::sleep_for(std::chrono::milliseconds(timeInterval));
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
    std::thread generateEnemiesThread(generateEnemies);

    renderScreeenThread.join();
    keyboardHandlingThread.join();
    generateEnemiesThread.join();

    for (int i = 0; i < bulletsThreads.size(); i++)
    {
        bulletsThreads[i].join();
    }

    for (int i = 0; i < enemiesThreads.size(); i++)
    {
        enemiesThreads[i].join();
    }

    endwin();
    return 0; 
}