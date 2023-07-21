#ifndef HANDLER_HH
#define HANDLER_HH

#include"../server/server.hpp"
#include"UTaxi.hh"
#include<sstream>
#include<string>
#include<vector>

class SignUpHandler : public RequestHandler{
public:
    SignUpHandler(UTaxi* utaxi_);
    Response *callback(Request* req);
private:
    std::string set_page_as_before(Request* req);
    std::string show_success();
    std::string set_error_page(Request* req, Error err);
    std::string close_page(std::string body_p);
    UTaxi* utaxi;
};

class RequestCostHandler : public RequestHandler{
public:
    RequestCostHandler(UTaxi* utaxi_);
    Response *callback(Request* req);
private:
    std::string set_get_cost_response(Request* req, double cost);
    std::string set_page_as_before(Request* req);
    std::string set_error_page(Request* req, Error err);
    std::string show_trip_id(int id);
    std::string close_page(std::string);
    UTaxi *utaxi;
};

class DeleteHandler : public RequestHandler{
public:
    DeleteHandler(UTaxi* utaxi_);
    Response *callback(Request* req);
private:
    std::string set_page_as_before(Request* req);
    std::string show_success();
    std::string set_error_page(Request* req, Error err);
    std::string close_page(std::string body_p);
    UTaxi* utaxi;
};

class GetTripsHandler : public RequestHandler{
public:
    GetTripsHandler(UTaxi* utaxi_);
    Response *callback(Request* req);
private:
    std::string show_trips(std::vector<Trip*> trips, std::string username);
    std::string show_error(Error err);
    UTaxi* utaxi;
};

class AcceptHandler : public RequestHandler{
public:
    AcceptHandler(UTaxi *utaxi_);
    Response *callback(Request* req);
private:
    std::string show_success();
    std::string show_error(Error err);
    UTaxi* utaxi;
};

class FinishHandler : public RequestHandler{
public:
    FinishHandler(UTaxi *utaxi_);
    Response *callback(Request* req);
private:
    std::string show_success();
    std::string show_error(Error err);
    UTaxi *utaxi;
};

#endif