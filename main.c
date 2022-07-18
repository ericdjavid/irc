



    // ? STAGES FOR SERVER

    // !CREATE SOCKET
    // http://www-igm.univ-mlv.fr/~dr/XPOSE2001/tari/Definition.htm#:~:text=*%20Internet%20(AF_INET)%2C%20pareil%20sur%20un%20r%C3%A9seau%20I.P.&text=Il%20d%C3%A9termine%20le%20type%20et,%C3%A9changes%2C%20le%20s%C3%A9quencement...&text=Les%20caract%C3%A9ristiques%20du%20mode%20d%C3%A9connect%C3%A9%20d%C3%A9pendent%20de%20la%20famille%20de%20la%20socket
    // Une socket se definit par
    //  - son domaine (AF_INET pr internet)
    //  - son type  (FT)
    //  - mode connect2 (Sock Stream)

    // !Setsockopt: This helps in manipulating options for the
    // [OPTIONNAL]
    // socket referred by the file descriptor sockfd. This is completely optional, but it helps in reuse of address and port. Prevents error such as: “address already in use”.

    // !Bind
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    // After creation of the socket, bind function binds the 
    // socket to the address and port number specified in addr(custom data structure). In the example code, we bind the server to the localhost, hence we use INADDR_ANY to specify the IP address.

    // !Listen
    // inr listen(int sockfd, int backlog);
    // It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection. The backlog, defines the maximum length to which the queue of pending connections for sockfd may grow. If a connection request arrives when the queue is full, the client may receive an error with an indication of ECONNREFUSED.
    
    // !ACCEPT
    // int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    // It extracts the first connection request on the queue of pending connections for the listening socket, sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket. At this point, connection is established between client and server, and they are ready to transfer data.

    // ? STAGES FOR CLIENT

    // !Socket connection: Exactly same as that of server’s socket creation
    // !Connect: The connect() system call connects the socket referred to by the file descriptor sockfd to the address specified by addr. Server’s address and port is specified in addr.

// https://www.geeksforgeeks.org/socket-programming-cc/
// https://www.geeksforgeeks.org/tcp-and-udp-server-using-select/
// https://www.geeksforgeeks.org/udp-server-client-implementation-c/
// https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080


int main(void) 
{
    struct sockarddr_in adLocale;
    // Type de la socket
    adLocale.sin_family = AF_INET;
    // Affectation du port local
    adLocale.sin_port = htons(PORT); 
    // Identif l'hote
    adLocale.sin_addr.sin_addr = htonl(INADDR_ANY);

    //  Cree socket UDP/TCP
    //  int sockfd = socket(domain, type, protocol)
    int skd = socket(AF_INET, SOCK_STREAM, 0);
    if (skd == 0)
    {
        perror("server socket failure");
        exit(EXIT_FAILURE)
    }

    // Forcefully attaching socket to the port 8080
    // if (setsockopt(server_fd, SOL_SOCKET,
    //                SO_REUSEADDR | SO_REUSEPORT, &opt,
    //                sizeof(opt))) {
    //     perror("setsockopt");
    //     exit(EXIT_FAILURE);
    }



}
