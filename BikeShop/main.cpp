#include <iostream>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include "profile.h"
#include "renter.h"
#include "bike.h"
#include "boss.h"
#include "worker.h"
using namespace std;

void init(vector<Profile*> &profiles,vector<Bike> &bikes,int &startingid){
    profiles.push_back(new Boss("boss","bosspass"));

    string line;

    ifstream bikeFile("bike.txt");
    if(bikeFile.is_open()){
        string _brand="",_type="",_serialstr="";
        int _serial=0;

        while(getline(bikeFile,line)){
            if(!line.empty()){
                istringstream tmp(line);
                tmp>>_brand>>_type>>_serialstr;
                _serial=stoi(_serialstr);
               bikes.push_back(Bike(_brand,_type,_serial));
            }
        }
    }
    bikeFile.close();

    ifstream workerFile("worker.txt");
    if(workerFile.is_open()){
        string _name="",_pass="",_salarystr="";
        int _salary=0;

        while (getline(workerFile,line)) {
            if(!line.empty()){
                istringstream tmp(line);
                tmp>>_name>>_pass>>_salarystr;
                _salary=stoi(_salarystr);
                profiles.push_back(new Worker(_name,_pass,_salary));
            }
        }
    }
    workerFile.close();

    ifstream renterFile("renter.txt");
    if(renterFile.is_open()){
        string _name="",_pass="",_address="",_email="",_rentsizestr="",_rentidstr="",bikeserialstr="",_daysstr="",_paidstr="";
        int rentsize=0,_rentid=0,bikeserial=0,_days=0;
        bool _paid=false;
        while (getline(renterFile,line)) {
            if(!line.empty()){
                istringstream tmp(line);
                tmp>>_name>>_pass>>_address>>_email>>_rentsizestr;
                rentsize=stoi(_rentsizestr);
                Renter *r=new Renter(_name,_pass,_address,_email);
                profiles.push_back(r);
                for(int i=0;i<rentsize;i++){
                    tmp>>_rentidstr>>bikeserialstr>>_daysstr>>_paid;
                    _rentid=stoi(_rentidstr);
                    bikeserial=stoi(bikeserialstr);
                    _days=stoi(_daysstr);
                    if(_rentid>=startingid) startingid=_rentid+1;
                    if(_paidstr=="1")_paid=true;
                    Bike *b=nullptr;
                    for(auto &bk:bikes){
                        if(bk.getSerialNumber()==bikeserial){
                            b=&bk;
                        }
                    }
                    if(b!=nullptr){
                        if(!_paid){
                            b->rentBike();
                        }
                        r->addRent(_rentid,b,_days,_paid);
                    }
                }
            }
        }


    }
    renterFile.close();
}

void saveToFile(vector<Profile*> profiles,vector<Bike> bikes){
    ofstream bikeFile("bike.txt",ios::trunc);

    if(bikeFile.is_open()){

        for(auto b:bikes){
            bikeFile<<b.toFile()<<endl;
        }
    }

    bikeFile.close();

    ofstream workerFile("worker.txt",ios::trunc);
    ofstream renterFile("renter.txt",ios::trunc);

    if(workerFile.is_open() && renterFile.is_open()){
        for(auto p:profiles){
            if(p->type()==2){
                workerFile<<p->toFile()<<endl;
            }

            if(p->type()==3){
                renterFile<<p->toFile()<<endl;
            }
        }

    }

    workerFile.close();
    renterFile.close();
}

void registration(vector<Profile*> &profiles){
    string _name="",_pass="",_address="",_email="";
    bool nameok=true;
    cout<<endl<<"Registration: "<<endl;

    do {
        nameok=true;
        cout<<"New profile name: ";
        cin>>_name;
        for(auto p:profiles){
           if(p->getName()==_name)nameok=false;
        }
        if(!nameok)cout<<"Name taken! Try again!"<<endl;
    } while (!nameok);

    cout<<"New profile password: ";
    cin>>_pass;
    cout<<"New profile address: ";
    cin>>_address;
    cout<<"New profile email: ";
    cin>>_email;

    cout<<"Write 'yes' to create the profile!"<<endl;
    string create="";
    cin>>create;

    if(create=="yes"){
        profiles.push_back(new Renter(_name,_pass,_address,_email));
        cout<<"Profile created succesfully!"<<endl;
    }else{
        cout<<"Profile creating cancelled!"<<endl;
    }
    cin.ignore();
}

int login(vector<Profile*> &profiles, Profile* &activeProfile){
    int point=0;
    string _name="",_pass="";
    activeProfile=nullptr;
    cout<<endl<<"Login:"<<endl;

    cout<<"Name: ";
    cin>>_name;
    cout<<"Password: ";
    cin>>_pass;

    for(auto p:profiles){
        point=p->login(_name,_pass);
        if(point!=0){
            activeProfile=p;
            return point;
        }
    }
    cin.ignore();
    return 0;
}

void bossMenu(Boss *boss,vector<Bike> &bikes,vector<Profile*> &profiles){
    int menuPoint=0;
    cin.ignore();
    do {
        cout<<endl<<"Boss Menu:"<<endl;
        cout<<"1. Add new bike"<<endl;
        cout<<"2. Manage workers"<<endl;
        cout<<"3. Logout"<<endl;
        cout<<"Choose between the menu points: ";

        string line;
        while(getline(cin,line)){
            stringstream ss(line);
            if(ss>>menuPoint){
                if(ss.eof() && (menuPoint==1 || menuPoint==2 || menuPoint==3)){
                    break;
                }
            }
            cout<<"Wrong menu point or not number given! Try again"<<endl;
        }
        string _brand="",_type="",create="";
        int _serial=0,workerid=0,salary=0;
        vector<int> workernumbers;
        bool workerok=false,serialok=true;
        Worker* w=nullptr;

        switch (menuPoint) {
        case 1:
            cout<<endl<<"Adding new bike"<<endl;
            cout<<"Bike brand: ";
            cin>>_brand;
            cout<<"Bike type: ";
            cin>>_type;          
            cin.ignore();

            do {
                cout<<"Bike serial number: ";
                serialok=true;
                while(getline(cin,line)){
                    stringstream ss(line);
                    if(ss>>_serial){
                        if(ss.eof()){
                            break;
                        }
                    }
                    cout<<"Not number given! Try again!"<<endl;
                }

                for(const auto &b:bikes){
                    if(b.getSerialNumber()==_serial)serialok=false;
                }

                if(!serialok)cout<<"Serial number taken, not unique! Try again!"<<endl;
            } while (!serialok);


            cout<<"Write 'yes' to add new bike!"<<endl;
            cin>>create;
            if(create=="yes"){
                boss->addNewBike(bikes,_brand,_type,_serial);
                cout<<"Bike added succesfully!"<<endl;
            }else{
                cout<<"Bike was not added!"<<endl;
            }
            cin.ignore();
            saveToFile(profiles,bikes);
            break;
        case 2:
            cout<<endl<<"Manage worker"<<endl;
            workernumbers.clear();
            for(unsigned i=0;i<profiles.size();i++){
                if(profiles[i]->type()==2){
                    cout<<i<<" "<<profiles[i]->toString()<<endl;
                    workernumbers.push_back(i);
                }
            }

            do {
                cout<<"Choose worker number:";
                while(getline(cin,line)){
                    stringstream ss(line);
                    if(ss>>workerid){
                        if(ss.eof()){
                            break;
                        }
                    }
                    cout<<"Not number given! Try again!"<<endl;
                }

                for(auto i:workernumbers){
                    if(i==workerid)workerok=true;
                }

                if(workerok==false){
                    cout<<"Wrong worker number given! Try again!"<<endl;
                }
            } while (!workerok);
            w=dynamic_cast<Worker*>(profiles[workerid]);

            cout<<"New salary:";
            while(getline(cin,line)){
                stringstream ss(line);
                if(ss>>salary){
                    if(ss.eof() && salary>0){
                        break;
                    }
                }
                cout<<"Not number given or salary 0 or less! Try again!"<<endl;
            }
            cout<<"Write 'yes' to give new salary!"<<endl;
            cin>>create;
            if(create=="yes"){
                boss->manageWorker(w,salary);
                cout<<"Salary added succesfully!"<<endl;
            }else{
                cout<<"Salary was not added!"<<endl;
            }
            cin.ignore();
            saveToFile(profiles,bikes);
            break;
        case 3:
            cout<<"Logging out!"<<endl;
            break;
        }
    } while (menuPoint!=3);
}

void workerMenu(Worker *worker, int &id,vector<Profile*> &profiles,vector<Bike> &bikes){
    string _name="",_pass="",_address="",_email="",create="",paid="";
    bool nameok=true,profileok=false,bikeok=false,rentnumberok=false;
    int profileid=0,bikeid=0,days=0,menuPoint=0,rentNumber=0,okbikes=0,okprofiles=0;
    vector<int> profilesnumbers;
    vector<int> bikenumbers;
    vector<int> rentnumbers;
    Renter *r=nullptr;
    Bike *b=nullptr;

    cin.ignore();
    do {
        cout<<endl<<"Worker menu:"<<endl;
        cout<<"1. Add new renter"<<endl;
        cout<<"2. Start new rent"<<endl;
        cout<<"3. View rent"<<endl;
        cout<<"4. Edit rent"<<endl;
        cout<<"5. End rent"<<endl;
        cout<<"6. Logout"<<endl;
        cout<<"Choose between the menu points: ";

        string line;
        while(getline(cin,line)){
            stringstream ss(line);
            if(ss>>menuPoint){
                if(ss.eof() && (menuPoint==1 || menuPoint==2 || menuPoint==3 || menuPoint==4 || menuPoint==5 || menuPoint==6)){
                    break;
                }
            }
            cout<<"Wrong menu point or not number given! Try again"<<endl;
        }

        switch (menuPoint) {
        case 1:
            cout<<endl<<"Adding new renter: "<<endl;
            do {
                nameok=true;
                cout<<"New renter name: ";
                cin>>_name;
                for(auto p:profiles){
                   if(p->getName()==_name)nameok=false;
                }
                if(!nameok)cout<<"Name taken! Try again!"<<endl;
            } while (!nameok);

            cout<<"New renter password: ";
            cin>>_pass;

            cout<<"New renter address: ";
            cin>>_address;

            cout<<"New renter email: ";
            cin>>_email;

            cout<<"Write 'yes' to create the profile!"<<endl;
            cin>>create;
            if(create=="yes"){
                worker->addNewRenter(profiles,_name,_pass,_address,_email);
                cout<<"Renter created succesfully!"<<endl;
            }else{
                cout<<"Renter creating cancelled!"<<endl;
            }
            cin.ignore();
            saveToFile(profiles,bikes);
            break;
        case 2:
            cout<<endl;
            okbikes=0;okprofiles=0;
            for(unsigned i=0;i<profiles.size();i++){
                if(profiles[i]->type()==3)okprofiles++;
            }

            for(unsigned i=0;i<bikes.size();i++){
                if(bikes[i].getFree())okbikes++;
            }

            if(bikes.empty() || okbikes==0 ||okprofiles==0){
               if(okprofiles==0) cout<<"You cannot make a rent wihtout renters!"<<endl;
               if(bikes.empty() || okbikes==0 ) cout<<"You cannot make a rent without bikes"<<endl;
            }else{
                cout<<"Starting new rent:"<<endl;
                profilesnumbers.clear();
                bikenumbers.clear();
                for(unsigned i=0;i<profiles.size();i++){
                    if(profiles[i]->type()==3){
                        cout<<i<<" "<<profiles[i]->toString()<<endl;
                        profilesnumbers.push_back(i);
                    }
                }

                do {
                    cout<<"Choose the profile number: ";
                    while(getline(cin,line)){
                        stringstream ss(line);
                        if(ss>>profileid){
                            if(ss.eof()){
                                break;
                            }
                        }
                        cout<<"Not number given! Try again!"<<endl;
                    }

                    for(auto i:profilesnumbers){
                        if(i==profileid)profileok=true;
                    }

                    if(profileok==false){
                        cout<<"Wrong profile number given! Try again!"<<endl;
                    }
                } while (!profileok);

                r=dynamic_cast<Renter*>(profiles[profileid]);

                for(unsigned i=0;i<bikes.size();i++){
                   if(bikes[i].getFree()){
                       cout<<i<<" "<<bikes[i].toString()<<endl;
                       bikenumbers.push_back(i);
                   }
                }

                do {
                    cout<<"Choose the bike number: ";
                    while(getline(cin,line)){
                        stringstream ss(line);
                        if(ss>>bikeid){
                            if(ss.eof()){
                                break;
                            }
                        }
                        cout<<"Not number given! Try again!"<<endl;
                    }

                    for(auto i:bikenumbers){
                        if(i==bikeid)bikeok=true;
                    }

                    if(bikeok==false){
                        cout<<"Wrong bike number given! Try again!"<<endl;
                    }
                } while (!bikeok);

                b=&bikes[bikeid];

                cout<<"How many days? ";
                while(getline(cin,line)){
                    stringstream ss(line);
                    if(ss>>days){
                        if(ss.eof()&& days>0){
                            break;
                        }
                    }
                    cout<<"Not number given or 0 or less days given! Try again!"<<endl;
                }

                cout<<"Write 'yes' to start the new rent!"<<endl;
                cin>>create;
                if(create=="yes"){
                    worker->startNewRent(r,id,b,days);
                    id++;
                    cout<<"Rent started succesfully!"<<endl;
                }else{
                    cout<<"Rent starting cancelled!"<<endl;
                }
                cin.ignore();
            }
            saveToFile(profiles,bikes);
            break;
        case 3:
            cout<<endl<<"Viewing rents:"<<endl;
            for(unsigned i=0;i<profiles.size();i++){
                if(profiles[i]->type()==3){
                    r=dynamic_cast<Renter*>(profiles[i]);
                    worker->viewRent(r);
                }
            }
            break;
        case 4:
            cout<<endl<<"Editing rent"<<endl;
            rentnumbers.clear();
            for(unsigned i=0;i<profiles.size();i++){
                if(profiles[i]->type()==3){
                    r=dynamic_cast<Renter*>(profiles[i]);
                    worker->viewRent(r);
                    r->getRentId(rentnumbers);
                }
            }
            cout<<"Rent number: ";
            do {
                while(getline(cin,line)){
                    stringstream ss(line);
                    if(ss>>rentNumber){
                        if(ss.eof()){
                            break;
                        }
                    }
                    cout<<"Not number given! Try again!"<<endl;
                }

                for(auto i:rentnumbers){
                    if(i==rentNumber)rentnumberok=true;
                }

                if(rentnumberok==false){
                    cout<<"Wrong rent number given! Try again!"<<endl;
                }

            } while (!rentnumberok);

            cout<<"How many days? ";
            while(getline(cin,line)){
                stringstream ss(line);
                if(ss>>days){
                    if(ss.eof()&& days>0){
                        break;
                    }
                }
                cout<<"Not number given or 0 or less days given! Try again!"<<endl;
            }

            cout<<"Write 'yes' to edit the rent!"<<endl;
            cin>>create;
            if(create=="yes"){
                worker->editRent(profiles,rentNumber,days);
                cout<<"Rent edited succesfully!"<<endl;
            }else{
                cout<<"Rent editing cancelled!"<<endl;
            }
            cin.ignore();
            saveToFile(profiles,bikes);
            break;
        case 5:
            cout<<endl<<"Ending rent"<<endl;
            rentnumbers.clear();
            for(unsigned i=0;i<profiles.size();i++){
                if(profiles[i]->type()==3){
                    r=dynamic_cast<Renter*>(profiles[i]);
                    worker->viewRent(r);
                    r->getRentId(rentnumbers);
                }
            }
            cout<<"Rent number: ";
            do {
                while(getline(cin,line)){
                    stringstream ss(line);
                    if(ss>>rentNumber){
                        if(ss.eof()){
                            break;
                        }
                    }
                    cout<<"Not number given! Try again!"<<endl;
                }

                for(auto i:rentnumbers){
                    if(i==rentNumber)rentnumberok=true;
                }

                if(rentnumberok==false){
                    cout<<"Wrong rent number given! Try again!"<<endl;
                }

            } while (!rentnumberok);

            cout<<"Write 'yes' to end the rent!"<<endl;
            cin>>create;
            if(create=="yes"){
                worker->endRent(profiles,rentNumber);
            }else{
                cout<<"Rent ending cancelled!"<<endl;
            }
            cin.ignore();
            saveToFile(profiles,bikes);
            break;
        case 6:
            cout<<"Logging out!"<<endl;
            break;
        }

    } while (menuPoint!=6);
}

void renterMenu(Renter *Renter){
    int menuPoint=0;
    cin.ignore();
    do {
        cout<<endl<<"Renter Menu:"<<endl;
        cout<<"1. View rents"<<endl;
        cout<<"2. Logout"<<endl;
        cout<<"Choose between the menu points: ";

        string line;
        while(getline(cin,line)){
            stringstream ss(line);
            if(ss>>menuPoint){
                if(ss.eof() && (menuPoint==1 || menuPoint==2)){
                    break;
                }
            }
            cout<<"Wrong menu point or not number given! Try again"<<endl;
        }

        switch (menuPoint) {
        case 1:
            cout<<endl;
            Renter->viewRent();
            break;
        case 2:
             cout<<"Logging out!"<<endl;
            break;
        }
    } while (menuPoint!=2);
}

int main()
{ 
    vector<Profile*> profiles;
    vector<Bike> bikes;
    Profile* activeProfile=nullptr;
    int startingid=0;

    init(profiles,bikes,startingid);
    int menuPoint=0;
    do {
        cout<<endl<<"Bike Shop Renting Application:"<<endl;
        cout<<"Choose what you want to do: "<<endl;
        cout<<"1. Login"<<endl;
        cout<<"2. Registration"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Choose between the menu points: ";

        string line;
        while(getline(cin,line)){
            stringstream ss(line);
            if(ss>>menuPoint){
                if(ss.eof() && (menuPoint==1 || menuPoint==2 || menuPoint==3)){
                    break;
                }
            }
            cout<<"Wrong menu point or not number given! Try again"<<endl;
        }

        int mainMenuPoint=0;
        Boss *boss=nullptr;
        Worker *worker=nullptr;
        Renter* renter=nullptr;

        switch (menuPoint) {
        case 1:
            mainMenuPoint=login(profiles,activeProfile);

            boss=dynamic_cast<Boss*>(activeProfile);
            worker=dynamic_cast<Worker*>(activeProfile);
            renter=dynamic_cast<Renter*>(activeProfile);

            switch (mainMenuPoint) {
            case 0:
                cout<<"Failed to login!"<<endl;
                break;
            case 1:
                bossMenu(boss,bikes,profiles);
                break;
            case 2:
                workerMenu(worker,startingid,profiles,bikes);
                break;
            case 3:
                renterMenu(renter);
                break;
            }
            break;
        case 2:
            registration(profiles);
            saveToFile(profiles,bikes);
            break;
        case 3:
            cout<<"Good Bye!"<<endl;
            break;
        }

    } while (menuPoint!=3);

    saveToFile(profiles,bikes);

    return 0;
}
