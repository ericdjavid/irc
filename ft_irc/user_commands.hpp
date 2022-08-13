#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "server.hpp"
#include "tools.hpp"
#include "commands.hpp"
#include "channel.hpp"
#include <sys/socket.h> //send
#include "part.hpp"
#include "./commands/nick.hpp"

int ft_deal_with_commands(int index, int sd, the_serv *irc_serv, std::vector<std::string> buff_arr)
{
    int ret = 0;
    // ? QUIT
    if (check_vector_arr(buff_arr, "QUIT") > 0)
    {
        delete_from_list(irc_serv, sd);
	    return (1);
    }
    // ? NICK
    if ((ret = check_vector_arr(buff_arr, "NICK")) > 0)
        nick_command(buff_arr.at(ret - 1).substr(5), index, irc_serv);
    if ((ret = check_vector_arr(buff_arr, "USERNAME")) > 0)
        username_command(buff_arr.at(ret - 1).substr(9), index, irc_serv);

    // ? PONG
    if (check_vector_arr(buff_arr, "PONG localhost") > 0)
    {
        // ? PING
        sleep(3);
        std::string PING("PING localhost\r\n");
	    if (send(sd,PING.c_str(), PING.size(), 0) == -1)
        {
            std::cout << "Problem with PING send" << std::endl;
        }
	    return (0);
    }
    // ?MODE

    std::string mod1 = "MODE " + irc_serv->the_users.at(get_index(irc_serv->the_users, sd)).tmp;
    if ((ret = check_vector_arr(buff_arr, mod1)) > 0)
    {
        std::cout << "MODE1" << std::endl;
        std::string resp = ":localhost 324 " + irc_serv->the_users.at(index).get_nick() + " " + irc_serv->the_users.at(get_index(irc_serv->the_users, sd)).tmp + " +stn\r\n";
        std::cout << resp << std::endl;
	    if (send(sd,resp.c_str(), resp.length(), 0) == -1)
        {
            std::cout << "Problem with join send" << std::endl;
        }
        std::string resp_mod = ":" + irc_serv->the_users.at(index).get_nick() + "!~" + irc_serv->the_users.at(index).get_username() + "@localhost" + " JOIN :" + irc_serv->the_users.at(get_index(irc_serv->the_users, sd)).tmp + "\r\n";
        std::cout << resp_mod << std::endl;
	    if (send(sd,resp_mod.c_str(), resp_mod.length(), 0) == -1)
        {
            std::cout << "Problem with join send" << std::endl;
        }
    }

    std::string mod2 = "MODE " + irc_serv->the_users.at(get_index(irc_serv->the_users, sd)).tmp + " b";
    if ((ret = check_vector_arr(buff_arr, mod2)) > 0)
    {
        std::cout << "MODE2" << std::endl;
        std::string resp = ":localhost 368 " + irc_serv->the_users.at(index).get_nick() + " " + irc_serv->the_users.at(get_index(irc_serv->the_users, sd)).tmp + " :End of Channel Ban List\r\n";
        std::cout << resp << std::endl;
	    if (send(sd,resp.c_str(), resp.length(), 0) == -1)
        {
            std::cout << "Problem with join send" << std::endl;
        }
    }

    if ((ret = check_vector_arr(buff_arr, "WHO")) > 0)
    {
        std::string resp2 = ":localhost 329 " + irc_serv->the_users.at(index).get_nick() + " " + irc_serv->the_users.at(get_index(irc_serv->the_users, sd)).tmp + " 1603137669\r\n";
	    if (send(sd,resp2.c_str(), resp2.length(), 0) == -1)
        {
            std::cout << "Problem with join send" << std::endl;
        }
        resp2 = ":localhost 352 " + irc_serv->the_users.at(index).get_nick() + " " + irc_serv->the_users.at(get_index(irc_serv->the_users, sd)).tmp + " ~" + irc_serv->the_users.at(index).get_nick() + " localhost " + irc_serv->the_users.at(index).get_nick() + " H :0 PCname\r\n";
        std::cout << resp2 << std::endl;
	    if (send(sd,resp2.c_str(), resp2.length(), 0) == -1)
        {
            std::cout << "Problem with join send" << std::endl;
        }

        std::string resp3 = ":localhost 315 " + irc_serv->the_users.at(index).get_nick() + " " + irc_serv->the_users.at(get_index(irc_serv->the_users, sd)).tmp + " :End of /WHO list.\r\n"; 
        std::cout << resp3 << std::endl;
	    if (send(sd,resp3.c_str(), resp3.length(), 0) == -1)
        {
            std::cout << "Problem with join send" << std::endl;
        }
    }


    // ? JOIN
    if ((ret = check_vector_arr(buff_arr, "JOIN")) > 0)
    {
        std::string     c_name = buff_arr[0];
        std::string     chann_name = c_name.substr(5, c_name.length() - 5);
        int             index2 = 0;

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
                std::string join = ":" + irc_serv->the_users.at(index).get_nick() + "!~" + irc_serv->the_users.at(index).get_username() + "@localhost" + " JOIN :" + chann_name + "\r\n";
                std::cout << "text is " << join << std::endl;
	            if (send(sd,join.c_str(), join.length(), 0) == -1)
                {
                    std::cout << "Problem with join send" << std::endl;
                }
                std::string join2 = ":localhost 353 " + irc_serv->the_users.at(index).get_nick() + " @ " + chann_name + " : " + irc_serv->the_users.at(index).get_nick() + " @mage\r\n";
                std::cout << "text is " << join2 << std::endl;
	            if (send(sd,join2.c_str(), join2.length(), 0) == -1)
                {
                    std::cout << "Problem with join send" << std::endl;
                }
                std::string join3 = ":localhost 366 " + irc_serv->the_users.at(index).get_nick() + " " + chann_name + " :End of /NAMES list.\r\n";
	            if (send(sd,join3.c_str(), join3.length(), 0) == -1)
                {
                    std::cout << "Problem with join send" << std::endl;
                }
                std::cout << "text is " << join3 << std::endl;
                irc_serv->the_users.at(index).tmp = chann_name;
                return 0;
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
			std::cout << "ERR_NOSUCHCHANNEL || 403\n";
		else
		{
			int channel_id = get_channel(channel_kick, irc_serv->the_channel);
			if ((i = check_if_user_exist_with_nick(target, irc_serv->the_users)) != -1)
			{
				if (( i = check_if_user_exist_in_channel(target, irc_serv->the_channel.at(channel_id).get_users())) == -1 )
					std::cout << "ERR_USERNOTINCHANNEL || 441\n";
				else
				{
					std::string kicker = get_user_name(sd, irc_serv->the_channel.at(channel_id).get_users());
					if (( i = check_if_user_exist_in_channel(kicker, irc_serv->the_channel.at(channel_id).get_users())) == -1 )
						std::cout << " ERR_USERNOTINCHANNEL || 441" << std::endl;
					else
					{
						std::string endmsg;
						if (reason.empty() == false)
            				endmsg = irc_serv->the_users.at(index).get_nick() + " KICK " + target + reason;
						else
            				endmsg = irc_serv->the_users.at(index).get_nick() + " KICK " + target;
						client_printer2(sd, &irc_serv->the_users.at(get_index(irc_serv->the_users, sd)), endmsg, 0, target);
						kick_user_out_from_channel(target, irc_serv->the_channel.at(channel_id).get_users_ptr());
					}
				}
			}
			else
				std::cout << "ERR_USERNOTINCHANNEL || 441\n";
		}
	}

	// ? Invite
    if ((ret = check_vector_arr(buff_arr, "INVITE")) > 0)
    {
		int i;
		std::cout << "You are being invited" << std::endl;
		std::string test = buff_arr.at(ret - 1).substr(7);
		std::string buff = test;
std::cout << test << std::endl;
		std::string	target = test.substr(0, test.find(' '));
std::cout << target << "--------" << std::endl;
		size_t target_len = target.size();
		std::string channel_invite = buff.erase(0, target_len);
		channel_invite.erase(0, 1);
std::cout << channel_invite << "-------- channel_invite" << std::endl;
		if (channel_invite.empty() == true)
			client_printer(sd, ":Not enough parameters", "461", "Invite");
		if ((i = check_if_channel_exist(channel_invite, irc_serv->the_channel)) == -1)
			client_printer(sd, ":No such nick/channel", "401", buff_arr.at(index));
		else
		{
			if ((i = check_if_user_exist_with_nick(target, irc_serv->the_users)) != -1)
			{
				std::cout << channel_invite << " " <<target << std::endl;
			}
			else
				client_printer(sd, ":No such nick/channel", "401", buff_arr.at(index));
    	}
	}

	// ? Notice
	if ((ret =  check_vector_arr(buff_arr, "NOTICE")) > 0)
	{
		int i;
		std::cout << "NOTICE called" << std::endl;
		std::string buff = buff_arr.at(ret - 1).substr(7); 
std::cout << "buff-" << buff << "----" << std::endl;
		std::string target = buff.substr(0, buff.find(' '));
std::cout << "Target --" << target << "------" << std::endl;
		std::string message = buff.substr(target.size());
		message = message.substr(2);
std::cout << "Message--" << message << "---" << std::endl;
		if ((i = check_if_many_user(target)) == 1)
		{
std::cout << "one user" << i << "----"<<  std::endl;	
			if ((i = check_if_user_exist_with_nick(target, irc_serv->the_users)) >= 0)
			{
std::cout << "the user " << target << " exists =) , sending msg" << std::endl;
				std::string endmsg = irc_serv->the_users.at(index).get_nick() + " NOTICE " + target + message;
				// client_printer(irc_serv->the_users.at(check_if_user_exist_with_nick(target, irc_serv->the_users)).get_id(), endmsg, 0, target );
				int target_id = irc_serv->the_users.at(check_if_user_exist_with_nick(target, irc_serv->the_users)).get_id();
std::cout << "ID of " << target << " is " << target_id << std::endl;
				// TODO! LE PREMIER MSG NE S ENVOIE PAS, A FIX
				client_printer(target_id, endmsg, "371", target);
			}
		}
		else
		{
			std::vector<std::string> targets;
			targets = get_everyone(target, i);
std::cout << "many users" << i << "----" << std::endl;
//for (size_t it = 0; it != targets.size(); it++)
//	std::cout << targets.at(it) << std::endl;
			for (size_t it = 0; it != targets.size(); it++)
			{
std::cout << targets.at(it) << std::endl;
        		if (check_if_user_exist_with_nick(target, irc_serv->the_users) >= 0)
				{
					std::string sev_msg = irc_serv->the_users.at(index).get_nick() + " NOTICE " + targets.at(it) + message;
					int target_sev = irc_serv->the_users.at(check_if_user_exist_with_nick(targets.at(it), irc_serv->the_users)).get_id();
					client_printer(target_sev, sev_msg, "371", targets.at(it));
				}
			}
		}
	}

    // ?PART
    if ((ret = check_vector_arr(buff_arr, "PART")) > 0)
    {
        t_part2      test;

        std::cout << "PART called" << std::endl;
        std::string user_to_delete;
        int         channel_to_target;
        std::string command = buff_arr.at(ret -1).substr(6);
        std::string response;
        int         count = 0;

        test = split_part_command(command);
        while (count < test.nb_chann)
        {
            channel_to_target = get_channel(test.channels.at(count), irc_serv->the_channel);
            if (channel_to_target == -1)
            {
                std::cout << "ERR_NOSUCHCHANNEL (403)" << std::endl;
            }
            else {
                user_to_delete = get_user_name(sd, irc_serv->the_channel.at(channel_to_target).get_users());
            }
            if (user_to_delete == "/*,\\not_in_channel")
            {
                std::cout << "ERR_NOTONCHANNEL (442)" << std::endl;
            }
            else if (channel_to_target != -1 && user_to_delete != "/*,\\not_in_channel")
            {
                kick_user_out_from_channel(user_to_delete, irc_serv->the_channel.at(channel_to_target).get_users_ptr());
                response = get_response_1(sd, irc_serv->the_users, buff_arr.at(ret -1), irc_serv, &(irc_serv->the_channel.at(channel_to_target)));
                std::cout << "RESPONSE : |" << response << "|" << std::endl;
                send(sd, response.c_str(), response.length(), 0);
                // send(sd, response.c_str(), response.length(), 0);
            }
            //DISCONNECT CURRENT USER FROM test.channel
            count++;
        }
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
        // display_users(irc_serv->the_users);
        std::string buff = buff_arr.at(ret - 1).substr(8);
        std::cout << "Buff is " << buff << std::endl;
        std::string target = buff.substr(0, buff.find(' '));
        if (buff.find(':') == std::string::npos)
        {
            std::cout << "error in command" << std::endl;
            return 1;
            // error("PRIVMSG command error");
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

                send_message_to_channel(irc_serv->the_channel[chan -1], msg, sd);

            }
            else
            {
                std::cout << "Channel not found" << std::endl;
                return 0;
            }

            return 1;
        }
        // CHECK IF TARGET EXISTS
        if (check_if_user_exist_with_nick(target, irc_serv->the_users) >= 0)
        {
            std::cout << "the user " << target << " exists =) , sending msg" << std::endl;
            std::string endmsg = "PRVMSG " + target + msg;
            // client_printer(irc_serv->the_users.at(check_if_user_exist_with_nick(target, irc_serv->the_users)).get_id(), endmsg, 0, target );
            int target_id = irc_serv->the_users.at(check_if_user_exist_with_nick(target, irc_serv->the_users)).get_id();
            std::cout << "ID of " << target << " is " << target_id << std::endl;
            // TODO! LE PREMIER MSG NE S ENVOIE PAS, A FIX
            // TODO GERER LES ERREURS
            // client_printer(target_id, endmsg, "371", target);
            client_printer2(target_id, &irc_serv->the_users.at(get_index(irc_serv->the_users, sd)), endmsg, "0", target);
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
