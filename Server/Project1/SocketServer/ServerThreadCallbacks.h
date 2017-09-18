#pragma once
#include <windows.h>
#include "ServerManager.h"
#include <assert.h>

int ID = 0;

namespace ServerThreadCallbacks
{
    typedef struct NewClient
    {
        SOCKET socket;
        SOCKADDR_IN address;
    }NewClient;

    DWORD WINAPI SendCallback(LPVOID lpParam)
    {
        Server* server = (Server*)lpParam;
        while (true)
        {
            int choice = 0;
            std::cin >> choice;
            switch(choice) 
            {
            case 1: // display all connected Clients
                break;
            }
        }
    }

    DWORD WINAPI ClientThreadCallback(LPVOID lpParam)
    {
        Server* server = (Server*)lpParam;

        std::cout << "Server Started at " << server->GetPort() << std::endl;

        unsigned long param = 1;
        int errorCode = ioctlsocket(server->GetSocket(), FIONBIO, &param);
        if (errorCode != 0)
        {
            assert(0);
        }
        
        sockaddr_in address;
        while (true)
        {
            char data[100];
            memset(data, 0, sizeof(0));

            int size = sizeof(address);
            errorCode = recvfrom(server->GetSocket(), data, sizeof(data), NULL, (sockaddr*) &address, &size);
            if ((errorCode != 0) && (data[0] != '\0'))
            {
                std::cout << data << std::endl;
            }
        }

        return 0;
    }

};