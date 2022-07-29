#pragma once

#include <string>
#include <vector>
#include "user.hpp"

class channel
{
    private:
    std::string _name;
    // list of users that have joined the channel
    std::vector<user> id;

    public:
    ~channel() {};
    channel(std::string name) : _name(name) 
    {
        std::cout << "Channel " << _name << " created" << std::endl;
    };
    std::string get_name()
    {
        return(_name);
    }

};