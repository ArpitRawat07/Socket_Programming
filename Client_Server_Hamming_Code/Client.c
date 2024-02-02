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

    // Data at receiver, sample corrupted array.
    int data[7], test[7];

    // Parity bits
    int p, p1, p2, p4;

    // Receive data
    n = recv(sockfd, (char *) &data, sizeof(data), 0);

    // Error on receiving
    if(n < 0){
        error("Error while receiving hamming code.");
    }
    
    // Data received
    printf("The data received is: \n");
    
    // Hamming code
    for(int i=0; i<7; i++){
        printf("%d ", data[i]);
    }

    // Ask for test data
    printf("\nPlease enter the test data (manually tampered test data):\n");

    // Test data
    for(int i=0; i<7; i++){
        scanf("%d", &test[i]);
    }

    // Calculate Parity bits
    p1 = test[6] ^ test[4] ^ test[2] ^ test[0];
    p2 = test[5] ^ test[4] ^ test[1] ^ test[0];
    p4 = test[3] ^ test[0] ^ test[2] ^ test[1];

    // Calculate tampered bit
    p = (4 * p4) + (2 * p2) + p1;

    // No error
    if(p == 0){
        printf("No Error.");
    }
    // Error
    else{
        printf("The error is at position %d\n", p);
        printf("The correct hamming code is: ");
        if(test[7 - p] == 0){
            test[7 - p] = 1;
        }
        else{
            test[7 - p] = 0;
        }
        for(int i=0; i<7; i++){
            printf("%d", test[i]);
        }
    }

    // Correct data
    printf("\n The correct data was : %d%d%d%d\n", test[0], test[1], test[2], test[4]);

    // Close the socket.
    closesocket(sockfd);
    WSACleanup();
    return 0;
}
