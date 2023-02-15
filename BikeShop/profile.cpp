#include "profile.h"

Profile::Profile(string _name, string _pass):
    name(_name),password(_pass)
{}

Profile::~Profile()
{}

const string &Profile::getName() const
{
    return name;
}

const string &Profile::getPassword() const
{
    return password;
}
