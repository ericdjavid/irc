#pragma once

#include <vector>
#include <string>
#include "server.hpp"
#include "tools.hpp"
#include "commands.hpp"
#include "channel.hpp"
#include <sys/socket.h> //send
#include "channel.cpp"

int ft_deal_with_commands(int index, int sd, the_serv *irc_serv, std::vector<std::string> buff_arr)
{
    int ret = 0;
    if (check_vector_arr(buff_arr, "PING localhost") > 0)
    {
	    // TODO FIX PONG, not working
	    // client_printer(sd, "PONG localhost", "371", "edj");
	    send(sd, "PONG :localhost\r\n", 15, 0);
        //send(sd, "PONG :localhost\r\n", 371, 0);
	    return (0);
    }
    // ? JOIN
    if ((ret = check_vector_arr(buff_arr, "JOIN")) > 0)
    {
        std::string     c_name = buff_arr[0];
        std::string     chann_name = c_name.substr(5, c_name.length() - 5);
        if (compare_to_existing_channels(chann_name, irc_serv->the_channel) == 0)
        {
            if (verify_channel_name(chann_name, irc_serv->the_channel) == 0)
            {
                const char    *reference;
                std::vector<User> users;

                reference = chann_name.c_str();
                class Channel tmp(chann_name, users, reference[0]);
                irc_serv->the_channel.push_back(tmp);
            }
            else{
                //MSG ERREUR NOM DE CHANN
                return (1);
            }
        }
        int     i;
        i = get_index(irc_serv->the_users, sd);
        irc_serv->the_users[i].connect_to_channel(get_channel(chann_name, irc_serv->the_channel));
        Channel *tmp2 = get_channel(chann_name, irc_serv->the_channel);
        tmp2->add_user(&(irc_serv->the_users[i]));
        //CONNECT TO CHANNEL
        std::cout << "JOIN called" << std::endl;
    }

    // ?BAN

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
