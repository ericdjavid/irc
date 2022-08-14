#pragma once
#include <string.h>
#include <iostream>
#include <vector>
#include "user.hpp"
#include "channel.hpp"
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include "server.hpp"
#include "tools.hpp"
#include "user_commands.hpp"


bool ft_check_password(std::vector<std::string> buff_arr, the_serv *irc_serv, int sd, std::string user)
{
	int ret = 0;
	if ((ret = check_vector_arr(buff_arr, "PASS")) > 0)
	{
		ret -= 1;
		std::string pass = buff_arr.at(ret).substr(5);
		if (debug)
			std::cout << "Pass is " << pass << std::endl;
		if (!pass.compare(irc_serv->password))
		{
			client_printer(sd, "Good password entered =)", "371", user);
			return true;
		}
		else
		{
			if (debug)
				std::cout << "Wrong password entered =(" << std::endl;
			return false;
		}
	}
	else
	{
		client_printer(sd, "No password set up, please connect with password", "471", user);
		return false;
	}
	return false;
}

int ft_deal_next(std::vector<std::string> buff_arr, the_serv *irc_serv, int sd)
{
	std::string nick;
	std::string user;
	int ret = 0;
	static int i = -1;

	// IRSSI NORMAL PROCEDURE
	if ((ret = check_vector_arr(buff_arr, "NICK")) > 0 && buff_arr.size() > 1)
	{
		nick = buff_arr.at(ret - 1).substr(5);
		if (debug)
			std::cout << "nick is " << nick << std::endl;
		if (nick_already_in_use(nick, irc_serv->the_users))
		{
			std::cout << "Nick already used !" << std::endl;
			return 1;
		}
		ret = check_vector_arr(buff_arr, "USER");
		if (ret >= 0)
		{
			user = buff_arr.at(ret - 1).substr(5);
			user = user.substr(0, user.find(" "));
		}
		else
			user = "Lambda User";
		if (debug)
			std::cout << "User is " << user << std::endl;
		std::string username = user.substr(0, nick.size());
		if (nick == username)
		{
			nick = "LambdaNick" + to_str(++i);
		}
		std::string msg = ":localhost 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!~" + user + "@localhost\r\n";
		send(sd, msg.c_str(), msg.length(), 0);
		msg = ":localhost 002 " + nick + " :Your host is openlocalhost, running version 1.0\r\n";
		send(sd, msg.c_str(), msg.length(), 0);
		msg = ":localhost 003 " + nick + " :This server was created Sun Aug 14 2022 at 16:01:34 CEST\r\n";
		send(sd, msg.c_str(), msg.length(), 0);
		msg = ":localhost 004 " + nick + " localhost 1.0 N\r\n";
		send(sd, msg.c_str(), msg.length(), 0);
		if (ft_check_password(buff_arr, irc_serv, sd, user) == true)
		{
			if (nick_already_in_use(nick, irc_serv->the_users) == 0)
			{
				class User tmp(sd, nick, user);
				irc_serv->the_users.push_back(tmp);
				// SEND THE NICK
				int index = get_index(irc_serv->the_users, sd);
				std::string resp = ":" + irc_serv->the_users.at(index).get_nick() + "!~" + irc_serv->the_users.at(index).get_username() + "@localhost NICK :" + nick + "\r\n";
				if (debug)	
					std::cout << "Sending the nick is |" << resp << "|" << std::endl;
				if (send(sd, resp.c_str(), resp.length(), 0) == -1)
				{
					if (debug)
						std::cout << "Problem with nick resp" << std::endl;
				}
				std::string PING(":localhost PING localhost :localhost\r\n");
				if (send(sd, PING.c_str(), PING.length(), 0) == -1)
				{
					if (debug)
						std::cout << "Problem with PING send" << std::endl;
					return 0;
				}
			}
			else
			{
				if (debug)
					std::cout << "user not created, nick" << nick << " already in use" << std::endl;
				i--;
				return 1;
			}
		}
		else
		{
			if (debug)
				std::cout << "no password set by user" << std::endl;
			i--;
			return 1;
		}
	}
	else
	{
		// NC PROCESS
		if (debug)
			std::cout << "NC process" << std::endl;
		if (check_if_user_exist(sd, irc_serv->the_users) == 0)
		{
			if (debug)
				std::cout << "Please set password" << std::endl;
			if (ft_check_password(buff_arr, irc_serv, sd, "tmp") == true)
			{
				if (debug)
					std::cout << "Please set nick" << std::endl;
				class User tmp(sd);
				irc_serv->the_users.push_back(tmp);
				return 0;
			}
			else
			{
				if (debug)
					std::cout << "Wrong password" << std::endl;
				return 1;
			}
		}
		else
		{
			if (debug)
				std::cout << "User sd exists" << std::endl;
			if ((ret = check_vector_arr(buff_arr, "NICK")) > 0)
			{
				nick = buff_arr.at(0).substr(5);
				if (nick_already_in_use(nick, irc_serv->the_users) == 0)
				{
					int ind = get_index(irc_serv->the_users, sd);
					if (debug)
						std::cout << "Index is " << ind << std::endl;
					if (ind >= 0)
					{
						irc_serv->the_users.at(ind).set_the_nick(nick);
						irc_serv->the_users.at(ind).set_nick(true);
						irc_serv->the_users.at(ind).set_username("lol");
						display_users(irc_serv->the_users);
					}
				}
				else
				{
					std::cout << "Nick already in use, set another nick";
					return 0;
				}
			}
			else
			{
				std::cout << "Please set a nick..." << std::endl;
			}
		}
		return 0;
	}
	return 0;
}

int ft_treat_commands(std::vector<std::string> buff_arr, the_serv *irc_serv, int sd)
{
	int ret = 0;
	if ((ret = check_vector_arr(buff_arr, "CAP LS")) > 0)
	{
		char const *cap_ls = "CAP * LS :multi-prefix extended-join sasl\r\n";
		send(sd, cap_ls, strlen(cap_ls), 0);
		if (debug)
			std::cout << "Buff arr size is " << buff_arr.size() << std::endl;
		if (buff_arr.size() == 1)
		{
			if (debug)
				std::cout << "Nothing after CAP LS, next" << std::endl;
			return 1;
		}
		else
		{
			// DEAL NEXT
			if (ft_deal_next(buff_arr, irc_serv, sd) == 1)
				return -2;
			else
			{
				display_users(irc_serv->the_users);
				return 1;
			}
		}
	}

	// CHECK IF SD IS IN THE LIST OF USER
	ret = -1;
	if (((ret = check_if_user_exist(sd, irc_serv->the_users)) > 0) && ret >= 0 && irc_serv->the_users.at(get_index(irc_serv->the_users, ret)).get_set_nick() == true)
	{
		int index = 0;
		index = get_index(irc_serv->the_users, sd);
		if (!ft_deal_with_commands(index, sd, irc_serv, buff_arr))
			return 1;
		return -2;
	}
	else
	{
		// if (DEBUG)
		if (debug)
			std::cout << "User nick don't exist in DB, starting the connexion process!" << std::endl;
		if (ft_deal_next(buff_arr, irc_serv, sd) == 1)
			return -2;
	}
	return 0;
}
