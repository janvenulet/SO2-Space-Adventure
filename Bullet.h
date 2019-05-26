#pragma once 
class Bullet 
{
    private:
        int X;
        int Y; 
        double speedX;
        double speedY;
    public:
        Bullet(int,int);
        ~Bullet();
        void move();
        void bounce();
        int getX();
        int getY();
};