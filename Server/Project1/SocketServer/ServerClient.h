#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <Windows.h>
#include <winsock.h>
#include <string>

class ServerClient
{
public:
    typedef struct ClientInfo
    {
        SOCKET socketHandle;
        SOCKADDR_IN socketDetails;
    }ClientInfo;

    ServerClient() {}
    ServerClient(int id) { myId = id; }
    ServerClient(int id, ClientInfo info) { myId = id; myInfo = info; }

    ~ServerClient(void) {}

    int GetID() { return myId; }
    void SetName(char* name) { myName = name; }
    std::string GetName() { return myName; }
    const char* GetIPAddress() { return inet_ntoa(myInfo.socketDetails.sin_addr); }
    const int GetPort() { return myInfo.socketDetails.sin_port; }
    const SOCKET GetSocket() { return myInfo.socketHandle; }
    void SetSocketHandle(SOCKET socketHandle) { myInfo.socketHandle = socketHandle; }
    void SetSocketAddress(SOCKADDR_IN address) { myInfo.socketDetails = address; }

    //FIELDS
private:
    int myId;
    std::string myName;
    
    ClientInfo myInfo;

};
