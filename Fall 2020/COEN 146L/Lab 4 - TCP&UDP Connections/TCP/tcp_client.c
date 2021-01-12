/*
Name: Ruchir Mehta
Date: October 29, 2020
Title: Lab 4 - Part 1
Description: TCP Client

Run: gcc -o client tcp_client.c -std=c99 
*/

//UDP Client
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <netinet/in.h>
#include <netdb.h>
#include <string.h>


int main(){
    //Declare socket file descriptor. All Unix I/O streams are referenced by descriptors
    int sockfd, recv_data;

    //Declare sending buffer of size 1k bytes
    char sbuf[1024], rbuf[1024]; 
    char buffer;

    //Declare server address
    struct sockaddr_in servAddr; 

    //Converts domain names into numerical IP addresses via DNS
    struct hostent *host;
    host = (struct hostent *)gethostbyname("localhost"); 

    //Open a socket, if successful, returns adescriptor associated with an endpoint 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);
    }

    //Set the server address to send using socket addressing structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5000);
    servAddr.sin_addr = *((struct in_addr *)host->h_addr);

    // connect to the server
    if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr)))
    {
        perror("Failure to connect to the server");
        exit(1);
    } // server equivalent: connfd

    // create file if one doesn't exit and write only
    // 0644 is some mode to specify read and write only (required)
    int destination = open("copyTo.txt",O_WRONLY | O_CREAT, 0644); 
    if (destination == -1)
    {
        perror("Error opening the destination file.");
        return (-1);
    }

    //Client to send messages to the server continuously using UDP socket 
    while(1){
        printf("Client: Type a file name you would like to get from the server\n");

        // interpret file name
        scanf("%s", sbuf);

        // send file name sbuf to the server
        send(sockfd, sbuf, strlen(sbuf), 0);

        while(recv(sockfd, rbuf, 1024, 0))
        {
            // write char to the destination file
            write(destination, rbuf, 1);

            // print what the server sent back
            printf("Server sent message: %s\n", rbuf);

            memset(rbuf, 0, sizeof(rbuf));
        }
        printf("Server finished writing to output file.\n");
    } 

    // close the socket, check for errors
    if (close(sockfd) == -1)
    {
        perror("There was an error closing the socket.");
        exit(1);
    }

    return 0;
}