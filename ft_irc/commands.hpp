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
        std::cout << new_str << std::endl;
        std::cout << " with:";
        std::cout << target << std::endl;
        if (new_str.compare(target) == 0)
        {
            // int index = std::distance(buff_arr.begin(), it);
            return i;
        }
    }
    return 0;
}


void ft_treat_commands(std::vector<std::string> buff_arr, the_serv *irc_serv, int sd, fd_set *readfds)
{

    if (FD_ISSET( sd , readfds))
    {

    char const *test2 = "pass received";
    send(sd , test2 , strlen(test2) , 0 );
    (void)irc_serv;
    if (check_vector_arr(buff_arr, "CAP LS\r"))
    {
        std::cout << "CAP LS received" << std::endl;
        char const *test = "CAP * LS :\r\n";
        send(sd , test , strlen(test) , 0 );
    }
    if (check_vector_arr(buff_arr, "PASS") > 0)
    {
        std::cout << "Pass received" << std::endl;
        char const *test = "pass received";
        send(sd , test , strlen(test) , 0 );
    }
    }


}

