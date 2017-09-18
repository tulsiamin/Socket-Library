#include "ServerManager.h"
#include <iostream>

ServerManager* ServerManager::myInstance = 0;

void ServerManager::Create()
{
    if (myInstance)
        return;
    myInstance = new ServerManager();
}

bool ServerManager::Init()
{
    return true;
}

bool ServerManager::InitializeNewServer(std::string name, int port)
{
    Server* server = new Server(name, port);
    AddServer(name, server);
    if (!server->OpenConnection())
        return false;
    if (!server->Start())
        return false;

    return true;
}

Server* ServerManager::GetServer(std::string name)
{
    if (!myServers[name])
    {
        std::cout << name << " server does not exist!" << std::endl;
        return NULL;
    }
    return myServers[name];
}

void ServerManager::AddServer(std::string name, Server* server)
{
    if(server)
        myServers[name] = server;
}
