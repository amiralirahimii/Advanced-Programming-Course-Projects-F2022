#include"UTaxi.hh"

using namespace std;


UTaxi::UTaxi(string file_path){
    fstream FILE;
    FILE.open(file_path);
    string line;
    string line_to_ignore;
    getline(FILE, line_to_ignore);
    while(getline(FILE, line)){
        locations.push_back(new Location(line));
    }
    FILE.close();
    next_available_id = INITIAL_TRIP_ID;
}

bool UTaxi::check_user_existance(string username){
    for(int i=0 ; i<persons.size() ; i++){
        if(persons[i]->is_equal(username))
            return true;
    }
    return false;
}

void UTaxi::add_user(string username, string role){
    if(check_user_existance(username)){
        throw Error(BAD_REQUEST);
    }
    else{
        if(role == DRIVER_ROLE)
            persons.push_back(new Driver(username));
        else if(role == CUSTOMER_ROLE)
            persons.push_back(new Customer(username));
        else
            throw Error(BAD_REQUEST);
    }
}

void UTaxi::sign_up(string username, string role){
    try{
        add_user(username, role);
        success();
    }
    catch(Error& err){
        err.print_message();
        throw err;
    }
}

void UTaxi::success(){
    cout<<SUCCESSFUL_CMD<<endl;
}

Person* UTaxi::find_person_by_name(string username){
    for(int i=0 ; i<persons.size() ; i++){
        if(persons[i]->is_equal(username)){
            return persons[i];
        }
    }
    throw Error(NOT_FOUND);
}

Location* UTaxi::find_location_by_name(string name){
    for(int i=0 ; i<locations.size() ; i++){
        if(locations[i]->is_equal(name))
            return locations[i];
    }
    throw Error(NOT_FOUND);
}

Trip* UTaxi::find_trip_by_id(int trip_id){
    for(int i=0 ; i<trips.size() ; i++){
        if(trips[i]->is_equal(trip_id))
            return trips[i];
    }
    throw Error(NOT_FOUND);
}

int UTaxi::add_trip(Person* per, Location* org, Location* dest, bool in_hurry){
    if(per->is_busy())
        throw Error(BAD_REQUEST);
    else if(!per->can_request())
        throw Error(PERMISSION_ISSUES);
    Trip* new_trip = new Trip(per, org, dest, in_hurry, next_available_id);
    next_available_id++;
    trips.push_back(new_trip);
    per->set_trip();
    new_trip->print_id();
    return new_trip->get_id();
}

int UTaxi::req_trip(string username, string origin, string destination, bool in_hurry){
    try{
        Person* per = find_person_by_name(username);
        Location* org = find_location_by_name(origin);
        Location* dest = find_location_by_name(destination);
        int id = add_trip(per, org, dest, in_hurry);
        return id;
    }
    catch(Error& err){
        err.print_message();
        throw err;
    }
}

int UTaxi::find_max_trip_price_index(vector<Trip*> copy){
    int max_index = 0;
    for(int i=0 ; i<copy.size() ; i++){
        if(copy[i]->has_more_price_than(copy[max_index])){
            max_index = i;
        }
    }
    return max_index;
}

vector<Trip*> UTaxi::return_by_cost(){
    vector<Trip*> copy_of_trips = trips;
    vector<Trip*> result;
    for(int i=0 ; i<trips.size() ; i++){
        int index = find_max_trip_price_index(copy_of_trips);
        result.push_back(copy_of_trips[index]);
        copy_of_trips.erase(copy_of_trips.begin() + index);
    }
    return result;
}


vector<Trip*> UTaxi::return_trips(Person* per, bool sort_by_cost){
    if(!per->can_see_trips_list()){
        throw Error(PERMISSION_ISSUES);
    }
    if(trips.size() == 0){
        throw Error(EMPTY_TRIPS_LIST);
    }
    if(sort_by_cost){
        return return_by_cost();
    }
    else
        return trips;
}

vector<Trip*> UTaxi::get_trips(string username, bool sort_by_cost){
    try{
        Person* per = find_person_by_name(username);
        vector<Trip*> sorted_trips;
        sorted_trips = return_trips(per, sort_by_cost);
        return sorted_trips;
    }
    catch(Error& err){
        err.print_message();
        throw err;
    }
}

void UTaxi::print_trip(Person* per, Trip* trip){
    if(!per->can_see_trips_list()){
        throw Error(PERMISSION_ISSUES);
    }
    trip->print_trip();
}

void UTaxi::get_trip(string username, int trip_id){
    try{
        Person* per = find_person_by_name(username);
        Trip* trip = find_trip_by_id(trip_id);
        print_trip(per, trip);
    }
    catch(Error& err){
        err.print_message();
        throw err;
    }
}

void UTaxi::remove_from_list(Person* per, Trip* trip){
    if(!per->can_request()){
        throw Error(PERMISSION_ISSUES);
    }
    if(!trip->can_delete(per)){
        throw Error(PERMISSION_ISSUES);
    }
    if(!trip->is_deletable()){
        throw Error(BAD_REQUEST);
    }
    for(int i=0 ; i<trips.size() ; i++){
        if(trip->is_equal(trips[i])){
            delete trips[i];
            trips.erase(trips.begin() + i);
            per->end_trip();
        }
    }
}

void UTaxi::delete_trip(string username, int trip_id){
    try{
        Person* per = find_person_by_name(username);
        Trip* trip = find_trip_by_id(trip_id);
        remove_from_list(per, trip);
        success();
    }
    catch(Error& err){
        err.print_message();
        throw err;
    }
}

void UTaxi::accept_request(string username, int trip_id){
    try{
        Person* per = find_person_by_name(username);
        Trip* trip = find_trip_by_id(trip_id);
        trip->accept_request(per);
        success();
    }
    catch(Error& err){
        err.print_message();
        throw err;
    }
}

void UTaxi::end_trip(string username, int trip_id){
    try{
        Person* per = find_person_by_name(username);
        Trip* trip = find_trip_by_id(trip_id);
        trip->end_trip(per);
        success();
    }
    catch(Error& err){
        err.print_message();
        throw err;
    }
}



double UTaxi::get_cost(string username, string origin, string destination, bool in_hurry){
    try{
        Person* per = find_person_by_name(username);
        if(!per->can_request())
            throw Error(PERMISSION_ISSUES);
        Location* org = find_location_by_name(origin);
        Location* dest = find_location_by_name(destination);
        Trip temp__trip_to_calc_price(per, org, dest, in_hurry, GET_COST_TRIP_ID);
        temp__trip_to_calc_price.print_price();
        cout<<endl;
        return temp__trip_to_calc_price.get_cost();
    }
    catch(Error& err){
        err.print_message();
        throw err;
    }
}