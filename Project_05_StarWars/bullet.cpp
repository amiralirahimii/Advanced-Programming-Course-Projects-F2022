#include"bullet.hpp"

using namespace std;

Bullet::Bullet(Point point_, int team_, int speed_, int moving_to_){
    point = point_;
    team = team_;
    speed = speed_;
    moving_to = moving_to_;
}

bool Bullet::check_in_window(Window* window){
    if(moving_to == UP_B){
        if((point.y - speed) < LEFT_UP_WINDOW_COORDINATION){
            return false;
        }
    }
    else if(moving_to == DOWN_B){
        if((point.y + speed) > window->get_height()){
            return false;
        }
    }
    return true;
}

void Bullet::draw(Window* window){
    if(team == MYSHIP){
        window->fill_circle(point, BULLET_SIZE, WHITE);
    }
    else{
        window->fill_circle(point, BULLET_SIZE, RED);
    }
}

void Bullet::move(){
    if(moving_to == UP_B){
        point.y -= speed;
    }
    else if(moving_to == DOWN_B){
        point.y += speed;
    }
}

bool Bullet::check_hit_ship(Ship* ship){
    if(!ship->is_alive()){
        return false;
    }
    if(ship->is_point_in_me(point)){
        if(ship->bullet_can_hit(team)){
            return true;
        }  
    }
    return false;
}