# Client-Server Communication Simulation

This project demonstrates a simple client-server communication simulation using socket programming in C. The client and server applications allow exchanging messages over a network.

## Prerequisites

- [Winsock Library](https://docs.microsoft.com/en-us/windows/win32/winsock/getting-started-with-winsock)

## Building and Running

### Server

1. Compile the server code:

   ```bash
   gcc -o Server.exe Server.c -lws2_32
   ```
2. Run the Server:
   ```bash
   Server.exe [port_number]
   ```
   Port number can be anything between 1025 - 65535.

### Client

1. Compile the client code:

   ```bash
   gcc -o Client.exe Client.c -lws2_32
   ```
2. Run the Server:
   ```bash
   Client.exe [server_ip_address] [port_number]
   ```
   Take port number same as the above.
   To know the server_ip_address of your system run:
   ```bash
   ipconfig
   ```
   Take the IPv4 Address as the server_ip_address.

### Usage
  * Start the server on a machine.

  * Run the client, providing the server's IP address and port number as command-line arguments.

  * Begin sending and receiving messages between the client and server.

  * Type "Bye" to terminate the communication.

### Project Structure
- server.c: Source code for the server application.
- client.c: Source code for the client application.
