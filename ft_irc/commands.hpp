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

int ft_deal_next(std::vector<std::string> buff_arr, the_serv *irc_serv, int sd)
{

	std::string nick;
	std::string user;
	int ret = 0;
	if ((ret = check_vector_arr(buff_arr, "NICK")) > 0)
	{
		nick = buff_arr.at(ret - 1).substr(5);
		std::cout << "nick is " << nick << std::endl;
		ret = check_vector_arr(buff_arr, "USER");
		if (ret >= 0)
			user = buff_arr.at(ret - 1).substr(5);
		else
			user = "Lambda User";
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
			else
			{
				std::cout << "user not created, nick" << nick << " already in use" << std::endl;
				return 1;
			}
			// std::cout << "||||||||||||| USERS |||||||||||||" << std::endl;
			// display_users(irc_serv->the_users);
			// std::cout <<  "||||||||||||| END |||||||||||||" << std::endl;
			return 0;
		}
		else
			return 1;
	}
	return 0;
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
			if (ft_deal_next(buff_arr, irc_serv, sd) == 1)
				return -2;
		}
	}
	
	// CHECK IF SD IS IN THE LIST OF USER
	// std::cout << "sd = " << sd << std::endl;
	if ((ret = check_if_user_exist(sd, irc_serv->the_users)) > 0)
	{
		// TODO? CHECK OTHER COMMANDS LIKE JOIN
		// std::cout << "The user with the same fd exists so let's not look for the connexion stuffs" << std::endl;
		int index = 0;
		if ((index = get_index(irc_serv->the_users, sd)) > 0)
		{
			// std::cout << "index is " << index << std::endl;
		}

		if (!ft_deal_with_commands(index, sd, irc_serv, buff_arr))
			return 1;
		return 2;

	}
	else
	{
		std::cout << "user don't exist, let's start the connexion process!" << std::endl;
		if(ft_deal_next(buff_arr, irc_serv, sd) == 1)
			return -2;
	}
	return 0;
}