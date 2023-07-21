#include"ships.hpp"

using namespace std;

Ship::Ship(int x_, int y_, int width_, int height_, int team_){
    x = x_;
    y = y_;
    width = width_;
    height = height_;
    team = team_;
    alive = true;
}

void Ship::draw(Window* window, string path, int degree){
    window->draw_img(path, Rectangle(x, y, width, height), NULL_RECT, degree);
}

bool Ship::is_point_in_me(Point point){
    if((x <= point.x) && (point.x <= x + width) && (y <= point.y) && (point.y <= y + height))
        return true;
    else
        return false;
}

bool Ship::check_crash(Ship* ship){
    if(!ship->is_alive()){
        return false;
    }
    vector<Point> points = {{x,y}, {x + width, y}, {x, y+ height} , {x + width, y + height}};
    for(int i=0 ; i<points.size() ; i++){
        if(ship->is_point_in_me(points[i])){
            return true;
        }
    }
    return false;
}

bool Ship::bullet_can_hit(int bullet_team){
    if(bullet_team == MYSHIP){
        if(team == ENEMY){
            return true;
        }
        else if(team == KIDNAP){
            return true;
        }
        else
            return false;
    }
    else if(bullet_team == ENEMY){
        if(team == MYSHIP){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}