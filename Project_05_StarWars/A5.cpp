#include<iostream>
#include"game.hpp"
#include"getfile.hpp"
#include"show_win_lose.hpp"
#include<vector>
#include<string>

using namespace std;


int main(int argc, char** argv){
    vector<vector<Ship*>> ships;
    ships = getmap(argv[1]);
    for(int i=0 ; i<ships.size() ; i++){
        Game game(ships[i]);
        int game_status;
        game_status = game.run();

        if(game_status == WIN && i == ships.size()-1){
            show_w_l("WIN");
        }
        else if(game_status == WIN){
            delay(1000);
            continue;
        }
        else if(game_status == LOSE){
            show_w_l("LOSE");
            break;
        }
        else if(game_status == QUIT){
            break;
        }
    }
}