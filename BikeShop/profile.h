#ifndef PROFILE_H
#define PROFILE_H
#include <string>

using namespace std;

class Profile
{
    string name,password;
public:
    Profile(string _name,string _pass);
    ~Profile();

    const string &getName() const;
    const string &getPassword() const;

    virtual unsigned login(string _name,string _pass) const=0;
    virtual int type()const=0;
    virtual string toString()const=0;
    virtual string toFile() const=0;
};

#endif // PROFILE_H
