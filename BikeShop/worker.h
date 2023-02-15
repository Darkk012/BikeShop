#ifndef WORKER_H
#define WORKER_H
#include <vector>
#include "profile.h"
#include "renter.h"
#include "rent.h"

using namespace std;

class Worker:public Profile
{
    int salary;
public:
    Worker(string _name,string _pass,int _salary);

    void addNewRenter(vector<Profile *> &profiles,string _name,string _pass,string _address,string _email);
    void startNewRent(Renter* &profile,int _id,Bike *b,int _days);
    void viewRent(Renter* &profile);
    void editRent(vector<Profile*> &profiles,int _rentid,int _days);
    void endRent(vector<Profile *> &profiles,int _rentid);
    void newSalary(int _salary);

    unsigned login(string _name, string _pass) const override;
    int type() const override;
    string toString() const override;
    string toFile() const override;
};

#endif // WORKER_H
