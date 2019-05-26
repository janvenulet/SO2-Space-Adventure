#include <ncurses.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <thread>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "mutex"
#include <algorithm>

int timeInterval = 5;
bool runningLoop = true;
int numberOfEnemies = 1; 
int windowX, windowY;
int mutexX = windowX/4;
int mutexY = windowY/2;

std::vector <std::thread> bulletsThreads;
std::vector <std::thread> enemiesThreads;

std::mutex mtx;

std::vector <Enemy *> enemies;
std::vector <Bullet *> bullets;	
Player * player;

void renderScreen()
{
	while (runningLoop)
	{
		clear();
        player->draw();

        mtx.lock();
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->getMissed()) continue; 
            mvprintw(bullets[i]->getY(), bullets[i]->getX(), "o");	
	    }
        mtx.unlock();

		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->draw();
	    }

		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
}

bool bulletShotSpaceship (Bullet * bullet, Spaceship * spaceship)
{
    if (spaceship->pointInside(bullet->getX(), bullet->getY()))
    {
        bullet->setMissed(true);
        return true;
    }
    else 
        return false;
}



void bulletThreadFunction(Bullet * bullet)
{
    bool collision = false;
    while (runningLoop && !collision)
    {
        if (bullet->hitWall()) break;
        //enemies.hit(bullet); warunek czy trafilo
		for (int i = 0; i < enemies.size(); i++)
		{
			collision = bulletShotSpaceship(bullet, enemies[i]);
	    }

        bullet->move();
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }
    // mtx.lock();
    // std::vector <Bullet *>::iterator it = std::find(bullets.begin(), bullets.end(), bullet);
    // bullets.erase(it);
    // mtx.unlock();
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
            mtx.lock();
            bullets.push_back(player->shoot());
            bulletId = bullets.size() -1;
            bulletsThreads.push_back(std::thread(bulletThreadFunction, bullets[bulletId]));
            mtx.unlock();
        }

    }
}

void enemyThreadFunction(Enemy * enemy)
{
    int nextMove = 1; 
    while (runningLoop)
    {
        if (enemy->getX() == 0 || enemy->getX() + enemy->getWidth()  == windowX - 1 ) nextMove *= -1; 
        enemy->move(nextMove,0);
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }
    
}

void generateEnemies()
{
    getmaxyx(stdscr, windowY, windowX);
	for (int i = 0 ; i < numberOfEnemies; i++) 
	{
		enemies.push_back(new Enemy(6, 3, windowX/2, windowY/3));
        //enemies.push_back(new Enemy());
		enemiesThreads.push_back(std::thread(enemyThreadFunction, enemies[i]));
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