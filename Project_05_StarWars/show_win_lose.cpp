#include"show_win_lose.hpp"

using namespace std;

void show_w_l(string game_status){
    if(game_status == "WIN"){
        cout<<"Congratulations, U Won"<<endl;
    }
    else if(game_status == "LOSE"){
        cout<<"Heh, Try Again"<<endl;
    }
}