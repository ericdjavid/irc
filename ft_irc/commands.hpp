#pragma once
#include <cstring>
#include <iostream>
#include <vector>
#include "channel.hpp"

void ft_join_channel(char* buff, the_serv *irc_serv)
{
    // Check if chan exists
    std::vector<channel>::iterator channs = irc_serv->the_channel.begin();
    std::string     channel_name;
    channel_name = buff;
    while (channs->get_name() != channel_name && channs != irc_serv->the_channel.end())
        channs++;
    if (channs->get_name() == channel_name)
    {
        //JOIN CHANNEL -> ADD USER TO CHANN
    }
    else{
        //CREATE CHANNEL
        std::cout << "Server: channel does not exist, creating it\n";
        for (int i = 0; i < 4; i++)
            buff++;
        std::string name(buff); 
        irc_serv->the_channel.push_back(channel(buff));
        // && AD USER TO CHANN
    }
}

void ft_get_command(char *buff, the_serv *irc_serv)
{
    if (strncmp(buff, "JOIN ", 5) == 0)
        ft_join_channel(buff, irc_serv);
}