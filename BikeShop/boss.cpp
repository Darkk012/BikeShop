#include "boss.h"

Boss::Boss(string _name,string _pass)
    :Profile(_name,_pass)
{}

void Boss::addNewBike(vector<Bike> &bike, string _brand, string _type, int _serial)
{
    bike.push_back(Bike(_brand,_type,_serial));
}

void Boss::manageWorker(Worker* &w, int _salary)
{
    w->newSalary(_salary);
}

unsigned Boss::login(string _name, string _pass) const
{
    if(this->getName()==_name && this->getPassword()==_pass){
        return 1;
    }else return 0;
}

int Boss::type() const
{
    return 1;
}

string Boss::toString() const
{
    return "Boss: Boss";
}

string Boss::toFile() const
{
    return getName()+" "+getPassword();
}
