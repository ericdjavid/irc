#pragma once
#include <string.h>
#include <iostream>
#include <vector>
#include "user.hpp"
#include "channel.hpp"
#include <sys/time.h>       //FD_SET, FD_ISSET, FD_ZERO macros
#include "server.hpp"
#include "tools.hpp"
#include "user_commands.hpp"

void ft_join_channel(char* buff, the_serv *irc_serv)
{
	if (!(irc_serv->the_channel.empty()))
	{
		// Check if chan exists
		std::vector<Channel>::iterator channs = irc_serv->the_channel.begin();
		std::string     channel_name(buff);
		while (channs->get_name() != channel_name && channs != irc_serv->the_channel.end())
		{
			channs++;
		}
	}

	// if not, add the channel
	std::cout << "Server: channel does not exist, creating it\n";
	for (int i = 0; i < 4; i++)
		buff++;
	std::string name(buff); 
	irc_serv->the_channel.push_back(Channel(buff));
}

bool ft_check_password(std::vector<std::string> buff_arr, the_serv *irc_serv, int sd)
{
	int ret = 0;
	std::string nick;
	std::string user;
	std::string tmp_user("edjavid");
	if ((ret = check_vector_arr(buff_arr, "PASS")) > 0)
	{ 
		ret -= 1;
		std::string pass = buff_arr.at(ret).substr(5);
		std::cout << "Pass is " << pass << std::endl;
		if (!pass.compare(irc_serv->password))
		{
			client_printer(sd, "Good password entered =)", "371", tmp_user);
			return true;
		}
		else
		{
			std::cout << "Wrong password entered =(" << std::endl;
			return false;
		}
	}
	else
	{
		client_printer(sd, "No password set up, please connect with password", "471", "EDJAV");
		return false;
	}
	return false;
}

void ft_deal_next(std::vector<std::string> buff_arr, the_serv *irc_serv, int sd)
{

	std::string nick;
	std::string user;
	int ret = 0;
	if ((ret = check_vector_arr(buff_arr, "NICK")) > 0)
	{
		nick = buff_arr.at(ret - 1).substr(5);
		std::cout << "nick is " << nick << std::endl;
		ret = check_vector_arr(buff_arr, "USER");
		user = buff_arr.at(ret - 1).substr(5);
		std::cout << "user is " << user << std::endl;
		std::string msg = nick + user;
		client_printer(sd, msg, "001", user);
		std::string the_str("Your host is localhost, running version 1");
		client_printer(sd, the_str, "002", user);
		client_printer(sd, "This localhost was created at [add hour]", "003", user);
		if (ft_check_password(buff_arr, irc_serv, sd) == true)
		{
			if (nick_already_in_use(nick, irc_serv->the_users) == 0)
			{
				std::cout << "creating user..." << std::endl; 
				class User tmp(sd, nick, user);
				irc_serv->the_users.push_back(tmp);
			}
			else{
				std::cout << "user not created, nick already in use" << std::endl;
				//DISCONNECT CLIENT HERE
			}
			std::cout << "||||||||||||| USERS |||||||||||||" << std::endl;
			display_users(irc_serv->the_users);
			std::cout <<  " ||||||||||||| END |||||||||||||" << std::endl;
		}
	}
}


int ft_treat_commands(std::vector<std::string> buff_arr, the_serv *irc_serv, int sd)
{
	int ret = 0;
	if ((ret = check_vector_arr(buff_arr, "CAP LS")) > 0)
	{
		char const *cap_ls = "CAP * LS :\r\n";
		send(sd , cap_ls , strlen(cap_ls) , 0 );
		std::cout << "Buff arr size is " << buff_arr.size() << std::endl;
		if (buff_arr.size() == 1)
		{
			std::cout << "Nothing after CAP LS, next" << std::endl;
			return 1;
		}
		else
		{
			// DEAL NEXT
			ft_deal_next(buff_arr, irc_serv, sd);
		}
	}
	
	// CHECK IF SD IS IN THE LIST OF USER
	// std::cout << "sd = " << sd << std::endl;
	if ((ret = check_if_user_exist(sd, irc_serv->the_users)) > 0)
	{
		// TODO? CHECK OTHER COMMANDS LIKE JOIN
		// std::cout << "The user with the same fd exists so let's not look for the connexion stuffs" << std::endl;
		// class User *the_user = &irc_serv->the_users.at(ret -1);
		// class User the_user = irc_serv->the_users.at((size_t)ret -1);

		// THE PROBLEM COMES FROM THE RET VALUE WHICH IS SD AND NOT INDEX
		class User tmp(300, "lol", "lol");

		if (!ft_deal_with_commands(tmp, sd, irc_serv, buff_arr))
			return 1;
		return 2;

	}
	else
	{
		std::cout << "user don't exist, let's start the connexion process!" << std::endl;
		ft_deal_next(buff_arr, irc_serv, sd);
	}
	return 0;
}