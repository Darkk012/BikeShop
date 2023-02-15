#ifndef RENTER_H
#define RENTER_H
#include <vector>
#include <algorithm>
#include "profile.h"
#include "rent.h"
#include "iostream"

using namespace std;

class Renter:public Profile
{
private:
    string address,email;
    vector<Rent> rents;
    int activeRents;

public:
    Renter(string _name,string _pass,string _address,string _email);

    void viewRent() const;
    void addRent(int _id, Bike *b, int _days,bool _paid=false);
    void deleteRent(int _id);
    void getRentId(vector<int> &rentids)const;
    void editRent(int _rentid,int _days);
    int getRentPrice(int _rentid)const;

    unsigned login(string _name, string _pass) const override;
    int type() const override;
    string toString() const override;
    string toFile() const override;
};

#endif // RENTER_H
