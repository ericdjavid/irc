#pragma once

#include <string>
#include <iostream>

class user 
{
    private:
    // NICK
    // pseudonyme unique ayant une longueur maximale de neuf (9) caractères.
    std::string _nick;
    int        _id;
    std::string _password;
    // Operators have increased power than the classic user
    bool        _is_operat;

    public:
    user(int id, std::string nick) : _nick(nick), _id(id)
    {
        _is_operat = false;
        std::cout << "new user created of id : " << _id << std::endl;
    };
    ~user() {};
    int set_nick(std::string nick);
    int set_password(std::string pswd);
    // set username
};


