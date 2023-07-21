#ifndef UTAXI_HH
#define UTAXI_HH

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"Location.hh"
#include"Driver.hh"
#include"Customer.hh"
#include"Error.hh"
#include"Define.hh"
#include"Trip.hh"
#include"Coordination.hh"

class UTaxi{
public:
    UTaxi(std::string file_path);
    void run();
    void sign_up(std::string username, std::string role);
    int req_trip(std::string username, std::string origin, std::string destination, bool in_hurry);
    std::vector<Trip*> get_trips(std::string username, bool sort_by_cost);
    void get_trip(std::string username, int trip_id);
    void delete_trip(std::string username, int trip_id);
    void accept_request(std::string username, int trip_id);
    void end_trip(std::string username, int trip_id);
    double get_cost(std::string username, std::string origin, std::string destination, bool in_hurry);
private:
    bool check_user_existance(std::string username);
    void add_user(std::string username, std::string role);
    void success();
    int add_trip(Person* per, Location* org, Location* dest, bool in_hurry);
    void print_trip(Person* per, Trip* trip);
    int find_max_trip_price_index(std::vector<Trip*> copy);
    std::vector<Trip*> return_by_cost();
    std::vector<Trip*> return_trips(Person* per, bool sort_by_cost);
    void remove_from_list(Person* per, Trip* trip);
    int read_type(std::string line);
    Person* find_person_by_name(std::string username);
    Location* find_location_by_name(std::string name);
    Trip* find_trip_by_id(int trip_id);
    std::vector<Location*> locations;
    std::vector<Person*> persons;
    std::vector<Trip*> trips;
    int next_available_id;
};



#endif