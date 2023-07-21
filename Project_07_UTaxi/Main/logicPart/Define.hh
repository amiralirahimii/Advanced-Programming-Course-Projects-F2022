#ifndef DEFINE_HH
#define DEFINE_HH

#include<string>
#include"Coordination.hh"

class Trip;

const std::string BAD_REQUEST = "Bad Request";
const std::string NOT_FOUND = "Not Found";
const std::string PERMISSION_ISSUES = "Permission Denied";
const std::string SUCCESSFUL_CMD = "OK";
const std::string WAITING_MESSAGE = "waiting";
const std::string TRAVELING_MESSAGE = "traveling";
const std::string FINISHED_MESSAGE = "finished";
const std::string DRIVER_ROLE = "driver";
const std::string CUSTOMER_ROLE = "passenger";
const std::string EMPTY_TRIPS_LIST = "Empty";
const std::string POST_COMMAND = "POST";
const std::string GET_COMMAND = "GET";
const std::string DELETE_COMMAND = "DELETE";
const std::string SIGN_UP_COMMAND = "signup";
const std::string TRIPS_COMMAND = "trips";
const std::string ACCEPT_COMMAND = "accept";
const std::string FINISH_COMMAND = "finish";
const std::string COST_COMMAND = "cost";
const std::string USERNAME = "username";
const std::string ROLE = "role";
const std::string ORIGIN = "origin";
const std::string DESTINATION = "destination";
const std::string ID = "id";
const std::string IN_HURRY = "in_hurry";
const std::string SORT_BY_COST = "sort_by_cost";
const char WORD_SEPERATOR = ' ';
const char LOCATION_SEPERATOR = ',';

const int WAITING = 0;
const int TRAVELING = 1;
const int FINISHED = 2;

const int INITIAL_TRIP_ID = 1;
const int GET_COST_TRIP_ID = 0;
const double ONE_DEGREE_IN_KM = 110.5;
const double IN_HURRY_FACTOR = 1.2;
const int PRIMAL_PRICE = 10000;
const int NUMBER_OF_DECIMAL_PLACE_TO_PRINT = 2;

const int SIGN_UP = 7;
const int TRIPS = 8;
const int ACCEPT = 9;
const int FINISH = 10;
const int ALL_TRIPS = 11;
const int COST = 12;

const Coordination DEFAULT_COR = Coordination(0, 0);
#endif