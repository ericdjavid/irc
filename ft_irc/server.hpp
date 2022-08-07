#pragma once

#include "user.hpp"
#include "channel.hpp"
#include <vector>

struct server
{
    std::vector<Channel> the_channel;
    std::vector<User> the_users;
    std::string password;

} typedef the_serv;


// FONCTION POUR PARCOURIR LA LISTE DES USERS, RENVOIE NULL SI PAS TROUVE, SINN ID DE L USER
int 	check_if_user_exist(int sd, std::vector<class User> users)
{
    if (users.empty())
        return -1;
    std::vector<class User>::iterator it = users.begin();
    while (it != users.end())
    {
        // std::cout << "Comparing " << sd << " with " << it->get_id() << std::endl;
        if (sd == it->get_id())
        {
            return (sd);
        }
        it++;
    }
    return 0;
}

// FONCTION POUR TROUVER INDEX USER
int     get_index(std::vector<class User> user_list, int id)
{
    if (user_list.empty() == true)
        return -1;
    int index = 0;
    std::vector<class User>::iterator it = user_list.begin();
    while(it != user_list.end())
    {
        if (id == it->get_id())
            return index;
        index++;
        it++;
    }
    return 0;

}

// FONCTION POUR PARCOURIR LA LISTE DES USERS, RENVOIE 0 SI PAS TROUVE, SINN INDEX DE L USER
int 	check_if_user_exist_with_nick(std::string nick, std::vector<class User> the_users)
{
    if (the_users.empty() == true)
        return -1;
    int index = 0;
    std::vector<class User>::iterator it = the_users.begin();
    while (it != the_users.end())
    {
        // std::cout << "Comparing " << sd << " with " << it->get_id() << std::endl;
        if (nick == it->get_nick())
        {
            return (index);
        }
        it++;
        index++;
    }
    return -1;
}

//Fonction pour voir si le channel existe
int	check_if_channel_exist(std::string channel_name, std::vector<class Channel> the_channel)
{
	if (the_channel.empty() == true)
		return (-1);
	int i = 0;
	channel_name = "#" + channel_name;
	for (std::vector<class Channel>::iterator it = the_channel.begin(); it != the_channel.end(); it++)
	{
		if (channel_name == it->get_name())
			return (i);
		i++;
	}
	return (-1);
}
