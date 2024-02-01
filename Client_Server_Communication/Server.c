#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

void error(const char *msg){
    /*
    Terminates the program when we want by providing an appropriate message(msg).
    perror - inbuilt functions that interprets the error number,
    and outputs the error description using standard error(stderr).
    */
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){
    /*
    argc - Number of parameters(2)
    argv[0] - File name
    argv[1] - Port number
    */

    // If arguments are less than required.
    if(argc < 2){
        fprintf(stderr, "File name or Port number not provided. Program terminated\n");
        exit(1);
    }

    // Initialize Winsock
    WSADATA wsa;
    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
        error("Failed to initialize Winsock.");
    }

    // Socket file descripters 
    int sockfd, newsockfd, portno, n; // newsockfd - To accept new connections(clients).

    // Message in buffer
    char buffer[255];

    // Server and Client internet address provided by sockaddr_in in netinet header file.
    struct sockaddr_in serv_addr, cli_addr;
    int cli_len;

    // Communication domain - AF_INET(Address Family), Communication Type - SOCK_STREAM(TCP/UDP), Communication Protocol - 0(TCP)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // If socket resulted in a failure.
    if(sockfd == INVALID_SOCKET){
        error("Error opening Socket.");
    }

    // Clear any data/text in server address
    memset((char *) &serv_addr, 0, sizeof(serv_addr));

    // Port number
    portno = atoi(argv[1]);

        // Getting data for server
    // Set the address family of the server socket.
    serv_addr.sin_family = AF_INET;
    // Server will bind to all available network interfaces on the machine(IP addresses).
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    // Set the port number that the server will listen on.
    // htons - Converts the portnumber from host byte order to network byte order.
    serv_addr.sin_port = htons(portno);

    // Bind the socket with server address structure
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == SOCKET_ERROR){
        error("Binding Failed.");
    }

    // Listen to 5 connection on socket.
    listen(sockfd, 5);

    // Client address length
    cli_len = sizeof(cli_addr);

    // New socket file descripter
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);

    // If new socket resulted in a failure.
    if(newsockfd == INVALID_SOCKET){
        error("Error on accept");
    }

    // Communication between Client and Server from Server's P.O.V
    while(1){
        
        // Clear the buffer.
        memset(buffer, 0, 255);

        // Receiving the message from the client.
        n = recv(newsockfd, buffer, 255, 0);

        // Error while receiving
        if(n < 0){
            error("Error on receiving.");
        }

        // Showing client's message
        printf("Client : %s\n", buffer);

        // Clear the buffer.
        memset(buffer, 0, 255);

        // getting reply of the client from the buffer.
        fgets(buffer, 255, stdin);

        // Sending message to the client
        n = send(newsockfd, buffer, strlen(buffer), 0);

        // Error while writing
        if(n < 0){
            error("Error on sending.");
        }

        // Closing the communication.
        int i = strncmp("Bye", buffer, 3);
        if(i == 0){
            break;
        }
    }

    // Close the socket.
    closesocket(newsockfd);
    closesocket(sockfd);
    WSACleanup();
    return 0;
}