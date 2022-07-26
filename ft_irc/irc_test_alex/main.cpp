#include <string>
#include <sys/time.h>
#include <iostream>
#include <vector>
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

#include "../tools.hpp"
#include "../server.hpp"
#include "../commands.hpp"
#include "../new_connection.cpp"

#define TRUE 1
#define FALSE 0
#define MAX_CLI 30
#define BUFF 1024

int		main(int ac, char **av)
{
	 if (ac != 3)
        error("Bad number of parameters");
    std::string port(av[1]);
    std::string pswd(av[2]);
    int uport = FromString<int>(port);
    int PORT = uport;
	int opt = TRUE;
    int master_socket , addrlen , new_socket , client_socket[30] , max_clients = 30 , activity, i , valread , sd;
    int max_sd;
    struct sockaddr_in address;

    char buffer[1025];
	fd_set readfds;

    the_serv irc_serv;
    irc_serv.password = pswd;
			//allowing connections
	printf("Listener on port %d \n", PORT);
	if (listen(master_socket, 5) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	addrlen = sizeof(address);
	puts("Waiting for connections ...");
		//end
    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++)
        client_socket[i] = 0;
	if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == -1)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
	if(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
	if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

	while (true)
	{
		FD_ZERO(&readfds); //reset socket
		FD_SET(master_socket, &readfds); //add master socket to set of socket to read to handle new connections
        max_sd = master_socket;
		for ( i = 0 ; i < max_clients ; i++) //add all other sockets to read them all
        {
			sd = client_socket[i];
			if(sd > 0)
                FD_SET( sd , &readfds); //FD_SET add sockets to read_list
			if(sd > max_sd)
                max_sd = sd;
        }
		timeval tmp;
        tmp.tv_sec = 5;
        activity = select( max_sd + 1 , &readfds , NULL , NULL , &tmp); //select is waiting for one of the fd from readfds to get ready for an action (read for example)
		
	}
}