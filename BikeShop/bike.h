#ifndef BIKE_H
#define BIKE_H
#include <string>

using namespace std;

class Bike
{
    string brand,type;
    int serialNumber;
    bool free=true;
public:
    Bike(string _brand,string _type,int _serial);

    void rentBike();
    void freeBike();
    bool getFree() const;
    int getSerialNumber() const;

    string toString();
    string toFile();
};

#endif // BIKE_H
