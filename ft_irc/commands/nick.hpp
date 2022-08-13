
#pragma once
#include <vector>
#include "../server.hpp"

void nick_command(std::string nick, int index, the_serv *irc_serv)
{
    // TODO if nick is ok
    if (check_if_user_exist_with_nick(nick, irc_serv->the_users) == -1)
    {
        irc_serv->the_users.at(index).set_the_nick(nick);
        std::cout << "Nick changed" << std::endl;
        return;
    }
    else
    {
        std::cout << "Sorry but nick exists";
        return;
    }
}

void username_command(std::string username, int index, the_serv *irc_serv)
{
    // TODO if username is ok
    if (true)
    {
        irc_serv->the_users.at(index).set_username(username);
        std::cout << "username changed" << std::endl;
    }
    return;
}