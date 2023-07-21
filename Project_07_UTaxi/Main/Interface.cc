#include"Interface.hh"

Interface::Interface(UTaxi* utaxi_){
    utaxi = utaxi_;
}

void Interface::start_program(){
    try{
        Server server(8080);
        server.get("/", new ShowPage("statics/mainPage.html"));
        server.get("/signUpPage", new ShowPage("statics/signUpPage.html"));
        server.get("/passengerPage", new ShowPage("statics/passengerPage.html"));
        server.get("/driverPage", new ShowPage("statics/driverPage.html"));
        server.get("/requestCostPage", new ShowPage("statics/requestCostPage.html"));
        server.get("/getTripsPage", new ShowPage("statics/getTripsPage.html"));
        server.get("/deletePage", new ShowPage("statics/deletePage.html"));
        server.post("/signup", new SignUpHandler(utaxi));
        server.post("/requestCost" , new RequestCostHandler(utaxi));
        server.post("/delete" , new DeleteHandler(utaxi));
        server.post("/getTrips", new GetTripsHandler(utaxi));
        server.post("/accept", new AcceptHandler(utaxi));
        server.post("/finish", new FinishHandler(utaxi));
        server.run();
    }
    catch(Server::Exception e){
        e.getMessage();
    }
}