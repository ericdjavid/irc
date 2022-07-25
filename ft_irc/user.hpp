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
    user() {
        (void)_id;
        (void)_is_operat;
    };
    ~user() {};
    int set_nick(std::string nick);
    // set username
    int set_password(std::string pswd);
};


