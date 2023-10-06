#include "Server.hpp"
#include <iostream>

// Define the port 
#define PORT 8080

int main(){

    Server server(PORT);
    server.Bind();
    server.Listen();

    while (true) {
    server.AcceptClient();
    server.ExecuteClientRequest();
    }

    return 0;
}