#include <string>
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
#include "tools.hpp"
#include "server.hpp"
#include "commands.hpp"
#include "user_commands.hpp"

#define TRUE 1
#define FALSE 0
#define MAX_CLI 30
#define BUFF 1024

int main(int argc, char **argv)
{
    if (argc != 3)
        error("Bad number of parameters");
    std::string port(argv[1]);
    std::string pswd(argv[2]);
    int uport = FromString<int>(port);
    int PORT = uport;

    int opt = TRUE;
    int master_socket , addrlen , new_socket , client_socket[30] , max_clients = 30 , activity, i , valread , sd = 0;
    int max_sd;
    struct sockaddr_in address;

    char buffer[1025];

    //set of socket descriptors
    fd_set readfds;

    the_serv irc_serv;
    irc_serv.port = argv[1];
    irc_serv.password = pswd;

    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }

    /*
        The socket() function creates a new socket.
        It takes 3 arguments,
            a. AF_INET: address domain of the socket.
            b. SOCK_STREAM: Type of socket. a stream socket in 
            which characters are read in a continuous stream (TCP)
            c. Third is a protocol argument: should always be 0. The 
            OS will choose the most appropiate protocol.
            This will return a small integer and is used for all 
            references to this socket. If the socket call fails, 
            it returns -1.
    */
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections (optionnal)
    if(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
          sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    /* 
        The variable serv_addr is a structure of sockaddr_in. 
        sin_family contains a code for the address family. 
        It should always be set to AF_INET.
        INADDR_ANY contains the IP address of the host. For 
        server code, this will always be the IP address of 
        the machine on which the server is running.
        htons() converts the port number from host byte order 
        to a port number in network byte order.
    */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    /* 
        The bind() system call binds a socket to an address. 
        It takes three arguments, 
        - the socket file descriptor. 
        - a pointer to a structure of type sockaddr, this must be cast to
        the correct type.
        - the adress size
    */
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    /*
        The listen system call allows the process to listen
        on the socket for connections.
        The program will be stay idle here if there are no
        incomming connections.
        The first argument is the socket file descriptor,
        and the second is the size for the number of clients
        i.e the number of connections that the server can
        handle while the process is handling a particular
        connection. The maximum size permitted by most
        systems is 5.
    */
    if (listen(master_socket, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while(TRUE)
    {
        // Clear the socket set
        FD_ZERO(&readfds);

        // Add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        // Add child sockets to set
        for ( i = 0 ; i < max_clients ; i++)
        {
            // Socket descriptor
            sd = client_socket[i];

            // If valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);

            // Highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is equal to 5 sec ,
        //so wait indefinitely
        // timeval tmp;
        // tmp.tv_sec = 5;
        // (void)tmp
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL); //third argument of select equals NULL, so select can wait an infinite time. If 3rd value set to 5 sec, select will wait 5sec

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }

        // If something happened on the master socket,
        // then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {

            if ((new_socket = accept(master_socket,
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            
            // Inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs (address.sin_port));

            // Send new connection greeting message
            char const* greetings = 
            "Welcome to our IRC server \n 1) Enter the required password using the command [PASS password]\n 2) Join or create a server using the commande [JOIN name]\n";
            if( send(new_socket, greetings, strlen(greetings), 0) != (ssize_t)strlen(greetings) )
            {
                perror("send");
            }

            // Add new socket to array of sockets
            for (i = 0; i < max_clients; i++)
            {
                // If position is empty
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);
                    break;
                }
            }
        }

        // Else it is some IO operation on some other socket
        for (i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET( sd , &readfds))
            {
                //Check if it was for closing , and also read the
                //incoming message
                if ((valread = read( sd , buffer, 1024)) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n" ,
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                    delete_from_list(&irc_serv, sd);

                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    client_socket[i] = 0;
                }
                else
                {
                    // Set the string terminating NULL byte on the end
                    // of the data read
                    buffer[valread] = '\0';
                    get_buffer(buffer);

                    //SPLIT THE BUFFER
                    std::string cpp_buf(buffer);
                    std::vector<std::string> buff_arr(0);
                    tokenize(cpp_buf, '\n', buff_arr);

                    int ret = 0;
                    if ((ret = ft_treat_commands(buff_arr, &irc_serv, sd)) == 1)
                    {
                        // the socket has been treated, we continue
                        continue;
                    }
                    else if (ret == -2)
                    {
                        // We close the connexion
                        getpeername(sd , (struct sockaddr*)&address , \
                            (socklen_t*)&addrlen);
                        printf("Host disconnected , ip %s , port %d \n" ,
                            inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                        
                        char const* QUIT = 
                        "QUIT\n";
                        if( send(new_socket, QUIT, strlen(QUIT), 0) != (ssize_t)strlen(QUIT) )
                        {
                            perror("QUIT");
                        }
                        delete_from_list(&irc_serv, sd);

                        //Close the socket and mark as 0 in list for reuse
                        close( sd );
                        client_socket[i] = 0;
                    }
                    FD_ZERO(&readfds);
                }
            }
        }
    }

    return 1;
}
