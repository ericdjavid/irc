#pragma once

#include <string>

class channel
{
    private:
    std::string _name;

    public:
    ~channel() {};
    channel(std::string name) : _name(name) 
    {
        std::cout << "Channel " << _name << " created" << std::endl;

    };

};