#include "channel.hpp"
#include "tools.hpp"

char     compare_first_char(char c)
{
    if (c == '&' || c == '#' || c == '+' || c == '!')
        return c;
    return '0';
}

int     is_forbidden(char c)
{
    if (c == ',' || c == ':' || c == ' ' || c == 7)
        return 1;
    return 0;
}

int     syntax_channel_name(std::string name)
{
    const char  *reference;
    int         i;

    reference = name.c_str();
    i = 0;
    while(reference[i])
    {
        if (is_forbidden(reference[i]) == 1)
            return 1;
        i++;
    }
    return 0;
}

// IF ALREADY TAKEN RETURN 1, ELSE 0
int     compare_to_existing_channels(std::string name, std::vector<Channel> channels)
{
    std::vector<Channel>::iterator it = channels.begin();
    while(it != channels.end())
    {
        if (it->get_name() == name)
        {
            std::cout << "name " << name << " is already used by another Channel. Please select another one." << std::endl;
            return 1;
        }
        it++;
    }
    return 0;
}

int     verify_channel_name(std::string name, std::vector<Channel> channels)
{
    const char  *reference;

    reference = name.c_str();
    if (compare_first_char(reference[0]) == '0' || name.length() >= 50)
    {
        std::cout << "wrong channel name, please select a correct one(starts with &-#-+-! and lenght of 50 char max)." << std::endl;
        return 1;
    }
    if (compare_to_existing_channels(name, channels))
        return 1;
    if (syntax_channel_name(name))
        return 1;
    return 0;
}

Channel *create_new_channel(std::string name, std::vector<Channel> channels)
{
    const char    *reference;

    reference = name.c_str();
    if (verify_channel_name(name, channels) == 1)
        return NULL;
    std::vector<User> users;
    class Channel tmp(name, users, reference[0]);
    Channel *chann = &tmp;
    return chann;
}

// RETURN INDEX IF IT EXISTS, ELSE RETURN -1
int     get_channel(std::string name, std::vector<Channel> channels)
{
    std::vector<Channel>::iterator it;

    it = channels.begin();
    int i = 0;
    while (it != channels.end())
    {
        if (it->get_name() == name)
            return (i);
        it++;
        i++;
    }
    return (-1);
}

void        print_channels(std::vector<Channel> ptr)
{
    std::vector<Channel>::iterator it;

    if (ptr.size() < 1)
        return ;

    it = ptr.begin();
    std::cout << "|||  CHANNELS  |||" << std::endl;
    while (it != ptr.end())
    {
        std::cout << it->get_name() << std::endl;
        it++;
    }
    std::cout << "|||     END    |||" << std::endl;
}

void        send_message_to_channel(class Channel chan, std::string message)
{ 
    std::cout << "we re inside send message to channel function, user list is " << std::endl;
    std::vector<User> user_list = chan.get_users();
    display_users(user_list);
    std::vector<User>::iterator it = user_list.begin();
    while (it != user_list.end())
    {
        client_printer(it->get_id(), message, "371", it->get_nick());
        it++;
    }
}