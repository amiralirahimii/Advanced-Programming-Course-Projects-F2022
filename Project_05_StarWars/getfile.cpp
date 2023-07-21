#include"getfile.hpp"

using namespace std;

Ship* char_to_ship(char c, int row, int col, int total_row, int total_col){
    Ship* new_ship;
    if(c == 'E'){
        new_ship = new EnemyShip(col*(WINDOW_WIDTH_ / (total_col)), row*(WINDOW_HEIGHT_ / (total_row)) , SHIP_SIZE, SHIP_SIZE, STATIC_ENEMY, ENEMY);
    }
    else if(c == 'M'){
        new_ship = new EnemyShip(col*(WINDOW_WIDTH_ / (total_col)), row*(WINDOW_HEIGHT_ / (total_row)) , SHIP_SIZE, SHIP_SIZE, ENEMYSHIP_SPEED, ENEMY);
    }
    else if(c == 'S'){
        new_ship = new Ship(col*(WINDOW_WIDTH_ / (total_col)), row*(WINDOW_HEIGHT_ / (total_row)) , SHIP_SIZE, SHIP_SIZE, KIDNAP);
    }
    else{
        new_ship = NULL;
    }
    return new_ship;
}

vector<Ship*> find_ships(fstream& FILE, int total_row, int total_col){
    vector<Ship*> result;
    for(int i=0 ; i<total_row ; i++){
        string line;
        getline(FILE, line);
        for(int j = 0 ; j<total_col ; j++){
            Ship* check_NULL;
            check_NULL = char_to_ship(line[j], i, j, total_row, total_col);
            if(check_NULL == NULL){
                continue;
            }
            else{
                result.push_back(check_NULL);
            }
        }
    }
    return result;
}

void find_numbers(fstream& FILE, int& row, int& col, int& num){
    string line;
    getline(FILE, line);
    row = line[0] - ZERO_ASCII_CODE;
    col = line[2] - ZERO_ASCII_CODE;
    getline(FILE, line);
    num = line[0] - ZERO_ASCII_CODE;
}

vector<vector<Ship*>> read_input(string path){
    fstream FILE;
    FILE.open(path);
    int row, col, num;
    find_numbers(FILE, row, col, num);
    vector<vector<Ship*>> ships;
    for(int i=0 ; i<num ; i++){
        ships.push_back(find_ships(FILE, row, col));
        string trash_can;
        getline(FILE, trash_can);
        getline(FILE, trash_can);
    }
    return ships;
}

vector<vector<Ship*>> getmap(string file_path){
    vector<vector<Ship*>> ships;
    ships = read_input(file_path);
    return ships;
}