#ifndef MYSHIP_H
#define MYSHIP_H

#include"rsdl.hpp"
#include"movingShips.hpp"
#include"bullet.hpp"

#include<string>

const int MYSHIP_SPEED = 5;
const std::string MYSHIP_PATH = "assests/myship.png";
const int MYSHIP_ROTATE_DEGREE = 0;
const int MYSHIP_INIT_Y = 900;

class MyShip : public MovingShip{
public:
    MyShip();
    MyShip(int, int, int, int, int, int);
    Bullet shoot();
    void move_suit_release(Event);
    void draw(Window*);
protected:
};

#endif