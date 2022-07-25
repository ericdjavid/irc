#pragma once

#include <string>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

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
    user() {
        (void)_id;
        (void)_is_operat;
    };
    ~user() {};
    int set_nick(std::string nick);
    // set username
    int set_password(std::string pswd);
};


