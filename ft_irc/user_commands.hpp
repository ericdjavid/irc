#pragma once
#include <vector>
#include <string>
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

    // ?PART
    if ((ret = check_vector_arr(buff_arr, "PART")) > 0)
    {
        t_part      test;

        std::cout << "PART called" << std::endl;
        std::string command = buff_arr.at(ret -1).substr(6);
        test = split_part_command(command.c_str());

        show_data_parsed_part(test);
        free_t_part(test);
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
        std::string msg = buff.substr(buff.find(':'));
        // std::cout << "target is " << target << std::endl;
        // std::cout << "msg is " << msg << std::endl;
        if (buff[0] == '#')
        {
            std::cout << "Someone is trying to write inside a channel" << std::endl;
            // CHECK IF CHANNEL EXIST

            if (get_channel(target, irc_serv->the_channel) >= 0)
            {
                std::cout << "channel found, sending the msg to others" << std::endl;


            }
            else
            {
                std::cout << "Channel not found" << std::endl;
                return 0;
            }

            // IF YES SEND MSG TO ALL USERS


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
