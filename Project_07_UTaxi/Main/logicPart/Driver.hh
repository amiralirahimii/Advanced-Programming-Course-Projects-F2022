#ifndef DRIVER_HH
#define DRIVER_HH

#include"Person.hh"

class Driver : public Person{
public:
    Driver(std::string username);
    bool can_request();
    bool can_see_trips_list();
private:
    
};

#endif