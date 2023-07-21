#ifndef COORDINATION_HH
#define COORDINATION_HH

#include<cmath>

class Coordination{
public:
    Coordination(double la, double lo);
    double calculate_distance_to(Coordination coor);
private:
    double latitude;
    double longitude;
};

#endif