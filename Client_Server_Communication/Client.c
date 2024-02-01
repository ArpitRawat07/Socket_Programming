#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

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
    argc - Number of parameters(3)
    argv[0] - File name
    argv[1] - server_ip_address
    argv[2] - Port number
    */

    // Initialize Winsock
        WSADATA wsa;
        if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
            error("Failed to initialize Winsock.");
        }

    // Socket file descripters 
    int sockfd, portno, n;

    // Server internet address provided by sockaddr_in in netinet header file.
    struct sockaddr_in serv_addr;
    
    // Message in buffer
    char buffer[255];

    // If arguments are less than required.
    if(argc < 3){
        fprintf(stderr, "usage %s hostname post \t File name or Server IP address or Port number not provided. Program terminated\n", argv[0]);
        exit(1);
    }

    // Port number
    portno = atoi(argv[2]);

    // Communication domain - AF_INET(Address Family), Communication Type - SOCK_STREAM(TCP/UDP), Communication Protocol - 0(TCP)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // If socket resulted in a failure.
    if(sockfd == INVALID_SOCKET){
        error("Error opening Socket.");
    }

    // Get host IP address using getaddrinfo
    struct addrinfo hints, *res;

    // Clear hints
    memset(&hints, 0, sizeof(hints));

    // Set the address family and the protol for the server(client's preference).
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // Incorrect server ip address or server is off
    if(getaddrinfo(argv[1], argv[2], &hints, &res) != 0){
        fprintf(stderr, "Error, no such host.\n");
        WSACleanup();
        exit(1);
    }


    struct sockaddr_in *ipv4 = (struct sockaddr_in *)res -> ai_addr;

    // Clear any data/text in server address
    memset((char*) &serv_addr, 0, sizeof(serv_addr));

    // Set the address family of the server socket.
    serv_addr.sin_family = AF_INET;
    // Copies the ipv4 address to server address
    serv_addr.sin_addr = ipv4->sin_addr;
    // Set the port number that the client wants to connect.
    serv_addr.sin_port = htons(portno);

    // Error on Connect
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("Connection Failed.");
    }

    // Free the result list.
    freeaddrinfo(res);

    while(1){

        // Clear buffer
        memset(buffer, 0, 255);

        // getting reply from client from the buffer.
        fgets(buffer, 255, stdin);

        // Sending message to the server
        n = send(sockfd, buffer, strlen(buffer), 0);

        // Error while send
        if(n < 0){
            error("Error while sending");
        }

        // Clear the buffer
        memset(buffer, 0, 255);

        // Receiving message from the serverd
        n = recv(sockfd, buffer, 255, 0);

        if(n < 0){
            error("Error while receiving.");
        }
        
        // Showing server's message
        printf("Server: %s", buffer);

        int i = strncmp("Bye", buffer, 3);
        if(i == 0){
            break;
        }
    }

    // Close the socket.
    closesocket(sockfd);
    WSACleanup();
    return 0;
}
