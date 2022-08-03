#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "server.hpp"
#include "tools.hpp"
#include "commands.hpp"
#include <sys/socket.h> //send

int ft_deal_with_commands(class User the_user, int sd, the_serv *irc_serv, std::vector<std::string> buff_arr)
{
    int ret = 0;
    if (check_vector_arr(buff_arr, "PING localhost") > 0)
    {
	    // TODO FIX PONG, not working
	    // client_printer(sd, "PONG localhost", "371", "edj");
	    send(sd, "PONG localhost\r", 15, 0);
	    return (0);
    }
    // ? JOIN
    if ((ret = check_vector_arr(buff_arr, "JOIN")) > 0)
    {
        std::cout << "JOIN called" << std::endl;
    }

    // ?BAN
    if ((ret = check_vector_arr(buff_arr, "BAN")))
    {
	std::cout << "You are being ban" << std::endl;
    }
	//Kick
    if ((ret = check_vector_arr(buff_arr, "KICK")))
    {
	    //KICK USERNAME OR NICK???
	    //std::string target = ;
	    std::cout << "You are being kick" << std::endl;
	    int i = 0;
	    std::vector<User>::iterator it = irc_serv->the_channel._users.begin();
	    while (it != irc_serv->the_users.end())
	    {
		if (sd == it->get_id())
			break;
		i++;
		it++;
	    }
	    it = irc_serv->the_users.begin();
	    irc_serv->the_channel.erase(it + i);
    }

    if ((ret = check_vector_arr(buff_arr, "INVITE")))
    {
	std::cout << "You are being invited" << std::endl;
    }

    // ? PRIVMSG
    if ((ret = check_vector_arr(buff_arr, "PRIVMSG")))
    {
        std::cout << "PRIVMSG called" << std::endl;
        std::string buff = buff_arr.at(ret - 1).substr(8);
        std::cout << "Buff is " << buff << std::endl;
        std::string target = buff.substr(0, buff.find(' '));
        std::string msg = buff.substr(buff.find(':'));
        std::cout << "target is " << target << std::endl;
        std::cout << "msg is " << msg << std::endl;
        // CHECK IF TARGET EXISTS
        if (check_if_user_exist_with_nick(the_user.get_nick(), irc_serv->the_users) == true)
            std::cout << "the user exists =)" << std::endl;
        else
            std::cout << "the user don't exist =(" << std::endl;        
    }

    return (0);





}
