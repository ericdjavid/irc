#include "user.hpp"

int user::set_nick(std::string nick)
{
    _nick = nick;
    return 1;
};

// int user::set_password(std::string pswd)
// {
//     _password = pswd;
//     return 1;
// };