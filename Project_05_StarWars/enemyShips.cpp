#include"enemyShips.hpp"

using namespace std;

EnemyShip::EnemyShip(int x_, int y_, int width_, int height_, int speed_, int team_)
    :MovingShip(x_, y_, width_, height_, speed_, team_)
{
    if(speed == STATIC_ENEMY)
        moving_to = NOT_MOVING;
    else{
        srand(time(NULL));
        if(rand()%2)
            moving_to = RIGHT;
        else
            moving_to = LEFT;
    }
    last_shoot = clock();
}

void EnemyShip::change_dir(){
    if(moving_to == LEFT)
        moving_to = RIGHT;
    else
        moving_to = LEFT;
}

void EnemyShip::draw(Window* window){
    Ship::draw(window, ENEMYSHIP_PATH, ENEMYSHIP_ROTATE_DEGREE);
}

bool EnemyShip::can_shoot(){
    if(is_alive() && ((clock() - last_shoot) >= TIME_BETWEEN_SHOTS)){
        return true;
    }
    else
        return false;
}

Bullet EnemyShip::shoot(){
    last_shoot = clock();
    return Bullet(Point(x + width / 2, y + height), ENEMY, ENEMYSHIP_BULLET_SPEED, DOWN_B);
}