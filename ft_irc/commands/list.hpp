#pragma once
#include <vector>
#include "../server.hpp"
#include "../user.hpp"
#include "../channel.hpp"
#include <sys/types.h>
#include <sys/socket.h>

int ft_list(std::string buff, the_serv *irc_serv, User *user)
{
    std::vector<Channel> tmp = irc_serv->the_channel;
    // all channels
    if (buff.size() == 5 || buff.size() == 4)
    {
        std::vector<Channel>::iterator it = tmp.begin();
        for (; it != tmp.end(); it++)
        {
            // :localhost 322 nickname nom_du_user 1 :\r\n;
            std::cout << it->get_name() << std::endl;
            ultimate_printer(user->get_id(), " " + it->get_name() + " 1 :", "322", user->get_nick());
        }
        // :localhost 323 nickname :End of LIST\r\n
        ultimate_printer(user->get_id(), " :End of LIST", "322", user->get_nick());
    }
    return (0);
}
