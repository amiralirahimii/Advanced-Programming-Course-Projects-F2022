#include"Coordination.hh"
#include"Define.hh"

using namespace std;

Coordination::Coordination(double la, double lo){
    latitude = la;
    longitude = lo;
}

double Coordination::calculate_distance_to(Coordination coor){
    double distance;
    distance = sqrt(pow((coor.latitude - latitude) , 2) + pow((coor.longitude - longitude) , 2));
    distance *= ONE_DEGREE_IN_KM;
    return distance;
}