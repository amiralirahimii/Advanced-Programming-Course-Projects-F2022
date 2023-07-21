#ifndef GAME_H
#define GAME_H

#include"rsdl.hpp"
#include"myShip.hpp"
#include"enemyShips.hpp"
#include"ships.hpp"
#include"bullet.hpp"
#include<vector>
#include<string>
#include<random>
#include<ctime>


const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const int NOT_ENDED = 3;
const int WIN = 2;
const int LOSE = 1;
const int QUIT = 0;
const int DELAY = 10;

const std::string BACKGROUND_PATH = "assests/background.jpg";

class Game{
public:
    Game(std::vector<Ship*> ships);
    int run();
private:
    Window* window;
    MyShip myship;
    std::vector<Ship> kidnapped_ships;
    std::vector<EnemyShip> enemy_ships;
    std::vector<Bullet> bullets;
    int end_game;
    void check_crash();
    void handle_key_press(Event);
    void handle_key_release(Event);
    void handle_events();
    void move_enemyships();
    void enemyships_shoot();
    void handle_bullets();
    void check_bullets_hits();
    void check_win();
    void update_game_status();
    void draw_on_window();
    void add_bullet(Bullet);
};
#endif