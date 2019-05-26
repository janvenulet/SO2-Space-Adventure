#include "Enemy.h"

Enemy::Enemy(int width, int height, int x_pos, int y_pos)
{
    this->height = height;
    this->width = width;
    this->X_pos = x_pos;
    this->Y_pos = y_pos;
    this->groupId = 1;
}



void Enemy::draw()  
{   


    for (int i = 0; i < this->height;  i++) 
    {
        mvprintw(this->Y_pos + i, this->X_pos, "|");
        mvprintw(this->Y_pos + i, this->X_pos + this->width, "|");    
    }

    for (int j = 0; j <= this->width; j++) 
    {
        mvprintw(this->Y_pos, this->X_pos + j, "-");
        mvprintw(this->Y_pos + this->height, this->X_pos + j, "-");
    }
}

int Enemy::getGroupId()
{
    return this->groupId;
}