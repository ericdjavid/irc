#pragma once

#include "user.hpp"
#include "channel.hpp"
#include <vector>

struct server
{
    std::vector<channel> the_channel;
    std::vector<user> the_users;
    std::string password;

} typedef the_serv;