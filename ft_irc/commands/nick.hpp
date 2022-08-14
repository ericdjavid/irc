
#pragma once
#include <vector>
#include "../server.hpp"
#include "../user.hpp"
#include "../debug.hpp"

int nick_command(std::string nick, int index, the_serv *irc_serv, int sd)
{
    // TODO check if nick is ok
    if (check_if_user_exist_with_nick(nick, irc_serv->the_users) == -1)
    {
        std::cout << "Nick changed" << std::endl;

        std::string resp = ":" + irc_serv->the_users.at(index).get_nick() + "!~" + irc_serv->the_users.at(index).get_username() + "@localhost NICK :" + nick + "\r\n";
        irc_serv->the_users.at(index).set_the_nick(nick);
        std::cout << "resp is |" << resp << "|" << std::endl;
        // :oldnickname!~username@localhost NICK :newnick\r\n;
	    if (send(sd,resp.c_str(), resp.length(), 0) == -1)
            std::cout << "Problem with join send" << std::endl;
        return (0);
    }
    else
    {
        // if already used
        // :localhost 443 nick_de_depart nick_demande :Nickname is already in use
        ultimate_printer(sd, nick + ":Nickname is already in use", "433", irc_serv->the_users.at(index).get_nick());
        std::cout << C_RED << " Sorry but nick exists" << C_END;
        return (0);
    }
}

int username_command(std::string username, int index, the_serv *irc_serv)
{
        irc_serv->the_users.at(index).set_username(username);
        std::cout << "Username changed" << std::endl;
    return (0);
}