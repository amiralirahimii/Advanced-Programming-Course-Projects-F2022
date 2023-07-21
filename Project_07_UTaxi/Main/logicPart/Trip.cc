#include"Trip.hh"

using namespace std;

double Trip::calculate_price(Location* org, Location* dest, bool in_hurry_){
    double price = org->calculate_price_to(dest);
    if(in_hurry)
        return price * IN_HURRY_FACTOR;
    else
        return price;
}

Trip::Trip(Person* per, Location* org, Location* dest, bool in_hurry_, int id_){
    driver = NULL;
    origin = org;
    destination = dest;
    customer = (Customer*) per;
    status = WAITING;
    id = id_;
    in_hurry = in_hurry_;
    price = calculate_price(org, dest, in_hurry_);
}

void Trip::print_trip(){
    cout<<id<<WORD_SEPERATOR<<customer->get_name()<<WORD_SEPERATOR<<origin->get_name()<<WORD_SEPERATOR<<destination->get_name()<<WORD_SEPERATOR;
    print_price();
    cout<<WORD_SEPERATOR;
    if(status == WAITING){
        cout<<WAITING_MESSAGE;
    }
    else if(status == TRAVELING){
        cout<<TRAVELING_MESSAGE;
    }
    else{
        cout<<FINISHED_MESSAGE;
    }
    cout<<endl;
}

bool Trip::is_equal(int trip_id){
    if(id == trip_id)
        return true;
    else
        return false;
}

bool Trip::is_equal(Trip* trip){
    if(trip->id == id)
        return true;
    else
        return false;
}

bool Trip::is_deletable(){
    if(status == WAITING)
        return true;
    else
        return false;
}

bool Trip::can_delete(Person* per){
    if(per->is_equal(customer))
        return true;
    else
        return false;
}

void Trip::print_id(){
    cout<<id<<endl;
}

void Trip::accept_request(Person* per){
    if(per->can_request()){
        throw Error(PERMISSION_ISSUES);
    }
    if(per->is_busy()){
        throw Error(BAD_REQUEST);
    }
    if(status != WAITING){
        throw Error(BAD_REQUEST);
    }
    status = TRAVELING;
    driver = (Driver*) per;
    per->set_trip();
}

void Trip::end_trip(Person* per){
    if(per->can_request()){
        throw Error(PERMISSION_ISSUES);
    }
    if(status != TRAVELING){
        throw Error(BAD_REQUEST);
    }
    if(!driver->is_equal(per)){
        throw Error(BAD_REQUEST);
    }
    status = FINISHED;
    driver->end_trip();
    customer->end_trip();
}

void Trip::print_price(){
    double decimal_number = price;
    int integer_part = (int)decimal_number;
    double decimal_part = decimal_number - integer_part;
    double decimal_needed_part = decimal_part * pow(10 , NUMBER_OF_DECIMAL_PLACE_TO_PRINT);
    decimal_needed_part = (double)(int) decimal_needed_part;
    decimal_needed_part /= pow(10 , NUMBER_OF_DECIMAL_PLACE_TO_PRINT);
    double result = integer_part + decimal_needed_part;
    cout<<fixed<<setprecision(NUMBER_OF_DECIMAL_PLACE_TO_PRINT)<<result;
}

bool Trip::has_more_price_than(Trip* trip){
    if(price > trip->price)
        return true;
    else if((price == trip->price) && id < trip->id)
        return true;
    else
        return false;
}
