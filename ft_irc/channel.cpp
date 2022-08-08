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

Channel     get_channel(std::string name, std::vector<Channel> channels)
{
    std::vector<Channel>::iterator it;

/*
    it = channels.begin();
    while (it != channels.end() && it->get_name() != name)
    {
        it++;
    }
    return (*it);
*/

	for (it = channels.begin(); it != channels.end(); it++)
	{
std::cout <<  "NAME ==>" << it->get_name() << "My name" << name << std::endl;
		if (it->get_name() == name)
			return (*it);
	}
	return (*it);
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

void        send_message_to_channel(std::string name, std::vector<Channel> channels, std::string message)
{
    try
    {
        Channel tmp = get_channel(name, channels);
        std::vector<User> tmp2 = tmp.get_users();
        std::vector<User>::iterator it = tmp2.begin();
        while (it != tmp.get_users().end())
        {
            client_printer(it->get_id(), message, 0, it->get_nick()); // TODO! NOT SURE ABOUT numeric VALUE (0), HAVE TO ASK ERIC
            it++;
        }
    }
    catch (const std::bad_exception& e)
    {
        //SI TMP NE POINTE PAS SUR UN CHANNEL
        std::cerr << "Caught " << e.what() << '\n';
    }
}
