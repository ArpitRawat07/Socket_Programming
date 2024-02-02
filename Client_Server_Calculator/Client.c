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

    int num1, num2, choice, answer;

        // Num1
    // Clear the buffer
S:  memset((char *) &buffer, 0, sizeof(buffer));
    // Receive from socket
    n = recv(sockfd, (char *)&buffer, 255, 0);
    // Error while receiving
    if(n < 0){
        error("Error receiving from the socket");
    }

    // Printing the message in the buffer sent by the Server.
    printf("Server - %s\n", buffer);
    // Enter num 1
    scanf("%d", &num1);
    // Sending num1 to the server
    n = send(sockfd, (char *)&num1, sizeof(num1), 0);
    // Error while sending num1
    if(n < 0){
        error("Error while sending num1 to the server.");
    }

        // Num2
    // Clear the buffer
    memset((char *) &buffer, 0, sizeof(buffer));
    // Receive from socket
    n = recv(sockfd, (char *)&buffer, 255, 0);
    // Error while receiving
    if(n < 0){
        error("Error receiving from the socket");
    }
    
    // Printing the message in the buffer sent by the Server.
    printf("Server - %s\n", buffer);
    // Enter num 2
    scanf("%d", &num2);
    // Sending num2 to the server
    n = send(sockfd, (char *)&num2, sizeof(num2), 0);
    // Error while sending num2
    if(n < 0){
        error("Error while sending num2 to the server.");
    }

        // Choice
    // Clear the buffer
    memset((char *) &buffer, 0, sizeof(buffer));
    // Receive from socket
    n = recv(sockfd, (char *)&buffer, 255, 0);
    // Error while receiving
    if(n < 0){
        error("Error receiving from the socket");
    }
    // Printing the message in the buffer sent by the Server.
    printf("Server - %s\n", buffer);
    // Enter choice
    scanf("%d", &choice);
    // Sending choice to the server
    n = send(sockfd, (char *)&choice, sizeof(choice), 0);
    // Error while sending choice
    if(n < 0){
        error("Error while sending choice to the server.");
    }

    // Exit if choice == 5
    if(choice == 5){
        goto Q;
    }

    // Receiving answer from the server
    n = recv(sockfd, (char *)&answer, sizeof(int), 0);
    // Error while receiving answer
    if(n < 0){
        error("Error while receiving answer");
    }
    // Printing the answer.
    printf("Server - The answer is: %d\n", answer);

    if(choice != 5){
        goto S;
    }

    // Close the socket.
Q:  printf("You have selected to exit.\nExit Successful.");
    closesocket(sockfd);
    WSACleanup();
    return 0;
}
