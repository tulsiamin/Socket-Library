// SINGLETON
#pragma once

#include <map>
#include "Server.h"

#define SERVER_MANAGER ServerManager::GetInstance()

class ServerManager 
{
private:
    static ServerManager *myInstance;
    std::map<std::string, Server*> myServers;

    // METHODS
    void AddServer(std::string, Server*);

public:
    void Create();
    bool Init();
    bool InitializeNewServer(std::string, int port);

    Server* GetServer(std::string);

    static ServerManager* GetInstance() { return myInstance; }
};
