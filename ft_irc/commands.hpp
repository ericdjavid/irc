#pragma once
#include <cstring>
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
			printf("ret = %d\n", i);
			return i;
		}
	}
	return 0;
}


int ft_treat_commands(std::vector<std::string> buff_arr, the_serv *irc_serv, int sd)
{
	static int first = 0;
	int ret = 0;
	std::string nick;
	std::string user;
	std::cout << "STATIC INT FIRST IS " << first << std::endl;
	// IF NICK ALREADY USED, SEND 433 INSTEAD
	//if (nick_already_in_use(nick, irc_serv->the_users))

	print_vector(buff_arr);

	if (check_vector_arr(buff_arr, "PING localhost\r") > 0)
	{
		// TODO FIX PONG, not working
		// client_printer(sd, "PONG localhost", 371, "edj");
		send(sd, "PONG localhost\r", 15, 0);
		return 1;
	}
	if (check_vector_arr(buff_arr, "CAP END\r") > 0)
		return 1;
	if (!first)
	{
		if ((ret = check_vector_arr(buff_arr, "CAP LS\r")) > 0)
		{
			client_printer(sd, "A channel for the good guyz", 371, "edj");
			//
			// ERROR HERE
			//
			std::cout << "JUMP HERE\n";
			char const *test = "CAP * LS :\r\n";
			send(sd , test , strlen(test) , 0 );
			char const *world = ":localhost 001 edjavid :Optionnal msg\r\n NICK john\r\n USER edjavid\r\n";
			send(sd, world, strlen(world), 0);
			client_printer(sd, "Your host is localhost, running version 1\n", 002, user);
			client_printer(sd, "This localhost was created at [add hour]\n", 003, user);
		}
		if ((ret = check_vector_arr(buff_arr, "PASS")) > 0)
		{ 
			first++;
			ret -= 1;
			std::string pass = buff_arr.at(ret).substr(5);
			if (!pass.compare(irc_serv->password))
			{
				client_printer(sd, "Good password entered =)", 371, user);
				std::cout << "Good password entered =)" << std::endl;

				// TODO ALEX ADD NEW USER --> check if sd is adapted for id
				class User *tmp_user = create_new_user(sd, "nick", "username", &(irc_serv->the_users));
				if (tmp_user == NULL)
					return (3);
				irc_serv->the_users.push_back(*tmp_user);
				std::cout << "USER NICK IS " << tmp_user->get_nick() << std::endl;
				std::cout << "||||||||||||| USERS |||||||||||||||" << std::endl;
				display_users(irc_serv->the_users);
				std::cout <<  "|||||||||||||END |||||||||||||||" << std::endl;
				return 1;
			}
			else
			{
				std::cout << "Wrong password entered =(" << std::endl;
				first--;
				return 2;
			}
		}
		else
		{
		    client_printer(sd, "No password set up, please connect with password", 471, "EDJAV");
			return 2;
		}
	}

	return 0;
}
