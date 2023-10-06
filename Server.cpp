#include "Server.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <algorithm>
#include <sys/wait.h>

// Define the maximum number of clients that can connect simultaneously.
#define MAX_CLIENT_NUM 3

Server::Server(int port) : port(port){
    // Create a server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cout << "Error creating the server socket" << std::endl;
        exit(EXIT_FAILURE);
    }
}

Server::~Server(){
    // Close the server socket 
    if (serverSocket != -1) {
        close(serverSocket);
    }
}

void Server::Bind(){
    // Set up the server's address information
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr= INADDR_ANY;

    // Bind the server socket to the specified address and port
    if(bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0){
        perror("bind");
        exit(EXIT_FAILURE);  
    }
}

void Server::Listen(){
    // Start listening for incoming connections
    listen(serverSocket, MAX_CLIENT_NUM);
    std::cout << "Server is listening on port: "<< port << std::endl;
}

void Server::AcceptClient(){
    // Check if serverSocket is valid
    if (serverSocket == -1) {
        std::cout << "Server socket is not valid" << std::endl;
        return;
    }

    // Accept an incoming connection from client
    clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == -1) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Send welcome message to the client
    const char* helloMsg = "Hello, from server!\n";
    send(clientSocket, helloMsg, strlen(helloMsg), 0);

    // Send help message to the client
    const char* helpMsg = "--------------------------------\n"
                            "help menue \n"
                            "--------------------------------\n "
                            "Type any commands:\n"
                            "1. terminal\n"
                            "2. calculator\n" 
                            "3. firefox\n"
                            "4. code (for VS-Code)\n"
                            "--------------------------------\n";
    send(clientSocket, helpMsg, strlen(helpMsg), 0);
}

// Method to execute the client request 
void Server::ExecuteClientRequest(){
    // Create a buffer
    char buffer[1024];

    // Clear the buffer
    memset(buffer, 0, sizeof(buffer));
    
    // Read data from the client into the buffer
    int bytes = read(clientSocket, buffer, sizeof(buffer));  
    if (bytes == -1){
        perror ("read");
    }

    // Print the received data
    std::cout << "Received request: "<< buffer << std::endl;

    // Clean the recived data
    Server::CleanRequest(buffer);
    std::cout << "After cleaning request: "<< buffer << std::endl;

    // Executing commands
    // Open terminal
    if(strcmp(buffer, "terminal") == 0){
        Server::ExecuteCommand("gnome-terminal", clientSocket);
    }
    // Open calculator
    else if(strcmp(buffer, "calculator") == 0){
        Server::ExecuteCommand("gnome-calculator", clientSocket);
    }
    // Open firefox
    else if(strcmp(buffer, "firefox") == 0){
        Server::ExecuteCommand("firefox", clientSocket);
    }
    // Open vs-code
    else if(strcmp(buffer, "code") == 0){
        Server::ExecuteCommand("code", clientSocket);
    }
    // Open firefox
    else if(strcmp(buffer, "firefox") == 0){
        Server::ExecuteCommand("firefox", clientSocket);
    }
    // Unknown command
    else{
        std::cout << "wrong command" << std::endl;
        close(clientSocket);
    }
    // For adding new commands:
    // Call 'ExecuteCommand' method the desired command name 

    // Close the client socket
    close(clientSocket);
}

//***************************//
// **** Private Methods *****// 
//***************************//
// Clean received request  from clients 
//     1. Remove white spaces
//     2. Convert to lowercase
void Server::CleanRequest(char* buffer){
    std::string input(buffer);

    // Remove spaces from the string
    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());

    // Convert the string to lowercase
    for (char &c : input) {
        c = std::tolower(c);
    }
    strcpy(buffer , input.data() );
}

// Function to execute command 
void Server::ExecuteCommand(const char* command, int clientSocket){
    // New child process
    pid_t childPid = fork();

    if (childPid == -1)
    {
        perror("fork");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    if(childPid == 0){
        // Child process takes control
        int result = execlp(command, command,nullptr);

        // Check if execlp failed
        if(result == -1){
            perror("execlp");
            close(clientSocket);
            exit(EXIT_FAILURE);
        }
    }else{
        // Parent process takes control
        // Wait child process to complete
        int status;
        waitpid(childPid, &status, 0);

        // Send response to the client
        const char* resultMsg = "Command executed successfully!\n";
        send(clientSocket, resultMsg, strlen(resultMsg), 0);
    }
}