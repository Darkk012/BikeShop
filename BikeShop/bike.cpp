#include "bike.h"

Bike::Bike(string _brand, string _type, int _serial):
    brand(_brand),type(_type),serialNumber(_serial)
{}

void Bike::rentBike()
{
    free=false;
}

void Bike::freeBike()
{
    free=true;
}

bool Bike::getFree() const
{
    return free;
}

int Bike::getSerialNumber() const
{
    return serialNumber;
}

string Bike::toString()
{
    return "Bike: "+brand+" "+type+" "+to_string(serialNumber);
}

string Bike::toFile()
{
    return brand+" "+type+" "+to_string(serialNumber);
}
