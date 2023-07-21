#include"Person.hh"

using namespace std;

Person::Person(string name_){
    name = name_;
    busy = false;
}

bool Person::is_equal(Person* per){
    if(per->name == name)
        return true;
    else
        return false;
}

bool Person::is_equal(string name_){
    if(name == name_)
        return true;
    else
        return false;
}

void Person::set_trip(){
    busy = true;
}

void Person::end_trip(){
    busy = false;
}