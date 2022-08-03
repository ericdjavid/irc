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


// FONCTION POUR PARCOURIR LA LISTE DES USERS, RENVOIE NULL SI PAS TROUVE, SINN INDEX DE L USER
int 	check_if_user_exist(int sd, std::vector<class User> users)
{
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
