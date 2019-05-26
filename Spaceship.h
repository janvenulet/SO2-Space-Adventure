#pragma once
class Spacesphip 
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
            X_pos += shiftX;
            Y_pos += shiftY;
        }

};