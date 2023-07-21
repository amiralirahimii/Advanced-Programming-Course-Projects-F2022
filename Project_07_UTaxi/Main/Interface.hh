#ifndef INTERFACE_HH
#define INTERFACE_HH

#include"server/server.hpp"
#include"logicPart/UTaxi.hh"
#include"logicPart/handler.hh"

class Interface{
public:
    Interface(UTaxi* utaxi_);
    void start_program();
private:
    UTaxi* utaxi;
};

#endif