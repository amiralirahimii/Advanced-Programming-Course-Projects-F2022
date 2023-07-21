#include"Driver.hh"

using namespace std;

Driver::Driver(string username)
:Person(username)
{
    
}

bool Driver::can_request(){
    return false;
}

bool Driver::can_see_trips_list(){
    return true;
}