#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "server.hpp"
#include "tools.hpp"
#include "commands.hpp"
#include <sys/socket.h> //send

int ft_deal_with_commands(int index, int sd, the_serv *irc_serv, std::vector<std::string> buff_arr)
{
    int ret = 0;
    if (check_vector_arr(buff_arr, "PING localhost") > 0)
    {
	    // TODO FIX PONG, not working
	    // client_printer(sd, "PONG localhost", "371", "edj");
	    send(sd, "PONG :localhost\r\n", 15, 0);
	    return (0);
    }
    // ? JOIN
    if ((ret = check_vector_arr(buff_arr, "JOIN")) > 0)
    {
        std::cout << "JOIN called" << std::endl;
    }

    // ?BAN
    if ((ret = check_vector_arr(buff_arr, "BAN"))> 0)
    {
	std::cout << "You are being ban" << std::endl;
    }
	//Kick
	if ((ret = check_vector_arr(buff_arr, "KICK")) > 0)
	{
	    //KICK USERNAME OR NICK???
		int i;
		std::cout << "You are being kick" << std::endl;

		std::string test = buff_arr.at(ret - 1).substr(6);	
		std::cout << "IT " << test << std::endl;
		std::string channel = test.substr(0, test.find(' '));
		std::cout << "channel _______ " << channel << std::endl;
		size_t pos = test.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789");
		std::string channel_kick = test.substr(pos);
		channel_kick.resize(channel_kick.find(':'));
		std::cout << "kick channel _______ " << channel_kick << "______" << std::endl;
		std::string target = test.substr(test.find(':'));
		target = target.substr(1);
		std::cout << "target _______ " << target << std::endl;

		if ((i = check_if_channel_exist(channel_kick, irc_serv->the_channel)) == -1)
			std::cout << "///////////////////error no channel///////////////////////\n";
		else
		{
			if ((i = check_if_user_to kick_exit())
		}
	}

    if ((ret = check_vector_arr(buff_arr, "INVITE")) > 0)
    {
	std::cout << "You are being invited" << std::endl;
    }

    // ? PRIVMSG
    if ((ret = check_vector_arr(buff_arr, "PRIVMSG")) > 0)
    {
        std::cout << "PRIVMSG called" << std::endl;
        std::string buff = buff_arr.at(ret - 1).substr(8);
        std::cout << "Buff is " << buff << std::endl;
        std::string target = buff.substr(0, buff.find(' '));
        std::string msg = buff.substr(buff.find(':'));
        std::cout << "target is " << target << std::endl;
        std::cout << "msg is " << msg << std::endl;
        // CHECK IF TARGET EXISTS
        if (check_if_user_exist_with_nick(target, irc_serv->the_users) > 0)
        {
            std::cout << "the user " << target << " exists =) , sending msg" << std::endl;
            std::string endmsg = irc_serv->the_users.at(index).get_nick() + " PRVMSG " + target + msg;
            // client_printer(irc_serv->the_users.at(check_if_user_exist_with_nick(target, irc_serv->the_users)).get_id(), endmsg, 0, target );
            int target_id = irc_serv->the_users.at(check_if_user_exist_with_nick(target, irc_serv->the_users)).get_id();
            std::cout << "ID of " << target << " is " << target_id << std::endl;
            // TODO! LE PREMIER MSG NE S ENVOIE PAS, A FIX
            client_printer(target_id, endmsg, "371", target);
            

        }
        else
            std::cout << "the user don't exist =(" << std::endl;        
    }

    return (0);





}
