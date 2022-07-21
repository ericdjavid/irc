#include <string>
#include <iostream>
#include <vector>
#include "tools.cpp"
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>         //close 
#include <arpa/inet.h>      //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h>       //FD_SET, FD_ISSET, FD_ZERO macros 
#include <stdio.h>

#define TRUE 1
#define FALSE 0

class channel
{
    private:
    std::string _name;

    public:

};

class server 
{
    private:
    std::string             _name;
    int                     _port;
    std::vector<channel>    chans;
    std::string             _password;
    //set of socket descriptors 
    // client sockets
    std::vector<int>        _cli_sock;
    struct sockaddr_in      address;  
    int                     _master_socket;
    int                     _opt;
    int                     addrlen;
    fd_set                  _readfds;

    public:
    fd_set      &ret_readfds() {return _readfds;};
    int         get_master_socket(){return _master_socket;};
    server(int port, std::string pswd) : _port(port), _password(pswd), _opt(1)
    {
        std::cout << "server class created with port " << port << std::endl;
           //create a master socket 
        if( (_master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
        {  
            perror("socket failed");  
            exit(EXIT_FAILURE);  
        }  
     
        //set master socket to allow multiple connections , 
        //this is just a good habit, it will work without this 
        if( setsockopt(_master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&_opt, 
            sizeof(_opt)) < 0 )  
        {  
            perror("setsockopt");  
            exit(EXIT_FAILURE);  
        }  
     
        //type of socket created 
        address.sin_family = AF_INET;  
        address.sin_addr.s_addr = INADDR_ANY;  
        address.sin_port = htons( _port ); 

        if (bind(_master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
        {  
            perror("bind failed");  
            exit(EXIT_FAILURE);  
        }

        //accept the incoming connection 
        addrlen = sizeof(address);  
        puts("Waiting for connections ...");  
    };
    // if the client put /channel, return the list of chans
    void get_list_of_chans(){};
};

void error(std::string str)
{
    std::cout << str << std::endl;
    exit(EXIT_FAILURE);
};

int main(int argc, char **argv)
{
    if (argc != 3)
        error("Bad number of parameters");
    std::string port(argv[1]);
    std::string pswd(argv[2]);
    int uport = FromString<int>(port);

    // Instantiate the server class  
    server IRC_serv(uport, pswd);

    // Launch the fcking machine
    while (TRUE)
    {
        FD_ZERO(&(IRC_serv.ret_readfds()));

        //add master socket to set 
        FD_SET(IRC_serv.get_master_socket(), &(IRC_serv.ret_readfds()));  
        // max_sd = master_socket;  
    }


    return 1;
}