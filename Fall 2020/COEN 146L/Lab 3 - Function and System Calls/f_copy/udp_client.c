//UDP Client
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

int main(){
    //Declare socket file descriptor. All Unix I/O streams are referenced by descriptors
    int sockfd; 

    //Declare sending buffer of size 1k bytes
    char sbuf[1024]; 

    //Declare server address
    struct sockaddr_in servAddr; 

    //Converts domain names into numerical IP addresses via DNS
    struct hostent *host;
    host = (struct hostent *)gethostbyname("localhost"); //Local host runs the server. You may use "127.0.0.1": loopback IP address

    //Open a socket, if successful, returns adescriptor associated with an endpoint 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);
    }

    //Set the server address to send using socket addressing structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5000);
    servAddr.sin_addr = *((struct in_addr *)host->h_addr);

    // File Setup
    FILE *sc;   // pointer to source file
    char myChar;

    // get file len
    fseek(sc, 0, SEEK_END);
    int len = ftell(sc);    

    // Put source file back to beginning
    fseek(sc, 0, SEEK_SET);

    //Client to send messages to the server continuously using UDP socket 
    while(1){
        printf("Client: Type a file name you would like to send to the server\n");
        // interpret file name
        scanf("%s", sbuf);
        sc = fopen(sbuf, "rb");
        // check to make sure opened correctly
        if (sc == NULL)
        {
            perror("Error opening the source file");
            exit(1);
        }

        for (int i = 0; i < len; i++)
        {
            // function that gets individual char
            myChar = fgetc(sc);

            // send source file and lenght of char
            sendto(sockfd, myChar, strlen(myChar), 0, (struct sockaddr *)&servAddr, sizeof(struct sockaddr));
        } 

    }

    return 0;
}