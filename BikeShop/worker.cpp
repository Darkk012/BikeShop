#include "worker.h"

Worker::Worker(string _name, string _pass, int _salary):
    Profile(_name,_pass),salary(_salary)
{}

void Worker::addNewRenter(vector<Profile*> &profiles, string _name, string _pass, string _address, string _email)
{
    profiles.push_back(new Renter(_name,_pass,_address,_email));
}

void Worker::startNewRent(Renter *&profile, int _id, Bike *b, int _days)
{
    profile->addRent(_id,b,_days);
    b->rentBike();
}

void Worker::viewRent(Renter *&profile)
{
    cout<<profile->toString()<<endl;
    profile->viewRent();
}

void Worker::editRent(vector<Profile *> &profiles, int _rentid, int _days)
{
    for(auto &p:profiles){
       if(p->type()==3){
            Renter *r=dynamic_cast<Renter*>(p);
            vector<int> ids;
            bool idok=false;
            r->getRentId(ids);
            for(auto i:ids){
                 if(i==_rentid)idok=true;
            }
            if(idok){
                r->editRent(_rentid,_days);
            }
       }
    }
}

void Worker::endRent(vector<Profile *> &profiles, int _rentid)
{
    for(auto &p:profiles){
        if(p->type()==3){
            Renter *r=dynamic_cast<Renter*>(p);
            int price=r->getRentPrice(_rentid);
            if(price!=0){
                cout<<"Rent price:"<<to_string(price)<<endl;
                cout<<"Write 'yes' if rent was paid!"<<endl;
                string paid="";
                cin>>paid;
                if(paid=="yes"){
                   r->deleteRent(_rentid);
                   cout<<"Rent ended succesfully!"<<endl;
                }else{
                    cout<<"Rent was not paid!"<<endl;
                }
            }
        }
    }
}

void Worker::newSalary(int _salary)
{
    salary=_salary;
}

unsigned Worker::login(string _name, string _pass) const
{
    if(this->getName()==_name && this->getPassword()==_pass){
        return 2;
    }else return 0;
}

int Worker::type() const
{
    return 2;
}

string Worker::toString() const
{
    return "Worker: "+getName()+" Salary: "+to_string(salary);
}

string Worker::toFile() const
{
    return getName()+" "+getPassword()+" "+to_string(salary);
}
