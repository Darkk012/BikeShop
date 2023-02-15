#include "renter.h"

Renter::Renter(string _name, string _pass, string _address, string _email):
    Profile(_name,_pass),address(_address),email(_email),activeRents(0)
{}

void Renter::viewRent() const
{
    if(activeRents!=0){
        for(auto r:rents){
            if(!r.getPaid()){
            cout<<"\t"<<r.toString()<<endl;
            }
        }
    }else{
        cout<<"\t"<<getName()+" not having any rent!"<<endl;
    }
}

void Renter::addRent(int _id, Bike *b, int _days, bool _paid)
{
    rents.push_back(Rent(_id,b,_days,_paid));
    if(!_paid){
        activeRents++;
    }
}

void Renter::deleteRent(int _id)
{
    for(unsigned i=0;i<rents.size();i++){
        if(rents[i].getId()==_id){
            rents[i].changePaid();
            rents[i].freeBike();
            activeRents--;
        }
    }
}

void Renter::getRentId(vector<int> &rentids) const
{
    for(auto &r:rents){
        rentids.push_back(r.getId());
    }
}

void Renter::editRent(int _rentid, int _days)
{
    for(auto &r:rents){
        if(r.getId()==_rentid){
            r.addDays(_days);
        }
    }
}

int Renter::getRentPrice(int _rentid) const
{
    for(auto r:rents){
        if(r.getId()==_rentid){
            return r.getPrice();
        }
    }
    return 0;
}

unsigned Renter::login(string _name, string _pass) const
{
    if(this->getName()==_name && this->getPassword()==_pass){
        return 3;
    }else return 0;
}

int Renter::type() const
{
    return 3;
}

string Renter::toString() const
{
    return getName()+" "+address+" "+email;
}

string Renter::toFile() const
{
    string str=getName()+" "+getPassword()+" "+address+" "+email+" "+to_string(rents.size());
    for(auto r:rents){
        str+=" "+r.toFile();
    }
    return str;
}
