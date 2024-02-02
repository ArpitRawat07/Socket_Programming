# TCP File Transfer - Client-Server Application

This is a simple client-server file transfer application using TCP (Transmission Control Protocol). The application allows users to transfer a text file from a client to a server, or vice versa, word by word.

## Features

- **TCP Communication:** The client and server communicate over a reliable, connection-oriented TCP channel.
- **Word-by-Word Transfer:** The file is transferred word by word, maintaining the order and content integrity.
- **Usage of Sockets:** The application utilizes sockets for network communication.

## How It Works

1. **Client Side:**
   - The client reads a text file (e.g., "Text_File_To_Be_Transferred.txt").
   - It establishes a TCP connection with the server.
   - The file content is sent word by word to the server.

2. **Server Side:**
   - The server listens for incoming TCP connections.
   - Upon connection, it receives the words and reconstructs the file.

## Usage

1. **Compile the Code:**
   ```bash
   gcc -o Client.exe Client.c -lws2_32
   gcc -o Server.exe Server.c -lws2_32
  
2. **Run Server**
  `./Server.exe <port_number>`
3. **Run Client**
  `./Client.exe <server_ip> <port_number>`


## Future Uses/Applications
This simple file transfer application can serve as a foundation for more advanced use cases and applications. Some potential future uses include:

- Enhanced Security: Implementing encryption for secure file transfers.
- Parallel File Transfer: Handling multiple client connections concurrently.
- User Authentication: Adding user authentication for access control.
- Graphical User Interface (GUI): Developing a user-friendly GUI for ease of use.
