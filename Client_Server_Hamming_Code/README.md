# Client - Server Hamming Code Implementation

## Overview
This project implements Hamming Code for error detection and correction in a client-server architecture. Hamming Code is a popular error-correcting code used in digital communication to ensure data integrity.

## Features
- **Client-Server Architecture:** The project is designed using a client-server model, where the server generates and transmits Hamming Code, and the client detects and corrects errors.
- **Error Detection and Correction:** Hamming Code allows the detection and correction of single-bit errors in transmitted data, enhancing the reliability of communication.
- **Socket Programming:** Implemented using socket programming in C, facilitating communication between the client and server over a network.

## How it Works
1. **Server Side:**
   - The server generates Hamming Code for a given set of data bits.
   - Transmits the Hamming Code to the client.

2. **Client Side:**
   - Receives the transmitted Hamming Code.
   - Detects and corrects errors using Hamming Code principles.
   - Notifies the user of successful error correction or reports the position of the error.

## Future Uses/Applications
- **Digital Communication Systems:** Integration into digital communication systems to enhance data reliability in transmission.
- **File Transfer Protocols:** Incorporation into file transfer protocols to ensure error-free data transfer.
- **Data Storage:** Implementation in storage systems to improve data integrity.

## How to Run
1. **Compile the Server and Client:**
   ```bash
   gcc -o Client.exe Client.c -lws2_32
   gcc -o Server.exe Server.c -lws2_32
   ```
2. Run Server:
  ```./Server.exe <port_number>```
3. Run Client:
   ```./Client.exe <server_ip> <port_number>```
