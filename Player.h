#include "Spaceship.h"
#include "Bullet.h"

class Player : public Spacesphip
{
    private: 

    public:
        void draw();
        Bullet * shoot();
        

        Player(int, int, int, int);
       
        ~Player();
};