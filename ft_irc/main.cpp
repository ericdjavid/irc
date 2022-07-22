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
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_CLI 30

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
    int                     _opt;
    fd_set                  _readfds;

    public:
    int				_master_socket;
    socklen_t			addrlen;
    struct sockaddr_in		address;  
    int         get_cli_nb(int nb)
    {
	    return _cli_sock.at(nb);
    };
    void        change_cli_nb(int i, int new_socket)
    {
	    _cli_sock[i] = new_socket;
    };
    fd_set      &ret_readfds()
    {
	    return _readfds;
    };
    int         get_master_socket()
    {
	    return _master_socket;
    };
    server(int port, std::string pswd) : _port(port), _password(pswd), _opt(1)
    {
        for (int i = 0; i < MAX_CLI; i++)
            _cli_sock.push_back(0);
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
        address.sin_addr.s_addr = htons(INADDR_ANY);
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
        // max_sd = IRC_serv.get_master_socket();  

        for ( int i = 0 ; i < MAX_CLI ; i++)  
        {  
            //socket descriptor 
            int sd = IRC_serv.get_cli_nb(i);  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &(IRC_serv.ret_readfds()));  
        }

        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        int activity = select( MAX_CLI + 1 , &(IRC_serv.ret_readfds()) , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }

        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(IRC_serv.get_master_socket(), &(IRC_serv.ret_readfds())))  
        {
            int new_socket;
	std::cout << "master socket " << IRC_serv.get_master_socket() << std::endl;
            if ((new_socket = accept((int)IRC_serv.get_master_socket(), (struct sockaddr *)&IRC_serv.address, (socklen_t*)&IRC_serv.addrlen))<0)  
            {
		    std::cout << "new socket accept " << new_socket << std::endl;
		    if (errno == EINVAL)
			    std::cout << "66666666666\n";
                // ! ERROR
                std::cout << "error is hereeeee" << std::endl;
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
             
            //inform user of socket number - used in send and receive commands 
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(IRC_serv.address.sin_addr) , ntohs (IRC_serv.address.sin_port));  
           
            //send new connection greeting message 
            // char *message = "WE MADE IT";
            if( send(new_socket, "lol", 4, 0) != 4 )  
            {  
                perror("send");  
            }  
                 
            puts("Welcome message sent successfully");  
                 
            //add new socket to array of sockets 
            for (int i = 0; i < MAX_CLI; i++)  
            {  
                //if position is empty 
                if( IRC_serv.get_cli_nb(i) == 0 )  
                {  
                    IRC_serv.change_cli_nb(i, new_socket);

                    printf("Adding to list of sockets as %d\n" , i);  
                         
                    break;  
                }  
            }  
        }  


    }

    return 1;
}
