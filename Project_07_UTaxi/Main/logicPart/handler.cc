#include"handler.hh"

using namespace std;

SignUpHandler::SignUpHandler(UTaxi* utaxi_){
    utaxi= utaxi_;
}

string SignUpHandler::close_page(string body_p){
    ostringstream body;
    body<<body_p;
    body<<"</body>";
    body<<"</html>";
    return body.str();
}

string SignUpHandler::set_page_as_before(Request* req){
    ostringstream body;
    body<<"<!DOCTYPE html><html><title>Sign Up</title><body><form action='/signup' method='post'><p><input type='text' name='username' value='";
    body<<req->getBodyParam("username")<<"'>";
    body<<"</p><input type='radio' id='driver' name='role' value='driver'";
    if(req->getBodyParam("role") == "driver")
        body<<" checked>"<<endl;
    else
        body<<">"<<endl;
    body<<"<label for='driver'>Driver</label>";
    body<<"<input type='radio' id='passenger' name='role' value='passenger'";
    if(req->getBodyParam("role") == "passenger")
        body<<" checked>"<<endl;
    else
        body<<">"<<endl;
    body<<"<label for='passenger'>Passenger</label><p><input type='submit' formtarget='_self' value='submit'></p></form><p><a href='/'>";
    body<<"<input type='button'  value='Back'></a></p>";
    return body.str();
}

string SignUpHandler::show_success(){
    ostringstream body;
    body<<"<!DOCTYPE html>"<<endl<<"<html>"<<endl<<"<title>Request</title>"<<endl<<"<body>"<<endl;
    body<<"<script>";
    body<<"alert('OK');";
    body<<"window.location.href = '/';";
    body<<"</script>";
    return close_page(body.str());
}

string SignUpHandler::set_error_page(Request* req, Error err){
    ostringstream body;
    body<< set_page_as_before(req);
    body<<"<script>";
    body<<"alert('";
    body<<err.what();
    body<<"');";
    body<<"</script>";
    return close_page(body.str());
}

Response *SignUpHandler::callback(Request* req){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    try{
        utaxi->sign_up(req->getBodyParam("username"), req->getBodyParam("role"));
        res->setBody(show_success());
    }
    catch(Error err){
        res->setBody(set_error_page(req, err));
    }
    return res;
}

RequestCostHandler::RequestCostHandler(UTaxi* utaxi_){
    utaxi= utaxi_;
}

string RequestCostHandler::set_page_as_before(Request* req){
    ostringstream body;
    body<<"<!DOCTYPE html>"<<endl<<"<html>"<<endl<<"<title>Request</title>"<<endl<<"<body>"<<endl;
    body<<"<form action='/requestCost' method='post'>"<<endl;
    body<<"<p>"<<endl<<"<label for='username'>Username:</label>"<<endl<<"<input type='text' name='username' id='username' value='"
        <<req->getBodyParam("username")<<"'>"<<endl<<"</p>";

    body<<"<p>"<<endl<<"<label for='origin'>Origin:</label>"<<endl<<"<input type='text' name='origin' id='origin' value='"
        <<req->getBodyParam("origin")<<"'>"<<endl<<"</p>"<<endl;

    body<<"<p>"<<endl<<"<label for='destination'>Destination:</label>"<<endl<<"<input type='text' name='destination' id='destination'value='"
        <<req->getBodyParam("destination")<<"'>"<<endl<<"</p>"<<endl;

    body<<"<p>"<<endl<<"Is Request In Hurry?<br>"<<endl<<"<input type='radio' id='yes' name='in_hurry' value='yes'";
    if(req->getBodyParam("in_hurry") == "yes")
        body<<" checked>"<<endl;
    else
        body<<">"<<endl;

    body<<"<label for='yes'>Yes</label>"<<endl;
    body<<"<input type='radio' id='no' name='in_hurry' value='no'";
    if(req->getBodyParam("in_hurry") == "no")
        body<<" checked>"<<endl;
    else
        body<<">"<<endl;
    body<<"<label for='no'>No</label>"<<endl<<"</p>"<<"<br>";

    body<<"<input type='radio' id='get_cost' name='request' value='get_cost'";
    if(req->getBodyParam("request") == "get_cost")
        body<<" checked>"<<endl;
    else
        body<<">"<<endl;
    body<<"<label for='get_cost'>Calculate Cost</label>"<<endl;

    body<<"<input type='radio' id='req_trip' name='request' value='req_trip'";
    if(req->getBodyParam("request") == "req_trip")
        body<<" checked>"<<endl;
    else
        body<<">"<<endl;
    body<<"<label for='req_trip'>Request Trip</label>"<<endl;
    body<<"<p>"<<endl<<"<input type='submit' formtarget='_self' value='submit'>"<<endl<<"</p>"<<endl<<"</form>";
    body<<"<p>"<<endl<<"<a href='/passengerPage'>"<<endl<<"<input type='button'  value='Back'>"<<endl<<"</a>"<<endl<<"</p>";
    return body.str();
}

string RequestCostHandler::set_get_cost_response(Request* req, double cost){
    ostringstream body;
    body<< set_page_as_before(req);
    body<<"<script>";
    body<<"alert('The Trip Cost Is:  ";
    body<<cost<<"');";
    body<<"</script>";
    return close_page(body.str());
}

string RequestCostHandler::set_error_page(Request* req, Error err){
    ostringstream body;
    body<< set_page_as_before(req);
    body<<"<script>";
    body<<"alert('";
    body<<err.what();
    body<<"');";
    body<<"</script>";
    return close_page(body.str());
}

string RequestCostHandler::show_trip_id(int id){
    ostringstream body;
    body<<"<!DOCTYPE html>"<<endl<<"<html>"<<endl<<"<title>Request</title>"<<endl<<"<body>"<<endl;
    body<<"<script>";
    body<<"alert('Your Trip Id Is:   ";
    body<<id;
    body<<"');";
    body<<"window.location.href = '/';";
    body<<"</script>";
    return close_page(body.str());
}

string RequestCostHandler::close_page(string body_p){
    ostringstream body;
    body<<body_p;
    body<<"</body>";
    body<<"</html>";
    return body.str();
}

Response *RequestCostHandler::callback(Request* req){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    try{
        bool in_hurry=false;
        if(req->getBodyParam("in_hurry") == "yes")
            in_hurry=true;
        else if(req->getBodyParam("in_hurry") == "no")
            in_hurry=false;
        if(req->getBodyParam("request") == "get_cost"){
            double cost;
            cost = utaxi->get_cost(req->getBodyParam("username"), req->getBodyParam("origin"), req->getBodyParam("destination"), in_hurry);
            res->setBody(set_get_cost_response(req, cost));
        }
        else if(req->getBodyParam("request") == "req_trip"){
            int id;
            id = utaxi->req_trip(req->getBodyParam("username"), req->getBodyParam("origin"), req->getBodyParam("destination"), in_hurry);
            res->setBody(show_trip_id(id));
        }
        else{
            throw Error(NOT_FOUND);
        }
    }
    catch(Error error){
        res->setBody(set_error_page(req, error));
    }
    return res;
}

string DeleteHandler::close_page(string body_p){
    ostringstream body;
    body<<body_p;
    body<<"</body>";
    body<<"</html>";
    return body.str();
}

string DeleteHandler::set_page_as_before(Request* req){
    ostringstream body;
    body<<"<!DOCTYPE html><html><title>Sign Up</title><body><form action='/delete' method='post'>";
    body<<"<p><label for='username'>Username: </label>";
    body<<"<input type='text' name='username' value='";
    body<<req->getBodyParam("username")<<"'></p>";
    body<<"<p><label for='trip_id'>Trip ID: </label>";
    body<<"<input type='text' name='trip_id' value='";
    body<<req->getBodyParam("trip_id")<<"'></p>";
    body<<"<p><input type='submit' formtarget='_self' value='submit'></p></form><p><a href='/passengerPage'>";
    body<<"<input type='button'  value='Back'></a></p>";
    return body.str();
}

string DeleteHandler::show_success(){
    ostringstream body;
    body<<"<!DOCTYPE html>"<<endl<<"<html>"<<endl<<"<title>Request</title>"<<endl<<"<body>"<<endl;
    body<<"<script>";
    body<<"alert('OK');";
    body<<"window.location.href = '/';";
    body<<"</script>";
    return close_page(body.str());
}

string DeleteHandler::set_error_page(Request* req, Error err){
    ostringstream body;
    body<< set_page_as_before(req);
    body<<"<script>";
    body<<"alert('";
    body<<err.what();
    body<<"');";
    body<<"</script>";
    return close_page(body.str());
}

DeleteHandler::DeleteHandler(UTaxi* utaxi_){
    utaxi= utaxi_;
}

Response *DeleteHandler::callback(Request* req){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    try{
        utaxi->delete_trip(req->getBodyParam("username"), stoi(req->getBodyParam("trip_id")));
        res->setBody(show_success());
    }
    catch(Error err){
        res->setBody(set_error_page(req , err));
    }
    return res;
}

GetTripsHandler::GetTripsHandler(UTaxi* utaxi_){
    utaxi= utaxi_;
}

string GetTripsHandler::show_trips(vector<Trip*> trips ,string username){
    ostringstream body;
    body<<"<!DOCTYPE html>"<<endl;
    body<<"<html>"<<endl;
    body<<"<title>Get Trips</title>"<<endl;
    body<<"<body>"<<endl;
    body<<"<table border = 1>"<<endl;
    body<<"<tr>"<<endl;
    body<<"<th>ID</th>"<<endl;
    body<<"<th>Name</th>"<<endl;
    body<<"<th>Origin</th>"<<endl;
    body<<"<th>Destination</th>"<<endl;
    body<<"<th>Price</th>"<<endl;
    body<<"<th>Status</th>"<<endl;
    body<<"<th>&nbsp;</th>"<<endl;
    body<<"</tr>"<<endl;
    for(int i=0 ; i<trips.size() ; i++){
        body<<"<tr>"<<endl;
        body<<"<td>"<<trips[i]->id<<"</td>"<<endl;
        body<<"<td>"<<trips[i]->customer->get_name()<<"</td>"<<endl;
        body<<"<td>"<<trips[i]->origin->get_name()<<"</td>"<<endl;
        body<<"<td>"<<trips[i]->destination->get_name()<<"</td>"<<endl;
        body<<"<td>"<<trips[i]->price<<"</td>"<<endl;
        if(trips[i]->status == WAITING){
            body<<"<td>"<<"waiting"<<"</td>"<<endl;
            body<<"<td>"<<endl;
            body<<"<form action='/accept' method='post'>"<<endl;
            body<<"<input type='hidden' name='username' value='";
            body<<username<<"'>"<<endl;
            body<<"<input type='hidden' name='trip_id' value='";
            body<<trips[i]->id<<"'>"<<endl;
            body<<"<input type='submit' formtarget='_self' value='Accept'>";
            body<<"</form>";
            body<<"</td>"<<endl;
        }
        else if(trips[i]->status == TRAVELING){
            body<<"<td>"<<"traveling"<<"</td>"<<endl;
            body<<"<td>"<<endl;
            body<<"<form action='/finish' method='post'>"<<endl;
            body<<"<input type='hidden' name='username' value='";
            body<<username<<"'>"<<endl;
            body<<"<input type='hidden' name='trip_id' value='";
            body<<trips[i]->id<<"'>"<<endl;
            body<<"<input type='submit' formtarget='_self' value='Finish'>"<<endl;
            body<<"</form>";
            body<<"</td>"<<endl;
        }
        else if(trips[i]->status == FINISHED){
            body<<"<td>"<<"finished"<<"</td>"<<endl;
        }
        body<<"</tr>"<<endl;
    }
    body<<"</table>"<<endl;
    body<<"<p><a href='/driverPage'><input type='button' value='Back'></a></p>";
    body<<"</body>";
    body<<"</html>";
    return body.str();
}

string GetTripsHandler::show_error(Error err){
    ostringstream body;
    body<<"<!DOCTYPE html>"<<endl<<"<html>"<<endl<<"<title>GetTrip</title>"<<endl<<"<body>"<<endl;
    body<<"<script>";
    body<<"alert('";
    body<<err.what();
    body<<"');";
    body<<"window.location.href = '/';";
    body<<"</script>";
    body<<"</body>";
    body<<"</html>";
    return body.str();
}

Response* GetTripsHandler::callback(Request* req){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    bool sort_by_cost = false;
    if(req->getBodyParam("sort_by_cost") == "yes")
        sort_by_cost = true;
    else
        sort_by_cost = false;
    try{
        vector<Trip*> trips = utaxi->get_trips(req->getBodyParam("username"), sort_by_cost);
        res->setBody(show_trips(trips, req->getBodyParam("username")));
    }
    catch(Error err){
        res->setBody(show_error(err));
    }
    return res;
}

AcceptHandler::AcceptHandler(UTaxi* utaxi_){
    utaxi = utaxi_;
}

string AcceptHandler::show_success(){
    ostringstream body;
    body<<"<!DOCTYPE html>"<<endl<<"<html>"<<endl<<"<title>Accept</title>"<<endl<<"<body>"<<endl;
    body<<"<script>";
    body<<"alert('OK');";
    body<<"window.location.href = '/';";
    body<<"</script>";
    body<<"</body>";
    body<<"</html>";
    return body.str();
}

string AcceptHandler::show_error(Error err){
    ostringstream body;
    body<<"<!DOCTYPE html>"<<endl<<"<html>"<<endl<<"<title>Accept</title>"<<endl<<"<body>"<<endl;
    body<<"<script>";
    body<<"alert('";
    body<<err.what();
    body<<"');";
    body<<"window.location.href = '/';";
    body<<"</script>";
    body<<"</body>";
    body<<"</html>";
    return body.str();
}

Response *AcceptHandler::callback(Request* req){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    try{
        utaxi->accept_request(req->getBodyParam("username"), stoi(req->getBodyParam("trip_id")));
        res->setBody(show_success());
    }
    catch(Error err){
        res->setBody(show_error(err));
    }
    return res;
}

FinishHandler::FinishHandler(UTaxi* utaxi_){
    utaxi = utaxi_;
}

string FinishHandler::show_success(){
    ostringstream body;
    body<<"<!DOCTYPE html>"<<endl<<"<html>"<<endl<<"<title>Finish</title>"<<endl<<"<body>"<<endl;
    body<<"<script>";
    body<<"alert('OK');";
    body<<"window.location.href = '/';";
    body<<"</script>";
    body<<"</body>";
    body<<"</html>";
    return body.str();
}

string FinishHandler::show_error(Error err){
    ostringstream body;
    body<<"<!DOCTYPE html>"<<endl<<"<html>"<<endl<<"<title>Finish</title>"<<endl<<"<body>"<<endl;
    body<<"<script>";
    body<<"alert('";
    body<<err.what();
    body<<"');";
    body<<"window.location.href = '/';";
    body<<"</script>";
    body<<"</body>";
    body<<"</html>";
    return body.str();
}

Response *FinishHandler::callback(Request* req){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    try{
        utaxi->end_trip(req->getBodyParam("username"), stoi(req->getBodyParam("trip_id")));
        res->setBody(show_success());
    }
    catch(Error err){
        res->setBody(show_error(err));
    }
    return res;
}
