#ifndef BULLET_H
#define BULLET_H

#include"rsdl.hpp"
#include"ships.hpp"

const int ENEMYSHIP_BULLET_SPEED = 4;
const int MYSHIP_BULLET_SPEED = 7;
const int UP_B = 1;
const int DOWN_B = 2;
const int BULLET_SIZE = 4;

class Bullet{
public:
    Bullet(Point, int, int, int);
    bool check_in_window(Window* window);
    void move();
    void draw(Window*);
    bool check_hit_ship(Ship*);
private:
    Point point;
    int team;
    int speed;
    int moving_to;
};

#endif