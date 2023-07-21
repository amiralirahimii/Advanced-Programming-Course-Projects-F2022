#include"Error.hh"

using namespace std;

Error::Error(string message){
    error_message = message;
}

void Error::print_message(){
    cout<<error_message<<endl;
}