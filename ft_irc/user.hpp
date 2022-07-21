#pragma once

#include <string>

class user 
{
    private:
    // NICK
    std::string _nick;
    int        _id;
    std::string _password;
    // Operators have increased power than the classic user
    bool        _is_operat;

    public:
    user();
    ~user();
    int set_nick(std::string nick);
    int set_password(std::string pswd);
};


