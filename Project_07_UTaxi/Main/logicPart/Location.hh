#ifndef LOCATION_HH
#define LOCATION_HH

#include<iostream>
#include<vector>
#include<string>
#include"Coordination.hh"
#include"Define.hh"

class Location{
public:
    Location(std::string n, Coordination c, int t);
    Location(std::string line);
    bool is_equal(std::string n);
    std::string get_name(){return name;}
    double calculate_price_to(Location* loc);
private:
    std::string name;
    Coordination coordination;
    int traffic;
};

#endif