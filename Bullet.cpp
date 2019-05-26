#include "Bullet.h"
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <iostream>


double gravity = 5.0;
double deltaTime = 0.2;


Bullet::Bullet(int x, int y)
{
    this->X = x;
    this->Y = y;
    int tmp = 0;
    //tmp = rand() % 9 - 5;
    //this->speedX = tmp;
    //tmp = rand() % 2 - 3;
    this->speedY = -1;
    this->missed = false;
}

bool Bullet::hitWall()
{
    int screenY = getmaxy(stdscr);
    bool missed = ( (this->Y < 0 || this->Y > screenY) ? true : false);
    return missed;
}


void Bullet::move()
{
    int screenX, screenY; 
    getmaxyx(stdscr, screenY, screenX);
    screenY--;
    
    if (this->X + speedX <= 0)
    {
        if (this->X + speedX == 0) 
                this->X=0;
        else 
                this->X = abs(this->X + speedX); // speed higher than discance
        speedX *= -1; 
    }
    else if (this->X + speedX >= screenX)
    {
        if (this->X + speedX == screenX)
                this->X=screenX-1;
        speedX *= -1; 
    }
    else
    {
        this->X += speedX; 
    }

    if (this->Y  <= 0 )
    {
        if (this->Y == 0) 
                this->Y=0;
        //else 
                //this->Y = abs(this->Y + speedY); // speed higher than discance
        speedY *= -1;
    }

    // else if ( this->Y == screenY) //surface friction
    // {
    //     speedX *= 0.8;
    //     if (abs(speedX) < 0.4)
    //             speedX = 0.0;
    // }

    if (this -> Y  > screenY - 1 ) 
    {
        this -> Y = screenY - 1;
        speedY *=  0.55;
        speedY *= -1;
        if (abs(speedY) < 6.00) 
            speedY *= 0.3; 
        if (abs(speedY) < 2.0) 
            this->Y = screenY; 
    }
    
    // if (this->getY() + speedY <= 0)
    // {
    //     if (this->getY() + speedY == 0) 
    //             this->Y=0;
    //     else 
    //             this->Y = abs(this->Y + speedY);
    //     speedY *= -1; 
    // }
    // else if (this->getY() + speedY >= screenY)
    // {
    //     if (this->getY() + speedY == 0)
    //             this->Y=0;
    //     else 
    //             this->Y= screenY - abs(screenY - (this->Y + speedY));
    //     speedY *= -1; 
    // }
    else 
    {
        this->Y += speedY;
    }
    return;
}

int Bullet::getX()
{
    return this->X;
}

int Bullet::getY()
{
    return this->Y;
}

bool Bullet::getMissed()
{
    return this->missed;
}

Bullet::~Bullet()
{}



