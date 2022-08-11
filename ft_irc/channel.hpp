#pragma once

#include <string>
#include <vector>
#include "user.hpp"

class Channel
{
    private:
    std::vector<User>     _users;
    std::vector<User>	_ban_users;
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

    Channel(std::string name, std::vector<User> users, std::vector<User> ban_u, char prop)
    {
        _name = name;
	_users = users;
	_ban_users = ban_u;
        _properties = prop;
    }

	User get_a_user(int i)
	{
		return (_users.at(i));
	}

    std::string get_name()
    {
        return(_name);
    }

    std::vector<User> get_users()
    {
        return _users;
    }

    std::vector<User> *get_users_ptr()
    {
        return &_users;
    }

	std::vector<User> get_ban_users()
	{
		return (_ban_users);
	}

    Channel &operator= (Channel *ptr)
    {
        return (*ptr);
    }

    void    add_user(class User utilisateur)
    {
        _users.push_back(utilisateur);
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

int		check_if_user_exist_in_channel(std::string target, std::vector<class User> users_channel)
{
	if (users_channel.empty() == true)
		return (-1);
	for(std::vector<User>::iterator it = users_channel.begin(); it != users_channel.end(); it++)
	{
std::cout << "user ==>" << it->get_nick() << "target ==>" << target << "----" << std::endl;
		if (it->get_nick() == target)
			return (1);
	}
	std::cout << "User not found in the channel \n";
	return (-1);
}


//Fonction pour kick l'user
	void	kick_user_out_from_channel(std::string target, std::vector<class User> *users_channel)
	{
		int i = 0;
		for(std::vector<User>::iterator it = users_channel->begin(); it != users_channel->end(); it++)
		{
			std::cout << "user ==> " << it->get_nick() << std::endl;
			std::cout << "target ==> " << target << std::endl;
			if (it->get_nick() == target)
				break;
			else
				i++;
		}
		users_channel->erase(users_channel->begin() + i);
		for(std::vector<User>::iterator it = users_channel->begin(); it != users_channel->end(); it++)
			std::cout << "user ==> " << it->get_nick() << std::endl;
	}

//Fonction pour ban l'user
	void	ban_user_out_from_channel(std::string target, std::vector<class User> users_channel, std::vector<class User> ban_users)
	{
		int i = 0;
		User tmp;
		for(std::vector<User>::iterator it = users_channel.begin(); it != users_channel.end(); it++)
		{
			std::cout << "user ==> " << it->get_nick() << std::endl;
			if (it->get_nick() == target)
				break;
			else
				i++;
		}
		tmp = users_channel.at(i);
		users_channel.erase(users_channel.begin() + i);
		for(std::vector<User>::iterator it = users_channel.begin(); it != users_channel.end(); it++)
			std::cout << "user ==> " << it->get_nick() << std::endl;
// get user then push back!!!!!!!!!!!!!11
		ban_users.push_back(tmp);
	}
