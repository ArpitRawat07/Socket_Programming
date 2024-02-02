# Client-Server Calculator

## Overview

This project implements a simple client-server calculator using socket programming in C. The server performs basic arithmetic operations based on the client's input, allowing users to perform calculations remotely.

## Features

- Addition
- Subtraction
- Multiplication
- Division

## How It Works

1. **Server Setup:**
   - The server listens on a specified port for incoming connections.
   - Upon a connection request from a client, it accepts the connection and waits for client input.

2. **Client Interaction:**
   - The client connects to the server by providing the server's IP address and port number.
   - The client enters two numbers and selects an operation (addition, subtraction, multiplication, or division).

3. **Calculation and Response:**
   - The server receives the client's input, performs the requested calculation, and sends the result back to the client.
   - The client displays the result.

## Getting Started

### Prerequisites

- [GCC](https://gcc.gnu.org/) compiler
- Windows operating system (for Winsock implementation)

### Build and Run

1. Compile the server: `gcc -o server.exe server.c -lws2_32`
2. Compile the client: `gcc -o client.exe client.c -lws2_32`
3. Run the server: `./server.exe <port>`
4. Run the client: `./client.exe <server_ip> <port>`
- -lws2_32 is for linking winsock2 library to the program.
- port number can be anything from 1024 - 65535
- Take IPv4 IP address from cmd by running: `ipconfig`
  
## Future Uses/Applications

This simple client-server calculator can serve as a foundation for more sophisticated applications. Potential future uses include:

- Integration into larger systems for distributed computing.
- Implementation of a secure communication layer for sensitive calculations.
- Extension to support additional mathematical functions or complex operations.

Feel free to contribute, enhance, and adapt this project for various applications!

## Contributing

If you have any ideas or improvements, feel free to open an issue or submit a pull request. Contributions are welcome!

