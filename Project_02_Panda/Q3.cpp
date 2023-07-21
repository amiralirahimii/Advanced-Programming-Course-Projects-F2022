#include<iostream>
#include<vector>
#include<string>

using namespace std;

struct Move{
    int row;
    int col;
};

const Move NONE={0 , 0};
const Move LEFT={0 , -1};
const Move RIGHT={0 , 1};
const Move UP={-1 , 0};
const Move DOWN={1 , 0};

struct Coordinate{
    int row;
    int col;
};

vector<string> get_input(){
    string readline;
    vector<string> input;
    while(cin >> readline){
        input.push_back(readline);
    }
    return input;
}

void initialize_panda_position(Coordinate& coordinate){
    coordinate.row=0;
    coordinate.col=0;
}

bool is_move_possible(vector<string> map,Move current_move, Coordinate panda_position){
    panda_position.col += current_move.col;
    panda_position.row += current_move.row;
    int board_row_size=map.size();
    int board_col_size=map[0].size();
    if(board_col_size-1 < panda_position.col|| board_row_size-1 < panda_position.row || panda_position.row<0 || panda_position.col<0 || map[panda_position.row][panda_position.col]== '#'){
        return false;
    }
    else {
        return true;
    }
}

Coordinate move_panda(Move current_move, Coordinate panda_position){
    panda_position.col += current_move.col;
    panda_position.row += current_move.row;
    return panda_position;
}

bool check_same_move(Move current_move, Coordinate panda_position ,vector<vector<string>>& move){
    if(current_move.col==DOWN.col && current_move.row==DOWN.row){
        for(int i=0;i<4;i++){
            if(move[i][panda_position.row][panda_position.col]=='d'){
                return true;
            }
        }
        for(int i=0;i<4;i++){
            if(move[i][panda_position.row][panda_position.col]=='n'){
                move[i][panda_position.row][panda_position.col]='d';
                return false;
            }
        }
    }
    if(current_move.col==LEFT.col && current_move.row==LEFT.row){
        for(int i=0;i<4;i++){
            if(move[i][panda_position.row][panda_position.col]=='l'){
                return true;
            }
        }
        for(int i=0;i<4;i++){
            if(move[i][panda_position.row][panda_position.col]=='n'){
                move[i][panda_position.row][panda_position.col]='l';
                return false;
            }
        }
    }
    if(current_move.col==UP.col && current_move.row==UP.row){
        for(int i=0;i<4;i++){
            if(move[i][panda_position.row][panda_position.col]=='u'){
                return true;
            }
        }
        for(int i=0;i<4;i++){
            if(move[i][panda_position.row][panda_position.col]=='n'){
                move[i][panda_position.row][panda_position.col]='u';
                return false;
            }
        }
    }
    if(current_move.col==RIGHT.col && current_move.row==RIGHT.row){
        for(int i=0;i<4;i++){
            if(move[i][panda_position.row][panda_position.col]=='r'){
                return true;
            }
        }
        for(int i=0;i<4;i++){
            if(move[i][panda_position.row][panda_position.col]=='n'){
                move[i][panda_position.row][panda_position.col]='r';
                return false;
            }
        }
    }
    return false;
}

void choose_next_move(vector<string> map,Move current_move, Coordinate panda_position ,int path_length ,vector<vector<string>> move ,vector<int>& calculated_path_length){
    if(current_move.col==NONE.col && current_move.row==NONE.row){
        if(is_move_possible(map ,DOWN ,panda_position)){
            current_move=DOWN;
            if(check_same_move(current_move, panda_position,move)){
                return;
            }
            Coordinate save_panda_position=panda_position;
            panda_position=move_panda(current_move, panda_position);
            path_length++;
            if(map[panda_position.row][panda_position.col]=='*'){
                calculated_path_length.push_back(path_length);
                return;
            }
            choose_next_move(map, current_move, panda_position, path_length, move ,calculated_path_length);
            panda_position=save_panda_position;
            path_length--;
        }
        if(is_move_possible(map ,RIGHT ,panda_position)){
            current_move=RIGHT;
            if(check_same_move(current_move, panda_position,move)){
                return;
            }
            Coordinate save_panda_position=panda_position;
            panda_position=move_panda(current_move, panda_position);
            path_length++;
            if(map[panda_position.row][panda_position.col]=='*'){
                calculated_path_length.push_back(path_length);
                return;
            }
            choose_next_move(map, current_move, panda_position, path_length, move ,calculated_path_length);
            panda_position=save_panda_position;
            path_length--;
        }
    }
    else if(is_move_possible(map, current_move ,panda_position)){
        if(check_same_move(current_move, panda_position,move)){
            return;
        }
        Coordinate save_panda_position=panda_position;
        panda_position=move_panda(current_move,panda_position);
        path_length++;
        if(map[panda_position.row][panda_position.col]=='*'){
            calculated_path_length.push_back(path_length);
            return;
        }
        choose_next_move(map, current_move, panda_position, path_length, move ,calculated_path_length);
        panda_position=save_panda_position;
        path_length--;
    }
    else{
        if(current_move.col==UP.col && current_move.row==UP.row){
            if(is_move_possible(map ,RIGHT ,panda_position)){
                current_move=RIGHT;
                if(check_same_move(current_move, panda_position,move)){
                    return;
                }
                Coordinate save_panda_position=panda_position;
                panda_position=move_panda(current_move, panda_position);
                path_length++;
                if(map[panda_position.row][panda_position.col]=='*'){
                    calculated_path_length.push_back(path_length);
                    return;
                }
                choose_next_move(map, current_move, panda_position, path_length, move ,calculated_path_length);
                panda_position=save_panda_position;
                path_length--;
            }
            if(is_move_possible(map ,LEFT ,panda_position)){
                current_move=LEFT;
                if(check_same_move(current_move, panda_position,move)){
                return;
                }
                Coordinate save_panda_position=panda_position;
                panda_position=move_panda(current_move, panda_position);
                path_length++;
                if(map[panda_position.row][panda_position.col]=='*'){
                    calculated_path_length.push_back(path_length);
                    return;
                }
                choose_next_move(map, current_move, panda_position, path_length, move ,calculated_path_length);
                panda_position=save_panda_position;
                path_length--;
            }
        }
        else if(current_move.col==LEFT.col && current_move.row==LEFT.row){
            if(is_move_possible(map ,UP ,panda_position)){
                current_move=UP;
                if(check_same_move(current_move, panda_position,move)){
                    return;
                }
                Coordinate save_panda_position=panda_position;
                panda_position=move_panda(current_move, panda_position);
                path_length++;
                if(map[panda_position.row][panda_position.col]=='*'){
                    calculated_path_length.push_back(path_length);
                    return;
                }
                choose_next_move(map, current_move, panda_position, path_length, move ,calculated_path_length);
                panda_position=save_panda_position;
                path_length--;
            }
            if(is_move_possible(map ,DOWN ,panda_position)){
                current_move=DOWN;
                if(check_same_move(current_move, panda_position,move)){
                    return;
                }
                Coordinate save_panda_position=panda_position;
                panda_position=move_panda(current_move, panda_position);
                path_length++;
                if(map[panda_position.row][panda_position.col]=='*'){
                    calculated_path_length.push_back(path_length);
                    return;
                }
                choose_next_move(map, current_move, panda_position, path_length, move ,calculated_path_length);
                panda_position=save_panda_position;
                path_length--;
            }
        }
        else if(current_move.col==DOWN.col && current_move.row==DOWN.row){
            if(is_move_possible(map ,LEFT ,panda_position)){
                current_move=LEFT;
                if(check_same_move(current_move, panda_position,move)){
                    return;
                }
                Coordinate save_panda_position=panda_position;
                panda_position=move_panda(current_move, panda_position);
                path_length++;
                if(map[panda_position.row][panda_position.col]=='*'){
                    calculated_path_length.push_back(path_length);
                    return;
                }
                choose_next_move(map, current_move, panda_position, path_length, move ,calculated_path_length);
                panda_position=save_panda_position;
                path_length--;
            }
            if(is_move_possible(map ,RIGHT ,panda_position)){
                current_move=RIGHT;
                if(check_same_move(current_move, panda_position,move)){
                    return;
                }
                Coordinate save_panda_position=panda_position;
                panda_position=move_panda(current_move, panda_position);
                path_length++;
                if(map[panda_position.row][panda_position.col]=='*'){
                    calculated_path_length.push_back(path_length);
                    return;
                }
                choose_next_move(map, current_move, panda_position, path_length, move ,calculated_path_length);
                panda_position=save_panda_position;
                path_length--;
            }
        }
        else if(current_move.col==RIGHT.col && current_move.row==RIGHT.row){
            if(is_move_possible(map ,DOWN ,panda_position)){
                current_move=DOWN;
                if(check_same_move(current_move, panda_position,move)){
                return;
                }
                Coordinate save_panda_position=panda_position;
                panda_position=move_panda(current_move, panda_position);
                path_length++;
                if(map[panda_position.row][panda_position.col]=='*'){
                    calculated_path_length.push_back(path_length);
                    return;
                }
                choose_next_move(map, current_move, panda_position, path_length, move ,calculated_path_length);
                panda_position=save_panda_position;
                path_length--;
            }
            if(is_move_possible(map ,UP ,panda_position)){
                current_move=UP;
                if(check_same_move(current_move, panda_position,move)){
                    return;
                }
                Coordinate save_panda_position=panda_position;
                panda_position=move_panda(current_move, panda_position);
                path_length++;
                if(map[panda_position.row][panda_position.col]=='*'){
                    calculated_path_length.push_back(path_length);
                    return;
                }
                choose_next_move(map, current_move, panda_position, path_length, move ,calculated_path_length);
                panda_position=save_panda_position;
                path_length--;
            }
        }
    }
    return;
}

int main(){
    vector<string> map;
    map = get_input();
    vector<vector<string>> move;
    for(int i=0;i<4;i++){
            move.push_back(map);
    }
    for(int i=0 ; i<4 ; i++){
        for(int j=0 ; j<map.size() ; j++){
            for(int k=0 ; k<map[0].size() ; k++){
                move[i][j][k]='n';
            }
        }
    }
    Coordinate panda_position;
    initialize_panda_position(panda_position);
    Move current_move=NONE;
    int path_length=0;
    vector<int> calculated_path_length;
    choose_next_move(map, current_move, panda_position, path_length ,move ,calculated_path_length);
    if(calculated_path_length.empty()){
        cout<<"No path found";
    }
    else{
        int minimum = calculated_path_length[0];
        for(int i=0;i<calculated_path_length.size();i++){
            if(calculated_path_length[i]<minimum){
                minimum=calculated_path_length[i];
            }
        }
        cout<<minimum;
    }
    return 0;
}