#pragma once
#include <cstring>
#include <iostream>

void ft_join_channel(char *buff, the_serv *irc_serv)
{
    // Check if chan exists

    // if not, add the channel
    std::cout << "Server: channel does not exist, creating it\n";
    for (int i = 0; i < 4; i++)
        buff++;
    std::string name(buff); 
    irc_serv->the_channel.push_back(channel(buff));

}

void ft_get_command(char *buff, the_serv *irc_serv)
{
    if (strncmp(buff, "JOIN ", 5) == 0)
        ft_join_channel(buff, irc_serv);
}