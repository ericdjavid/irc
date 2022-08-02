#pragma once

#include <string>
#include <vector>
#include "user.hpp"

class Channel
{
    private:
    std::string _name;
    // list of users that have joined the channel
    //std::vector<User> id;

    public:
    ~Channel() {};
    Channel(std::string name) : _name(name) 
    {
        //id = std::vector<User>;
        std::cout << "Channel " << _name << " created" << std::endl;
    };
    std::string get_name()
    {
        return(_name);
    }
    Channel &operator= (Channel *ptr)
    {
        return (*ptr);
    }
};