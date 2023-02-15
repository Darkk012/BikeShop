#include "rent.h"

int Rent::price=500;

Rent::Rent(int _id, Bike *b, int _days,bool _paid):
    bike(b),days(_days),id(_id),paid(_paid)
{}

int Rent::getId() const
{
    return id;
}

int Rent::getPrice() const
{
    return days*price;
}

bool Rent::getPaid() const
{
    return paid;
}

void Rent::addDays(int _days)
{
    days+=_days;
}

void Rent::changePaid()
{
    paid=true;
}

void Rent::freeBike()
{
    bike->freeBike();
}

string Rent::toString() const
{
    return "Rent: "+to_string(id)+" Days: "+to_string(days)+" "+bike->toString();
}

string Rent::toFile() const
{
    if(paid){
        return to_string(id)+" "+to_string(bike->getSerialNumber())+" "+to_string(days)+" 1";
    }else{
        return to_string(id)+" "+to_string(bike->getSerialNumber())+" "+to_string(days)+" 0";
    }
}
