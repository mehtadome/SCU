#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <string.h>

//Declare socket file descriptor. All Unix I/O streams are referenced by descriptors
int sockfd;

//Declare receiving buffer of size 1k bytes
char rbuf[1024], sbuf[1024];

//Declare server address to which to bind for receiving messages and client address to fill in sending address
struct sockaddr_in servAddr, remoteAddr;
socklen_t addrLen = sizeof(struct sockaddr);

struct hostent *host;

// change
char hostName[10], source_file[10], destination_file[10];

// 6000, 5000
void setup()
{
    //Converts domain names into numerical IP addresses via DNS
    host = (struct hostent *)gethostbyname(hostName);

    if (host == NULL) {
        puts("Error: unable to resolve hostname.");
        exit(1);
    }

    //Setup the server address to bind using socket addressing structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5000); //Port 5000 is assigned
    //servAddr.sin_addr.s_addr = INADDR_ANY; //Local IP address of any interface is assigned (generally one interface IP address)
    servAddr.sin_addr = *((struct in_addr *)host->h_addr);

    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(6000); //Port 6000 is assigned
    //remoteAddr.sin_addr.s_addr = INADDR_ANY; //Local IP address of any interface is assigned (generally one interface IP address)
    remoteAddr.sin_addr = *((struct in_addr *)host->h_addr);

    //Open a UDP socket, if successful, returns a descriptor associated with an endpoint
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);
    }
}

void start_server() {
    gethostname(hostName, 20);
    printf("Server hostname: %s\n", hostName);

    // setup everything
    setup();

    //Set address/port of server endpoint for socket socket descriptor
    if ((bind(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))) < 0){
        perror("Failure to bind server address to the endpoint socket");
        exit(1);
    }

    // wait for client to request a file
    int rb;
    while ((rb = recvfrom(sockfd, rbuf, 1024, 0, (struct sockaddr *)&remoteAddr, &addrLen)) > 0){
        rbuf[rb] = '\0';
        printf("Client sent: %s\n", rbuf);  // line breaks the code for some reason
        
        // never reaches
       //puts("Peer sent: %s\n", rbuf)
        printf("strcmp(rbuf, REQUEST) %d", strcmp(rbuf, "REQUEST"));
        if(strcmp(rbuf, "REQUEST") == 0)
        {
            puts("I break out of the while loop.");
            break;
        }

    }

    // setup source file for server() to read
    int sc = open(source_file, O_RDWR); // O_RDWR mode for reading and writing
    // check to make sure opened correctly
    if (sc == -1)
    {
        perror("Error opening source file.");
        sendto(sockfd, "ERROR", strlen("ERROR"), 0, (struct sockaddr *)&remoteAddr, sizeof(struct sockaddr));
        exit(1);
    }

    sendto(sockfd, "PROCESSING", strlen("PROCESSING"), 0, (struct sockaddr *)&remoteAddr, sizeof(struct sockaddr));
   
    memset(rbuf, 0, sizeof(rbuf));
    while(read(sc, &rbuf, 1) > 0)
    {
        printf("rbuf %s\n", rbuf);
        sendto(sockfd, &rbuf, strlen(&rbuf), 0, (struct sockaddr *)&remoteAddr, sizeof(struct sockaddr));
        memset(rbuf, 0, sizeof(rbuf));
    }

    // let the client know that the file has finished sending
    sendto(sockfd, "FINISHED", strlen("FINISHED"), 0, (struct sockaddr *)&remoteAddr, sizeof(struct sockaddr));
    
    // Close the file
    close(sc);

    // Close the socket descriptor
    close(sockfd);
}

void start_client() {
    printf("Enter hostname to contact: ");
    scanf("%s", hostName);

    // setup everything
    setup();

    // Client sends file request
    sendto(sockfd, "REQUEST", strlen("REQUEST"), 0, (struct sockaddr *)&remoteAddr, sizeof(struct sockaddr));
    printf("Sent file request to server.\n");


    // read 
    int rb;
    while ((rb = recvfrom(sockfd, rbuf, 1024, 0, (struct sockaddr *)&remoteAddr, &addrLen)) > 0){
        rbuf[rb] = '\0';
        printf("Server sent: %s\n", rbuf);

        if (strcmp(rbuf, "PROCESSING") == 0)
        {
            break;
        } else{
            perror("There was an error making a connection.");
            exit(1);
        }
    }

    // setup destination file
    int destination = open(destination_file ,O_WRONLY | O_CREAT, 0644);
    if (destination < 0) {
        perror("There was an error opening the destination file");
        exit(1);
    }

    // wait for response
    while (rb = recvfrom(sockfd, rbuf, 1024, 0, (struct sockaddr *)&remoteAddr, &addrLen)){
        rbuf[rb] = '\0';
        printf("Server sent: %s\n", rbuf);

        // if not finished, continue writing to file
        if (strcmp(rbuf, "FINISHED") == 0)
        {
            printf("Done writing to file.\n");
            break;
        } else {
            // write char to the destination file
            write(destination, rbuf, 1);
        }
    }

    // close the destination file
    close(destination);

    // Close socket descriptor
    close(sockfd);
}

int main() {
    
    while (1) {
        puts("Enter 0 for sending, 1 for receiving.");
        int input;
        scanf("%d", &input);
        
        // send file to other peer
        if (input == 0) {
            puts("Enter file name to send.");
            scanf("%s", source_file);

            puts("Successfully read input, updating...");
            start_server();
        }
        // request file to receive from other peer
        else if (input == 1) {
            puts("Enter file name to write to");
            scanf("%s", destination_file);

            puts("Successfully read input, updating...");
            start_client();
        }
        else {
            puts("Please enter something valid");
        }
    }
    return 0;
}