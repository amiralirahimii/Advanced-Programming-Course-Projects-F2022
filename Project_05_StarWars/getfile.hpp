#ifndef GETFILE_H
#define GETFILE_H

#include"rsdl.hpp"
#include"ships.hpp"
#include"enemyShips.hpp"
#include<vector>
#include<string>
#include<fstream>

const int ZERO_ASCII_CODE = 48;
const int WINDOW_WIDTH_ = 1000;
const int WINDOW_HEIGHT_ = 1000;


Ship* char_to_ship(char c, int row, int col, int total_row, int total_col);
void find_numbers(std::fstream& FILE, int& row, int& col, int& num);
std::vector<Ship*> find_ships(std::fstream& FILE, int total_row, int total_col);
std::vector<std::vector<Ship*>> read_input(std::string file_path);
std::vector<std::vector<Ship*>> getmap(std::string file_path);


#endif