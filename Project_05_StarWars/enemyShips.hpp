#ifndef ENEMYSHIPS_H
#define ENEMYSHIPS_H

#include"movingShips.hpp"
#include"bullet.hpp"
#include<random>
#include<ctime>
#include<string>

const int ENEMYSHIP_SPEED = 4;
const int STATIC_ENEMY = 0;
const std::string ENEMYSHIP_PATH = "assests/enemyship.png";
const int ENEMYSHIP_ROTATE_DEGREE = 180;
const int TIME_BETWEEN_SHOTS = 100000;

class EnemyShip : public MovingShip{
public:
    EnemyShip(int, int, int, int, int, int);
    bool can_shoot();
    Bullet shoot();
    void change_dir();
    void draw(Window*);
private:
    int team;
    clock_t last_shoot;
};

#endif