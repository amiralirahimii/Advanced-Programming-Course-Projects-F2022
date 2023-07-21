#include"movingShips.hpp"

using namespace std;

MovingShip::MovingShip(int x_, int y_, int width_, int height_, int speed_,int team_)
    :Ship(x_, y_, width_, height_, team_)
{
    speed = speed_;
}

void MovingShip::set_moving_to(int dir){
    if(dir == RIGHT){
        moving_to = RIGHT;
    }
    else if(dir == LEFT){
        moving_to = LEFT;
    }
    else if(dir == UP){
        moving_to = UP;
    }
    else if(dir == DOWN){
        moving_to = DOWN;
    }
    else if(dir == NOT_MOVING){
        moving_to = NOT_MOVING;
    }
}


bool MovingShip::stay_in_window(Window* window){
    if(moving_to == RIGHT){
        if((x + width + speed) > window->get_width()){
            return false;
        }
        return true;
    }
    else if(moving_to == LEFT){
        if((x - speed) < LEFT_UP_WINDOW_COORDINATION){
            return false;
        }
        return true;
    }
    else if(moving_to == UP){
        if((y - speed) < LEFT_UP_WINDOW_COORDINATION){
            return false;
        }
        return true;
    }
    else if(moving_to == DOWN){
        if((y + height + speed) > window->get_height()){
            return false;
        }
        return true;
    }
    return false;
}


void MovingShip::move(Window* window){
    if(stay_in_window(window)){
        if(moving_to == RIGHT){
            x += speed;
        }
        else if(moving_to == LEFT){
            x -= speed;
        }
        else if(moving_to == UP){
            y -= speed;
        }
        else if(moving_to == DOWN){
            y += speed;
        }
    }
}
