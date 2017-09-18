#include "Server.h"

#include <iostream>
#include "ServerThreadCallbacks.h"

const char* Server::myIP = "10.206.27.6";

// thread callbacks
Server::Server()
{
}

Server::Server(int port)
{
    myInfo.port = port;
}

Server::Server(std::string name)
{
    myName = name;
}

Server::Server(std::string name, int port)
{
    myName = name;
    myInfo.port = port;
}

Server::~Server()
{
}

bool Server::OpenConnection()
{
    if (WSAStartup(0x0202, &myInfo.wsadata))
        return false;

    SOCKADDR_IN& target = myInfo.socketAddress;
    target.sin_port = htons(myInfo.port);
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = htonl(INADDR_ANY);
    myInfo.socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    return true;
}

bool Server::Start()
{
    SOCKADDR_IN& target = myInfo.socketAddress;
    int errorCode = bind(myInfo.socket, (SOCKADDR *)&target, sizeof(target));
    if (errorCode == SOCKET_ERROR)
        assert(0);

    std::cout << "Bind Successful!" << std::endl;

    listen(myInfo.socket, 1);

    // start a server
    Server* server = new Server();

    // Create Thread for Sending data
    HANDLE sendThreadHandle = CreateThread(NULL, 0, ServerThreadCallbacks::SendCallback, this, 0, NULL);

    // Create Thread for handling clients data
    HANDLE clientThreadHandle = CreateThread(NULL, 0, ServerThreadCallbacks::ClientThreadCallback, this, 0, NULL);

    return true;
}

void Server::AddClient(ServerClient* newClient)
{
}
