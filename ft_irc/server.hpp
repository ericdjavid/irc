#pragma once

#include "user.hpp"
#include "channel.hpp"
#include <vector>

struct server
{
    std::vector<Channel> the_channel;
    std::vector<User> the_users;
    std::string password;
    std::string port;

} typedef the_serv;


// FONCTION POUR PARCOURIR LA LISTE DES USERS, RENVOIE NULL SI PAS TROUVE, SINN ID DE L USER
int 	check_if_user_exist(int sd, std::vector<class User> users)
{
    if (users.empty())
        return 0;
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

std::vector<User>::iterator     get_iterator(std::vector<class User> user_list, int id)
{
    std::vector<User>::iterator ret = user_list.end();
    if (user_list.empty() == true)
        return ret;
    std::vector<class User>::iterator it = user_list.begin();
    while(it != user_list.end())
    {
        if (id == it->get_id())
            return it;
        it++;
    }
    return ret;

}

// FONCTION POUR TROUVER INDEX USER
int     get_index(std::vector<class User> user_list, int id)
{
    if (user_list.empty())
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
    return -1;

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
        if (nick == it->get_nick())
            return (index);
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
	for (std::vector<class Channel>::iterator it = the_channel.begin(); it != the_channel.end(); it++)
	{
std::cout << "Channel name ==>" << channel_name << "---chanel is ==>" << it->get_name() << "----\n";
		if (channel_name == it->get_name())
			return (i);
		i++;
	}
	return (-1);
}

void delete_from_list(the_serv *irc_serv, int sd)
{
        std::cout << "Deleting sd from list if exists" << std::endl;
        int ind = get_index(irc_serv->the_users, sd);
        if (ind >= 0)
        {
            std::vector<class User>::iterator it = irc_serv->the_users.begin();
            irc_serv->the_users.erase(it + ind);
        }
	    return;
}

std::string	get_response_1(int	id, std::vector<User> tab, std::string command_name, the_serv *serv, Channel *chan)
{
	std::vector<User>::iterator	it = tab.begin();
	std::string					response;
    (void)chan;
    (void)serv;
	while(it != tab.end())
	{
		if(it->get_id() == id)
		{
			std::cout << "GET RESPONSE : |" << it->get_nick() << "| |" << it->get_username() << "|" << std::endl;
			response = ":" + it->get_nick() + "!~" + it->get_username() + "@localhost" + " " + command_name + "\r\n";
			break ;
		}
		it++;
	}
	return (response);
}