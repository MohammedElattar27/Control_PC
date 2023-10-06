#pragma once

#include <netinet/in.h>



class Server {
    public:
    // Constructor: Initializes the server with the given port.
    Server(int port);

    // Destructor: Cleans up resources when the server object is destroyed.
    ~Server();

    // Bind: Binds the server socket to the specified address and port.
    void Bind();
    // Listen: Starts listening for incoming connections.
    void Listen();
    // AcceptClient: Accepts an incoming connection from a client and sends a welcome message and help menu.
    void AcceptClient();
    // ExecuteClientRequest: Handles the execution of client requests.
    void ExecuteClientRequest();

    private:
    int serverSocket, clientSocket;
    int port;
    struct sockaddr_in serverAddress;

    // CleanRequest: Cleans up the received request by removing spaces and converting to lowercase.
    void CleanRequest(char* buffer);
    // ExecuteCommand: Executes a command in a child process and sends the result back to the client.
    void ExecuteCommand(const char* command, int clientSocket);

};