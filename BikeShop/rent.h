#ifndef RENT_H
#define RENT_H
#include <string>
#include "bike.h"

using namespace std;

class Rent
{
    Bike *bike;
    int days,id;
    bool paid;
    static int price;
public:
    Rent(int _id,Bike *b,int _days,bool _paid=false);

    int getId() const;
    int getPrice() const;
    bool getPaid() const;
    void addDays(int _days);
    void changePaid();
    void freeBike();

    string toString() const;
    string toFile() const;
};

#endif // RENT_H
