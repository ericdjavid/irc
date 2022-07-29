#pragma once
#include <cstring>
#include <iostream>
#include <vector>
#include "channel.hpp"
#include <sys/time.h>       //FD_SET, FD_ISSET, FD_ZERO macros

void ft_join_channel(char* buff, the_serv *irc_serv)
{
	if (!(irc_serv->the_channel.empty()))
	{
		// Check if chan exists
		std::vector<channel>::iterator channs = irc_serv->the_channel.begin();
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
	irc_serv->the_channel.push_back(channel(buff));

}

// void ft_get_command(char *buff, the_serv *irc_serv, int sd)
// {
//     if (strncmp(buff, "JOIN ", 5) == 0)
//         ft_join_channel(buff, irc_serv);
//     if (strncmp(buff, "PING ", 5) == 0)
//         send(sd, "PONG localhost", 14, 0);
// }

int check_vector_arr(std::vector<std::string> buff_arr, std::string target)
{
	int i = 0;
	for (std::vector<std::string>::iterator it = buff_arr.begin() ; it != buff_arr.end() ; ++it)
	{
		i++;
		size_t s = target.length();
		std::string new_str(*it);
		new_str = new_str.substr(0, s);
		std::cout << "comparing:";
		std::cout << new_str;
		std::cout << " with:";
		std::cout << target << std::endl;
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
	// int	erase_count = 0;
	int ret = 0;
	print_vector(buff_arr);
	if (!first)
	{
		if ((ret = check_vector_arr(buff_arr, "CAP LS\r")) > 0)
		{
			client_printer(sd, "A channel for the good guyz", 371, "edj");
			char const *test = "CAP * LS :\r\n";
			send(sd , test , strlen(test) , 0 );
			char const *world = ":localhost 001 edjavid :Optionnal msg\r\n NICK john\r\n USER edjavid\r\n";
			send(sd, world, strlen(world), 0);
			char const *world2 = ":localhost 002 edjavid :Your host is localhost, running version 1.0\r\n";
			send(sd, world2, strlen(world2), 0);
			char const *world3 = ":localhost 003 edjavid :This localhost was created at 17:14\r\n";
			send(sd, world3, strlen(world3), 0);
			if (buff_arr.size() == 1)
				return 1;
		}
		if ((ret = check_vector_arr(buff_arr, "PASS")) > 0)
		{ 
			// grab user and nick name
			// if((ret = check_vector_arr(buff_arr, "USER")) > 0)
			// {
				// add user name
				// buff_arr.erase(buff_arr.begin() + ret);
			// }
			first++;
			client_printer(sd, "Password entered", 371, "EDJAV");
			// comparer
			(void)irc_serv;

			int siz = buff_arr.at(ret -1).size();
			std::cout << "Password: " << buff_arr.at(ret) << std::endl;
			std::cout << "Size of the line is " << siz << std::endl;
			std::string pass = buff_arr.at(ret).substr(5);
			if (!pass.compare(irc_serv->password))
			{
				std::cout << "Good password entered =)" << std::endl;
			}
			else
			{
				std::cout << "Wrong password entered =(" << std::endl;
			}

		}
		// else
		// {
		//     client_printer(sd, "Password incorrect or missing", 471, "EDJAV");
		// }
	}

	return 0;
}

