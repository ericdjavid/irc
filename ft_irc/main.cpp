#include <string>
#include <iostream>
#include <vector>
#include "tools.cpp"


class channel
{
    private:
    std::string _name;

    public:

};

class server 
{
    private:
    std::string _name;
    int _port;
    std::vector<channel> chans;
    std::string _password;

    public:
    server(int port, std::string pswd) : _port(port), _password(pswd) 
    {
        std::cout << "server class created with port " << port << std::endl;
    };
    void get_list_of_chans(){};
};


int error(std::string str)
{
    std::cout << str << std::endl;
    return 2;
};


int main(int argc, char **argv)
{
    if (argc != 3)
        return(error("Bad number of parameters"));
    std::string port(argv[1]);
    std::string pswd(argv[2]);
    int uport = FromString<int>(port);
    server IRC_serv(uport, pswd);
    return 1;
}