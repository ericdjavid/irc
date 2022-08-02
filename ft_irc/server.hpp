#pragma once

#include "user.hpp"
#include "channel.hpp"
#include <vector>

struct server
{
    std::vector<Channel> the_channel;
    std::vector<User> the_users;
    std::string password;

} typedef the_serv;