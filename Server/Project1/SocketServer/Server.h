#pragma once

#include <string>
#include <map>
#include "ServerClient.h"

class Server
{
public:
    Server();
    Server(int);
    Server(std::string);
    Server(std::string, int);
    ~Server();

    // METHODS
    bool OpenConnection();
    bool Start();
    void AddClient(ServerClient*);

    const int GetPort() { return myInfo.port; }
    void SetPort(int port) { myInfo.port = port; }
    SOCKET GetSocket() { return myInfo.socket; }
    unsigned int GetClientCount() {}

    // FIELDS
    struct ServerInfo
    {
        SOCKET socket;
        WSADATA wsadata;
        SOCKADDR_IN socketAddress;
        int port;
    };

    ServerInfo myInfo;
    std::string myName;
    static const char* myIP;

private:
    std::map<std::string, ServerClient*> myClients;

};
