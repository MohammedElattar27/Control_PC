# Control_PC

This is a simple C++ server application that listens for incoming connections from clients and executes predefined commands based on client requests. It can be used as a starting point for creating your own server applications.


## Table of Contents
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Setup Client](#Setup-Client)
- [Adding Custom Commands](#adding-custom-commands)
- [Acknowledgments](#Acknowledgments)
- [Execution Result](#Execution-Result)

## Features

- Accepts incoming connections from multiple clients (up to a defined limit).
- Sends a welcome message and a help menu to clients upon connection.
- Executes predefined commands based on client requests.
- Cleans client requests by removing spaces and converting to lowercase.
- Handles errors gracefully.


## Prerequisites

Before you begin, ensure you have met the following requirements:

- C++ compiler (e.g., g++)
- Linux-based operating system (the example is tested on Ubuntu)
- Basic knowledge of C++ and socket programming


## Getting Started

1. Clone this repository to your local machine:

   ```bash
   https://github.com/MohammedElattar27/Control_PC.git
   ```

2. Compile the server program:

      ```bash
      g++ main.cpp Server.cpp -o server -std=c++11
      ```


## Usage
1. Start the server:

   ```bash
   ./server
   ```

   The server will start listening on the specified port (default is 8080).

2. Connect to the server using a client application or a terminal.

3. Send one of the predefined commands to the server, e.g. "terminal," "calculator," "firefox," or "code."

4. The server will execute the corresponding command and send a success message to the client.

5. You can add your own custom commands by modifying the server code.
   

## Setup Client

1. Download [Tcp Udp Server & Client]([url](https://play.google.com/store/apps/details?id=tcpudpserverclient.steffenrvs.tcpudpserverclient&pcampaignid=web_share))
2. follow these steps:

![client](https://github.com/MohammedElattar27/Control_PC/assets/141765152/b790a4eb-28f7-45dd-af79-df625778b923)



## Adding Custom Commands

To add custom commands to the server:

1. Open the `Server.cpp` file.

2. In the `ExecuteClientRequest` method, add conditional statements to handle your custom commands.

   Example:

   ```cpp
   // Add custom command
   else if(strcmp(buffer, "mycommand") == 0){
       Server::ExecuteCommand("my_custom_script.sh", clientSocket);
   }
   ```

3. Create a script or executable for your custom command (e.g., `my_custom_script.sh`) and place it in the appropriate location.

4. Recompile the server program.
   
      ```bash
      g++ main.cpp Server.cpp -o server -std=c++11
      ```

5. Start the server, and you can now execute your custom command by sending it from the client.


## Acknowledgments

- This project was created as a learning exercise in socket programming and C++.

Feel free to customize and expand upon this project to further develop your skills and create more advanced server-client applications.


## Execution Result

![Control_PC](https://github.com/MohammedElattar27/Control_PC/assets/141765152/eca07dfc-b117-4212-946a-7b5acaf5b071)




