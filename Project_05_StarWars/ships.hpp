#ifndef SHIPS_H
#define SHIPS_H

#include"rsdl.hpp"
#include<vector>
#include<string>

const int LEFT_UP_WINDOW_COORDINATION = 0;
const int SHIP_SIZE = 100;
const int MYSHIP = 1;
const int ENEMY = 2;
const int KIDNAP = 3;
const std::string KIDNAP_PATH = "assests/kidnapship.png";
const int KIDNAP_ROTATE_DEGREE = 0;

class Ship{
public:
    Ship(int, int, int, int, int);
    virtual void draw(Window*, std::string, int);
    bool check_crash(Ship*);
    bool is_point_in_me(Point);
    bool bullet_can_hit(int);
    bool is_alive(){return alive; }
    int get_team(){return team; }
    int get_x(){return x;}
    int get_y(){return y;}
    void die(){
        if(is_alive()){alive = false;}
    }
protected:
    int x;
    int y;
    int width;
    int height;
    int team;
    bool alive;
};

#endif