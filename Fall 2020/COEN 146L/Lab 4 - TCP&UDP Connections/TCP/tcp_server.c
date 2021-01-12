/*
Name: Ruchir Mehta
Date: October 29, 2020
Title: Lab 4 - Part 1
Description: TCP Server

Run: gcc -o server tcp_server.c -std=c99 -pthread
*/

// UDP Server
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include <pthread.h> 

#define CONNECTIONS 5
pthread_t tids[CONNECTIONS];

void *start_routine(void *arg)
{
    // setup buffers
    char rbuf[1024], buffer[1024];
    // setup rb, sc
    int rb, sc;
    // char buffer;
    // setup connfd
    int connfd = *(int *) arg;

    // // accept file request from client and write it back to it
    
    rb = recv(connfd, rbuf, 1024, 0);

    // rbuf will be the name of the text file it wants to copy; ex: copyMe1.txt
    rbuf[rb] = '\0';
    printf("Client sent: %s\n", rbuf);

    // send back and ACK to the client
    //send(connfd, "Acknowledge", 20.0);

    // O_RDWR mode for reading and writing
    // check to make sure opened correctly
    if ((sc = open("goals.txt", O_RDWR)) > 0)
    {
        perror("Error opening source file.");
        //exit(1);
    }

    // read the chars one by one and send back to client
    while(read(sc, &buffer, 1) > 0)
    {
        send(connfd, &buffer, strlen(&buffer), 0);
        printf("Buffer is %s, %d\n", buffer, strlen(&buffer));
        memset(buffer, 0, sizeof(buffer));
    }
    printf("\nFinished sending file to client.\n");

    //}
}

int main(){
    //Declare socket file descriptor. All Unix I/O streams are referenced by descriptors
    int sockfd, connfd, sin_size;

    //Declare server address to which to bind for receiving messages and client address to fill in sending address
    struct sockaddr_in servAddr, clienAddr;
    socklen_t addrLen = sizeof(struct sockaddr);

    //Open a TCP socket, if successful, returns adescriptor associated with an endpoint 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
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

    // listen function, queue 5 client requests
    if (listen(sockfd, CONNECTIONS) == -1)
    {
        perror("Error encountered while trying to listen.");
        exit(1);
    }

    // setup multithreading
    for (int i = 0; i <= CONNECTIONS; i++)
    {
        int *myconn = malloc(sizeof(int));
        
        // server accepts establishing connection with client
        *myconn = accept(sockfd, (struct sockaddr *)&clienAddr, (socklen_t *)&sin_size);

        // create the thread
        pthread_create(&tids, NULL, start_routine, myconn);
    }

    // close the socket, check for errors
    if (close(sockfd) == -1)
    {
        perror("There was an error closing the socket.");
        exit(1);
    }

    return 0;
}