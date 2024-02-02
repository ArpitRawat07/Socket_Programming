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

    // f - File pointer, words - number of words, ch - number of words.
    FILE *f;
    int words;
    int ch = 0;

    // Writing onto a new file.(If no file with the given name is present, fopen creates a new file.)
    f = fopen("Transferred_File.txt", "w");

    // Error while writing
    if (f == NULL) {
        error("Error opening file for writing.");
    }

    // Receive the words
    n = recv(newsockfd, (char *)&words, sizeof(int), 0);
    // Error receving the file
    if(n < 0){
        error("Error receiving the file.");
    }
    
    // Writing on the file
    while(ch != words){
        // Receive the words
        n = recv(newsockfd, (char *)&buffer, sizeof(buffer), 0);
        // Error receiving the file
        if(n < 0){
            error("Error receiving the file.");
        }
        fprintf(f, "%s ", buffer);
        ch++;
    }

    // File received
    printf("The file has been received successfully. It is saved by the name Transferred_File.txt .");
    
    // Close the file
    fclose(f);

    // Close the socket.
    closesocket(newsockfd);
    closesocket(sockfd);
    WSACleanup();
    return 0;
}