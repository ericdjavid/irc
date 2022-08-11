#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "server.hpp"
#include "tools.hpp"
#include "commands.hpp"
#include "channel.hpp"
#include <sys/socket.h> //send
#include "channel.cpp"
#include "part.cpp"

int ft_deal_with_commands(int index, int sd, the_serv *irc_serv, std::vector<std::string> buff_arr)
{
    int ret = 0;
    // ? QUIT
    
    if (check_vector_arr(buff_arr, "QUIT") > 0)
    {
        delete_from_list(irc_serv, sd);
	    return (1);
    }



    // ? PONG
    if (check_vector_arr(buff_arr, "PING localhost") > 0)
    {
        std::string PONG(":localhost PONG localhost :localhost");
	    send(sd,":localhost PONG localhost :localhost", PONG.size(), 0);
	    return (0);
    }
    // ? JOIN
    if ((ret = check_vector_arr(buff_arr, "JOIN")) > 0)
    {
        std::string     c_name = buff_arr[0];
        std::string     chann_name = c_name.substr(5, c_name.length() - 5);
        int     index2 = 0;

        // IF USER IS ALREADY IN A CHANNEL, HE CAN T CREATE ANOTHER ONE
        if (compare_to_existing_channels(chann_name, irc_serv->the_channel) == 0)
        {
            if (verify_channel_name(chann_name, irc_serv->the_channel) == 0)
            {
                // USER IS CREATING A CHANNEL
                const char    *reference;
                std::vector<User> users;
                reference = chann_name.c_str();
                class Channel tmp(chann_name, users, reference[0]);
                tmp.add_user(irc_serv->the_users[index]);
                irc_serv->the_channel.push_back(tmp);
                irc_serv->the_users.at(index).set_operat(true);
            }
            else
            {
                std::cout << "Bad syntax for channel's name/Name already taken" << std::endl;
                return (1);
            }
        }
        else
        {
            index2 = get_channel(chann_name, irc_serv->the_channel);
            irc_serv->the_channel.at(index2).add_user(irc_serv->the_users[index]);

        }
        //DISPLAY INFOS ABOUT CHANNELS AND USER
        std::cout << "Channels are as following :" << std::endl;
        print_channels(irc_serv->the_channel);
        std::cout << "Users in channel " << irc_serv->the_channel.at(index2).get_name() << " are as following :" << std::endl;
        display_users(irc_serv->the_channel.at(index2).get_users());
    }
    // ?BAN
    if ((ret = check_vector_arr(buff_arr, "BAN"))> 0)
    {
	std::cout << "You are being ban" << std::endl;
	int i;
	std::string test = buff_arr.at(ret - 1).substr(6);	
	std::cout << "IT " << test << std::endl;
	std::string channel_ban = test.substr(0, test.find(' '));
	std::cout << "channel _______" << channel_ban << std::endl;
	size_t pos = test.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789");
	std::string target = test.substr(pos);
	target.resize(target.find(':'));
	target.erase(0,1);
	target = target.substr(0, target.size()-1);
//	channel_kick.pop_back();
	std::cout << "target _______ " << target << "______" << std::endl;
	std::string reason = test.substr(test.find(':'));
	reason = reason.substr(1);
	std::cout << "reason _______ " << reason << std::endl;
	channel_ban = "#" + channel_ban;

	if ((i = check_if_channel_exist(channel_ban, irc_serv->the_channel)) == -1)
		std::cout << "///////////////////error no channel///////////////////////\n";
	else
	{
		int channel_id = get_channel(channel_ban, irc_serv->the_channel);
		if ((i = check_if_user_exist_with_nick(target, irc_serv->the_users)) != -1)
		{
			if (( i = check_if_user_exist_in_channel(target, irc_serv->the_channel.at(channel_id).get_users())) == -1 )
				std::cout << "11111111111User is not in the channel\n";
			else
				ban_user_out_from_channel(target, irc_serv->the_channel.at(channel_id).get_users(), irc_serv->the_channel.at(channel_id).get_ban_users());
		}
		else
			std::cout << "No user!!!!\n" << i << std::endl;
	}
    }
	//Kick
	if ((ret = check_vector_arr(buff_arr, "KICK")) > 0)
	{
	    //KICK USERNAME OR NICK???
		int i;
		std::cout << "You are being kick" << std::endl;

		std::string test = buff_arr.at(ret - 1).substr(6);	
		std::string channel_kick = test.substr(0, test.find(' '));
		size_t pos = test.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789");
		std::string target = test.substr(pos);
		target.resize(target.find(':'));
		target.erase(0,1);
		target = target.substr(0, target.size()-1);
//		channel_kick.pop_back();
		std::string reason = test.substr(test.find(':'));
		reason = reason.substr(1);
std::cout << "reason _______ " << reason << std::endl;
		channel_kick = "#" + channel_kick;
		if ((i = check_if_channel_exist(channel_kick, irc_serv->the_channel)) == -1)
			std::cout << "///////////////////error no channel///////////////////////\n";
		else
		{
			int channel_id = get_channel(channel_kick, irc_serv->the_channel);
			if ((i = check_if_user_exist_with_nick(target, irc_serv->the_users)) != -1)
			{
				if (( i = check_if_user_exist_in_channel(target, irc_serv->the_channel.at(channel_id).get_users())) == -1 )
					std::cout << "11111111111User is not in the channel\n";
				else
					kick_user_out_from_channel(target, irc_serv->the_channel.at(channel_id).get_users());
			}
			else
				std::cout << "No user!!!!\n" << i << std::endl;
		}
	}

    if ((ret = check_vector_arr(buff_arr, "INVITE")) > 0)
    {
	std::cout << "You are being invited" << std::endl;
    }

    // ?PART
    if ((ret = check_vector_arr(buff_arr, "PART")) > 0)
    {
        t_part2      test;

        std::cout << "PART called" << std::endl;
        std::string command = buff_arr.at(ret -1).substr(6) + '\0';
        test = split_part_command(command);
//        if (test.nb_chann == 0)
//        {
            // int     channel_to_target = get_channel(test.channel, irc_serv->the_channel);
            // User    user_to_delete = get_user_to_delete(sd, irc_serv->the_channel.at(channel_to_target).get_users());

            // irc_serv->the_channel.at(channel_to_target).get_users().erase(get_user_position(sd, irc_serv->the_channel.at(channel_to_target).get_users()));
            // std::string response = ":" + user_to_delete.get_nick() + "!" + user_to_delete.get_username() + "@localhost PART :" + irc_serv->the_channel.at(channel_to_target).get_name() +" :" + test.reason;
            // int     check = send(sd, response.c_str(), response.length(), 0);
            // std::cout << "CHECK VALUE : " << check << std::endl;
            //DISCONNECT CURRENT USER FROM test.channel
//        }
//        else{
            //DISCONNECT CURRENT USER FROM test.channels[all]
//        }
        show_data_parsed_part(test);
        // free_t_part(test);
        /*
        DOC:
            - https://dd.ircdocs.horse/refs/commands/part

        INFOS:
            - format de la commande : PART <channel>{,<channel>} [<reason>]
            - codes erreur a retourner : ERR_NOSUCHCHANNEL (403) | ERR_NOTONCHANNEL (442)

        A FAIRE:
            - verifier le nombre de channels a quitter
            - verifier que le(s) channel(s) existe(nt)
            - retirer l'utilisateur de la liste des users du/des chann(s)
            - envoyer un message aux channels indiquant que l'utilisateur a quitte le chann + reason
        */
    }
    // ? PRIVMSG
    if ((ret = check_vector_arr(buff_arr, "PRIVMSG")) > 0)
    {
        std::cout << "PRIVMSG called" << std::endl;
        std::string buff = buff_arr.at(ret - 1).substr(8);
        std::cout << "Buff is " << buff << std::endl;
        std::string target = buff.substr(0, buff.find(' '));
        if (buff.find(':') == std::string::npos)
        {
            error("PRIVMSG command error");
        }
        std::string msg = buff.substr(buff.find(':'));
        std::cout << "target is |" << target << "|" << std::endl;
        // std::cout << "msg is " << msg << std::endl;
        if (buff[0] == '#')
        {
            std::cout << "Someone is trying to write inside a channel" << std::endl;
            // CHECK IF CHANNEL EXIST
            if (int chan = get_channel(target, irc_serv->the_channel) >= 0)
            {
                std::cout << "channel found, sending the msg to others" << std::endl;
                // SEND THE MSG TO ALL THE USER LIST OF THE CHANNEL
                std::cout << "Chan is " << chan << std::endl;
                
                send_message_to_channel(irc_serv->the_channel[chan -1], msg);

            }
            else
            {
                std::cout << "Channel not found" << std::endl;
                return 0;
            }

            return 1;
        }
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

    // ? OPERATOR STAT
    if ((ret = check_vector_arr(buff_arr, "OPER")) > 0)
    {
        // BECORME OPERATOR
        std::cout << "OPERATOR called" << std::endl;
        std::string buff = buff_arr.at(ret - 1).substr(5);
        std::string user = buff.substr(0, buff.find(' '));
        std::string pswd = buff.substr(buff.find(' '));
        std::string pass = "YEAH";
        if (!pass.compare(pswd.substr(1,4)))
        {
            irc_serv->the_users.at(get_index(irc_serv->the_users, sd)).set_operat(true);
            std::cout << "User " << user << " set as operator" << std::endl;
        }
    }
    return (0);

}
