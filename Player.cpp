#include "Player.h"
#include <ncurses.h>


Player::Player(int width, int height, int x_pos, int y_pos)
{
    this->height = height;
    this->width = width;
    this->X_pos = x_pos;
    this->Y_pos = y_pos;
}


void Player::draw()  
{   

    for (int i = 0; i < this->height;  i++) 
    {
        for (int j = 0; j < this->width; j++) 
        {
            mvprintw(this->Y_pos + i, this->X_pos + j, "#");
        }    
    
    }
    mvprintw(this->Y_pos - 1, this->X_pos + this->width/2-1, "/");
    mvprintw(this->Y_pos - 1, this->X_pos + this->width/2, "\\");
}

Bullet * Player::shoot()
{
    Bullet * bullet = new Bullet(this->Y_pos - 2, this->X_pos + this->width/2);

    return bullet;
}

Player::~Player()
 {

 }