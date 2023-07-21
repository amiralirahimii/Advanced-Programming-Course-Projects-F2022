#ifndef TRIP_HH
#define TRIP_HH

#include<iostream>
#include<string>
#include"Location.hh"
#include"Driver.hh"
#include"Customer.hh"
#include"Define.hh"
#include"Error.hh"
#include<cmath>
#include <iomanip>

class Trip{
public:
    Trip(Person* per, Location* org, Location* dest, bool in_hurry_, int id_);
    void print_trip();
    bool is_equal(int trip_id);
    bool is_equal(Trip* trip);
    bool is_deletable();
    void print_id();
    bool can_delete(Person* per);
    void accept_request(Person* per);
    void end_trip(Person* per);
    void print_price();
    bool has_more_price_than(Trip* trip);
    double get_cost(){return price;}
    int get_id(){return id;}
    friend class GetTripsHandler;
private:
    double calculate_price(Location* org, Location* dest, bool in_hurry_);
    int id;
    Location* origin;
    Location* destination;
    Driver* driver;
    Customer* customer;
    int status;
    double price;
    bool in_hurry;
};
#endif