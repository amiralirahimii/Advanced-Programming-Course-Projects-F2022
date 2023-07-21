#include<iostream>
#include"logicPart/UTaxi.hh"
#include"Interface.hh"

using namespace std;

int main(int argc, char* argv[]){
    UTaxi utaxi(argv[1]);
    Interface interface(&utaxi);
    interface.start_program();
}