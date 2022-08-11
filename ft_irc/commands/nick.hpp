
#pragma once
#include <vector>
#include "../server.hpp"

int nick_command(std::string nick, int index, the_serv *irc_serv)
{
    // TODO if nick is ok
    if (true)
    {
        irc_serv->the_users.at(index).set_the_nick(nick);
        std::cout << "Nick changed" << std::endl;
        return (0);
    }
    else
        return (1);
}

int username_command(std::string username, int index, the_serv *irc_serv)
{
    // TODO if username is ok
    if (true)
    {
        irc_serv->the_users.at(index).set_username(username);
        std::cout << "username changed" << std::endl;
        return (0);
    }
    else
        return (1);
}