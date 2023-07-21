#include"game.hpp"

using namespace std;


Game::Game(vector<Ship*> ships)
{
    srand(time(NULL));
    int init_x = rand() % (WINDOW_WIDTH - SHIP_SIZE);
    myship = MyShip(init_x, MYSHIP_INIT_Y, SHIP_SIZE , SHIP_SIZE, MYSHIP_SPEED, MYSHIP);
    for(int i = 0 ; i<ships.size() ; i++){
        if(ships[i]->get_team() == ENEMY){
            EnemyShip* enemy = (EnemyShip*)(ships[i]);
            enemy_ships.push_back(*enemy);
        }
        else if(ships[i]->get_team() == KIDNAP){
            kidnapped_ships.push_back(*ships[i]);
        }
    }
    window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Game");
    end_game = NOT_ENDED;
}

int Game::run(){
    while(true){
        handle_events();
        update_game_status();
        if(end_game != NOT_ENDED){
            delete window;
            return end_game;
        }
        draw_on_window();
        window->update_screen();
        delay(DELAY);
    }
}

void Game::add_bullet(Bullet bullet){
    bullets.push_back(bullet);
}

void Game::handle_key_press(Event event){
    if(event.get_pressed_key() == 'd'){
        myship.set_moving_to(RIGHT);
    }
    else if(event.get_pressed_key() == 's'){
        myship.set_moving_to(DOWN);
    }
    else if(event.get_pressed_key() == 'a'){
        myship.set_moving_to(LEFT);
    }
    else if(event.get_pressed_key() == 'w'){
        myship.set_moving_to(UP);
    }
    else if(event.get_pressed_key() == ' '){
        add_bullet(myship.shoot());
    }
}

void Game::handle_key_release(Event event){
    myship.move_suit_release(event);
}

void Game::handle_events(){
    while(window->has_pending_event()){
        Event event = window->poll_for_event();
        switch(event.get_type()){
        case Event::EventType::KEY_PRESS:
            handle_key_press(event);
            break;
        case Event::EventType::KEY_RELEASE:
            handle_key_release(event);
            break;
        case Event::EventType::QUIT:
            end_game = QUIT;
            break;
        }
    }
}

void Game::check_crash(){
    for(int i=0 ; i<enemy_ships.size() ; i++){
        if(myship.check_crash(&enemy_ships[i]))
            end_game = LOSE;
    }
    for(int i=0 ; i<kidnapped_ships.size() ; i++){
        if(myship.check_crash(&kidnapped_ships[i]))
            end_game = LOSE;
    }
}

void Game::move_enemyships(){
for(int i=0 ; i<enemy_ships.size() ; i++){
        if(!enemy_ships[i].is_alive()){
            continue;
        }
        if(enemy_ships[i].stay_in_window(window))
            enemy_ships[i].move(window);
        else
            enemy_ships[i].change_dir();
    }
}

void Game::enemyships_shoot(){
    for(int i=0 ; i<enemy_ships.size() ; i++){
        if(enemy_ships[i].can_shoot()){
            bullets.push_back(enemy_ships[i].shoot());
        }
    }
}

void Game::handle_bullets(){
    for(int i=0 ; i<bullets.size() ; i++){
        if(!bullets[i].check_in_window(window)){
            bullets.erase(bullets.begin() + i);
        }
    }
    for(int i=0 ; i<bullets.size() ; i++){
        bullets[i].move();
    }
}

void Game::check_bullets_hits(){
    for(int i=0 ; i<bullets.size() ; i++){
        if(bullets[i].check_hit_ship(&myship)){
            end_game = LOSE;
        }
        for(int j=0 ; j<enemy_ships.size() ; j++){
            if(bullets[i].check_hit_ship(&enemy_ships[j])){
                bullets.erase(bullets.begin() + i);
                enemy_ships[j].die();
            }
        }
        for(int j=0 ; j<kidnapped_ships.size() ; j++){
            if(bullets[i].check_hit_ship(&kidnapped_ships[j])){
                end_game = LOSE;
            }
        }
    }
}

void Game::check_win(){
    bool won = true;
    for(int i = 0 ; i<enemy_ships.size() ; i++){
        if(enemy_ships[i].is_alive())
            won = false;
    }
    if(won == true){
        end_game = WIN;
    }
}

void Game::update_game_status(){
    myship.move(window);
    move_enemyships();
    enemyships_shoot();
    handle_bullets();
    check_bullets_hits();
    check_crash();
    check_win();
}

void Game::draw_on_window(){
    window->clear();
    window->draw_img(BACKGROUND_PATH);
    myship.draw(window);
    for(int i=0 ; i<enemy_ships.size() ; i++){
        if(enemy_ships[i].is_alive()){
            enemy_ships[i].draw(window);
        }
    }
    for(int i=0 ; i<kidnapped_ships.size() ; i++){
        kidnapped_ships[i].draw(window, KIDNAP_PATH, KIDNAP_ROTATE_DEGREE);
    }
    for(int i=0 ; i<bullets.size() ; i++){
        bullets[i].draw(window);
    }
}