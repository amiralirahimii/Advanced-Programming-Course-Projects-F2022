#ifndef ERROR_HH
#define ERROR_HH

#include <string>
#include<iostream>

class Error{
public:
    Error(std::string message);
    void print_message();
    std::string what(){return error_message;}
private:
    std::string error_message;
};

#endif