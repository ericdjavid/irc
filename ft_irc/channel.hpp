#pragma once

#include <string>
#include <vector>
#include "user.hpp"

class Channel
{
    private:
    std::vector<class User>     _users;
    std::vector<class User>	_ban_users;
    std::string                 _name;
    char                        _properties;

    public:

    ~Channel() {};

    Channel(std::string name) : _name(name) {}

    Channel(std::string name, std::vector<User> users, std::vector<User> ban_u, char prop)
    {
        _name = name;
        _users = users;
	_ban_users = ban_u;
        _properties = prop;
    }

    std::string get_name()
    {
        return(_name);
    }
<<<<<<< HEAD
/*
	int	get_user_needed(int sd)
	{
		int i = 0;
		std::vector<User>::iterator it = _users.begin();
		while (it != _users.end())
		{
			//if (sd == it->get_id())
				break;
			i++;
			it++;
		}
		return (i);
	}
*/
=======

    std::vector<User> get_users()
    {
        return _users;
    }

>>>>>>> 8b64656561287fc2f3b0fc7da0695d5855ed245a
    Channel &operator= (Channel *ptr)
    {
        return (*ptr);
    }

    void    add_user(class User *utilisateur)
    {
        _users.push_back(*utilisateur);
    }

    void    create_new_channel(std::string name, std::vector<Channel> *channels)
    {
        const char  *reference;

        reference = name.c_str();
        if (verify_channel_name(name, *channels) == 1)
            return ;
        std::vector<User> users;
	std::vector<User> ban_u;
        Channel *tmp = new Channel(name, users, ban_u, reference[0]);
        channels->push_back(*tmp);
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
        return 1;
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
