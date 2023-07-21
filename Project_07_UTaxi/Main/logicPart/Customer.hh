#ifndef CUSTOMER_HH
#define CUSTOMER_HH

#include"Person.hh"

class Customer : public Person{
public:
    Customer(std::string username);
    bool can_request();
    bool can_see_trips_list();
private:
    
};

#endif