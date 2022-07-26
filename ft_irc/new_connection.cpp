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

int		new_connection(int sd)
{
	std::cout << "CAP END reached\n";
    printf("REACHED\n");
    char const *test = "CAP * LS :\r\n";
    send(sd , test , strlen(test) , 0 );
    char const *world = ":localhost 001 edjavid :Optionnal msg\r\n NICK john\r\n USER edjavid\r\n";
    send(sd, world, strlen(world), 0);
    char const *world2 = ":localhost 002 edjavid :Your host is localhost, running version 1.0\r\n";
	send(sd, world2, strlen(world2), 0);
    char const *world3 = ":localhost 003 edjavid :This localhost was created at 17:14\r\n";
    send(sd, world3, strlen(world3), 0);
    char const *world4 = ":localhost 004 <nick> <servername> <version> <available umodes> <available cmodes> [<cmodes with param>]\r\n";
    send(sd, world4, strlen(world4), 0);
	return (0);
}