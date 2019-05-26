#pragma once
#include "ncurses.h"

class Spaceship 
{
    protected:
        int height; 
        int width;
        int X_pos;
        int Y_pos;
        int healthPoints = 3; //ile razy musi zostac ustrzelony
        
    public:
        //void virtual draw(int, int);
        //void virtual draw();
        int getX() 
        {
            return X_pos;
        }

        int getY() 
        {
            return Y_pos;
        }

        int getHeight();
        int getWidth()
        {
            return width;
        };
        
        void move(int shiftX, int shiftY)
        {
            int screenX = getmaxx(stdscr);
            int tmp = X_pos + shiftX;
            if (! (tmp < 0 || tmp > screenX)) 
                X_pos += shiftX;
            Y_pos += shiftY;
        }

        bool pointInside(int x, int y) 
        {
            return ( ( x >= X_pos && x <= X_pos + width) && ( y >= Y_pos && y <= Y_pos + height) );
        }

        int getHealthPoint()
        {
            return healthPoints;
        }

        void gotShot() //zmniejsza hp
        {
            healthPoints -= 1; 
        } 

};