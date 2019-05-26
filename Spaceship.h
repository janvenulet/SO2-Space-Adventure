#pragma once
#include "ncurses.h"

class Spaceship 
{
    protected:
        int height; 
        int width;
        int X_pos;
        int Y_pos;
        
    public:
        //void virtual draw(int, int);
        //void virtual draw();
        int getX();
        int getY();
        int getHeight();
        int getWidth();
        
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


};