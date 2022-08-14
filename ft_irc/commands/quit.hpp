
#pragma once
#include <vector>
#include "../server.hpp"
#include "../user.hpp"
#include <sys/types.h>
#include <sys/socket.h>

int ft_quit(the_serv *irc_serv, int index, int sd)
{
    // :Eric_!~Eric@62.210.32.149 QUIT :"leaving"
    if (index == -1)
        return (1);
    std::string resp = ":" + irc_serv->the_users.at(index).get_nick() + "!~" + irc_serv->the_users.at(index).get_username() + "@localhost QUIT :\"leaving\"\r\n";
    std::cout << resp << std::endl;
    if (send(sd, resp.c_str(), resp.length(), 0) == -1)
        std::cout << "Problem with quit send" << std::endl;
    delete_from_list(irc_serv, sd);
    return (1);
}