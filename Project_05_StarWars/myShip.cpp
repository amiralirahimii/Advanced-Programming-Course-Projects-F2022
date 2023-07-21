#include"myShip.hpp"

using namespace std;

MyShip::MyShip()
    :MovingShip(0, 0, 0, 0, 0, 0)
{
    
}

MyShip::MyShip(int x_, int y_, int width_, int height_, int speed_, int team_)
    :MovingShip(x_, y_, width_, height_, speed_, team_)
{
    moving_to = NOT_MOVING;
}


Bullet MyShip::shoot(){
    return Bullet(Point(x + width / 2, y), MYSHIP, MYSHIP_BULLET_SPEED, UP_B);
}


void MyShip::move_suit_release(Event event){
    if(moving_to == RIGHT && event.get_pressed_key() == 'd'){
        moving_to = NOT_MOVING;
    }
    else if(moving_to == LEFT && event.get_pressed_key() == 'a'){
        moving_to = NOT_MOVING;
    }
    else if(moving_to == UP && event.get_pressed_key() == 'w'){
        moving_to = NOT_MOVING;
    }
    else if(moving_to == DOWN && event.get_pressed_key() == 's'){
        moving_to = NOT_MOVING;
    }
}


void MyShip::draw(Window* window){
    Ship::draw(window, MYSHIP_PATH, MYSHIP_ROTATE_DEGREE);
}