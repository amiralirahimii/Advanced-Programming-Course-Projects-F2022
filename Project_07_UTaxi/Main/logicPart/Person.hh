#ifndef PERSON_HH
#define PERSON_HH

#include<string>
#include"Define.hh"

class Person{
public:
    Person(std::string name_);
    bool is_equal(Person* per);
    bool is_equal(std::string name_);
    bool is_busy(){return busy; }
    void set_trip();
    void end_trip();
    std::string get_name(){return name; }
    virtual bool can_request() = 0;
    virtual bool can_see_trips_list() = 0;
private:
    std::string name;
    bool busy;
};

#endif