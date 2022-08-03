#pragma once
// #include <cstring>
#include <string.h>
#include <iostream>
#include <vector>
#include "user.hpp"
#include "channel.hpp"
#include <sys/time.h>       //FD_SET, FD_ISSET, FD_ZERO macros
#include "server.hpp"
#include "tools.hpp"

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

int check_vector_arr(std::vector<std::string> buff_arr, std::string target)
{
	int i = 0;
	for (std::vector<std::string>::iterator it = buff_arr.begin() ; it != buff_arr.end() ; ++it)
	{
		i++;
		size_t s = target.length();
		std::string new_str(*it);
		new_str = new_str.substr(0, s);
		// std::cout << "comparing:";
		// std::cout << new_str;
		// std::cout << " with:";
		// std::cout << target << std::endl;
		if (new_str.compare(target) == 0)
		{
			// int index = std::distance(buff_arr.begin(), it);
			// printf("ret = %d\n", i);
			return i;
		}
	}
	return 0;
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
	std::string tmp_user("edjavid");
	int ret = 0;
	if ((ret = check_vector_arr(buff_arr, "NICK")) > 0)
	{
		nick = buff_arr.at(ret - 1).substr(5);
		std::cout << "nick is " << nick << std::endl;

		ret = check_vector_arr(buff_arr, "USER");
		user = buff_arr.at(ret - 1).substr(5);
		std::cout << "user is " << user << std::endl;

		// if (nick_already_in_use(nick, irc_serv->the_users))
		// {
		// 	std::cout << "Nick already in use, please pick another one" << std::endl;
		// 	return (2);
		// }
		std::string msg = nick + user;
		client_printer(sd, msg, "001", tmp_user);
		std::string the_str("Your host is localhost, running version 1");
		client_printer(sd, the_str, "002", tmp_user);
		client_printer(sd, "This localhost was created at [add hour]", "003", tmp_user);
		if (ft_check_password(buff_arr, irc_serv, sd) == true)
		{
			if (nick_already_in_use(nick, irc_serv->the_users) == 0)
			{
				class User tmp(sd, nick, user);
				irc_serv->the_users.push_back(tmp);
			}
			else
			{
				perror("PBM with user allocation");
			}
			// std::cout << "||||||||||||| USERS |||||||||||||" << std::endl;
			// display_users(irc_serv->the_users);
			// std::cout <<  "||||||||||||| END |||||||||||||" << std::endl;
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
	if (check_if_user_exist(sd, irc_serv->the_users) > 0)
	{
		std::cout << "The user with the same fd exists so let's not look for the connexion stuffs" << std::endl;
		// TODO? CHECK OTHER COMMANDS LIKE JOIN
		return 1;
	}
	else
	{
		std::cout << "user don't exist, let's start the connexion process!" << std::endl;
		ft_deal_next(buff_arr, irc_serv, sd);
	}

	// if (check_vector_arr(buff_arr, "PING localhost\r") > 0)
	// {
	// 	// TODO FIX PONG, not working
	// 	client_printer(sd, "PONG localhost", 371, "edj");
	// 	send(sd, "PONG localhost\r", 15, 0);
	// 	return 1;
	// }

	return 0;
}
