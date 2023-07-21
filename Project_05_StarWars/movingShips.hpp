#ifndef MOVINGSHIP_H
#define MOVINGSHIP_H

#include"rsdl.hpp"
#include "ships.hpp"

const int NOT_MOVING = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;
const int UP = 4;

class MovingShip : public Ship{
public:
    MovingShip(int, int, int, int, int, int);
    void set_moving_to(int dir);
    void move(Window*);
    bool stay_in_window(Window*);
protected:
    int speed;
    int moving_to;
};


#endif