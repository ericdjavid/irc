#pragma once
#include <vector>
#include "../server.hpp"
#include "../user.hpp"
#include "../channel.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include "./quit.hpp"
#include "../tools.hpp"

int ft_kill(User *user, std::string cmd, the_serv *irc_serv)
{
    if (check_partial_cmd(cmd, 5))
    {
        if (debug)
            std::cout << C_RED << "Partial CMD =(" << C_END;
        return 0;
    }
    if (user->is_operat() == false)
    {
        if (debug)
            std::cout << C_RED << "User is not operator" << C_END;
        return (0);
    }
    else
    {
        std::string target = cmd.substr(5);
        std::string reason = "";
        std::string nick = target.substr(0, target.find(" "));
        if (target.size() > target.find(":"))
            reason = target.substr(target.find(":"));
        if (debug)
            std::cout << C_BLUE << "Nick is " << nick << " and reason is " << reason << C_END;
         
        if (int ret = check_if_user_exist_with_nick(nick, irc_serv->the_users) >= 0)
        {
            // SEND KILL MSG 361
            ft_quit(irc_serv, get_index(irc_serv->the_users, irc_serv->the_users.at(ret).get_id()), irc_serv->the_users.at(ret).get_id());
            return (0);
        }
        else
        {
            if (debug)
                std::cout << C_RED << "User not found" << C_END;
        }
    }
    return (0);
}