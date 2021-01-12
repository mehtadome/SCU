// UDP Server
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>


int main(){
    //Declare socket file descriptor. All Unix I/O streams are referenced by descriptors
    int sockfd;

    //Declare receiving buffer of size 1k bytes
    char rbuf[1024];

    //Declare server address to which to bind for receiving messages and client address to fill in sending address
    struct sockaddr_in servAddr, clienAddr;
    socklen_t addrLen = sizeof(struct sockaddr);

    //Open a UDP socket, if successful, returns adescriptor associated with an endpoint 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    {
        perror("Failure to setup an endpoint socket");
        exit(1);
    }

    //Setup the server address to bind using socket addressing structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5000); //Port 5000 is assigned
    servAddr.sin_addr.s_addr = INADDR_ANY; //Local IP address of any interface is assigned (generally one interface IP address)

    //Set address/port of server endpoint for socket socket descriptor
    if ((bind(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))) < 0)
    {
        perror("Failure to bind server address to the endpoint socket");
        exit(1);
    }

    // File reading and writing setup
    FILE *destination = fopen("destination.jpg", "rb+");
    // Error Checking
    if (destination == NULL)
    {
        perror("Error opening the destination file");
        return(-1);
    }

    //int len; // len for length of file

    //Sever continuously waits for messages from client, then prints incoming messages.
    while (1){
        // user information
        printf("Server waiting for messages from client: \n");

        // read from UDP socket into message, gets client's address (IP & Port)
        int nr = recvfrom(sockfd, rbuf, 1024, 0, (struct sockaddr *)&clienAddr, &addrLen);
        
        // write char to the destination file
        fputc(&rbuf, destination);
        
        // Not sure*
        // rbuf[nr] = '\0';

        // printf("Client with IP: %s and Port: %d sent message: %s\n", inet_ntoa(clienAddr.sin_addr),ntohs(clienAddr.sin_port), rbuf);
    }

    return 0;
}