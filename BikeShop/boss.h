#ifndef BOSS_H
#define BOSS_H
#include <iostream>
#include <vector>
#include "profile.h"
#include "bike.h"
#include "worker.h"

using namespace std;

class Boss: public Profile
{
public:
    Boss(string _name,string _pass);

    void addNewBike(vector<Bike> &bike,string _brand, string _type, int _serial);
    void manageWorker(Worker* &w,int _salary);

    unsigned login(string _name, string _pass) const override;
    int type() const override;
    string toString() const override;
    string toFile() const override;
};

#endif // BOSS_H
