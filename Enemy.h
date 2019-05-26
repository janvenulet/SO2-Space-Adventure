#include "Spaceship.h"

class Enemy : public Spaceship 
{
    private:
        int groupId;
        int healthPoints;

    public:
        int getGroupId();
        void draw(); 

        
        Enemy(int, int, int, int);
        Enemy();
        ~Enemy();

};