#pragma once

#include <string>
#include <vector>
#include "user.hpp"

class Channel
{
    private:
    std::vector<class User>     _users;
    std::string                 _name;
    char                        _properties;

    public:
    ~Channel() {};

    Channel(std::string name) : _name(name) {}

    Channel(std::string name, std::vector<User> users, char prop)
    {
        _name = name;
        _users = users;
        _properties = prop;
    }

    std::string get_name()
    {
        return(_name);
    }

    Channel &operator= (Channel *ptr)
    {
        return (*ptr);
    }

    void    add_user(class User *utilisateur)
    {
        _users.push_back(*utilisateur);
    }

    int     verify_channel_name(std::string name, std::vector<Channel> channels)
    {
        const char  *reference;

        reference = name.c_str();
        if (compare_first_char(reference[0]) == '0' || name.length() >= 50)
        {
            std::cout << "wrong channel name, please select a correct one(starts with &-#-+-! and lenght of 50 char max)." << std::endl;
            return 1;
        }
        if (compare_to_existing_channels(name, channels))
            return 1;
        if (syntax_channel_name(name))
            return 1;
        return 0;
    }

   char     compare_first_char(char c)
    {
        if (c == '&' || c == '#' || c == '+' || c == '!')
            return c;
        return '0';
    }

    int     compare_to_existing_channels(std::string name, std::vector<Channel> channels)
    {
        std::vector<Channel>::iterator it = channels.begin();
        while(it != channels.end())
        {
            if (it->_name == name)
            {
                std::cout << "name " << name << " is already used by another Channel. Please select another one." << std::endl;
                return 1;
            }
            it++;
        }
        return 0;
    }

    int     syntax_channel_name(std::string name)
    {
        const char  *reference;
        int         i;

        reference = name.c_str();
        i = 0;
        while(reference[i])
        {
            if (is_forbidden(reference[i]) == 1)
                return 1;
            i++;
        }
        return 0;
    }
    
int     is_forbidden(char c)
    {
        if (c == ',' || c == ':' || c == ' ' || c == 7)
            return 1;
        return 0;
    }
};

void    print_channels(std::vector<Channel> channels)
{
    std::vector<Channel>::iterator it;

    it = channels.begin();
    while (it != channels.end())
    {
        std::cout << it->get_name() << std::endl;
        it++;
    }
}