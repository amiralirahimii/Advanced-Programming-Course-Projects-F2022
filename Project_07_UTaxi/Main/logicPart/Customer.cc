#include"Customer.hh"

using namespace std;

Customer::Customer(string username)
:Person(username)
{

}

bool Customer::can_request(){
    return true;
}

bool Customer::can_see_trips_list(){
    return false;
}