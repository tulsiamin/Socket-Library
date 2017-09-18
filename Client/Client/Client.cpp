
#include "Client.h"
#include <iostream>
#include <assert.h>
using namespace std;

HANDLE LockMutex;

SOCK_INFO* gServerSockInfo;

DWORD WINAPI threadToSend(LPVOID lpParameter)
{
    SOCK_INFO* clientSockInfo = (SOCK_INFO*)lpParameter;
    char datatoSend[50];
    
    memset(datatoSend, 0, sizeof(datatoSend));

    int isConnected = 1;
    while (true)
    {
        cin.getline(datatoSend, sizeof(datatoSend));
        int errorCode = sendto(clientSockInfo->socket, datatoSend, sizeof(datatoSend), NULL, (sockaddr*)&(gServerSockInfo->target), sizeof(gServerSockInfo->target));
        if (errorCode == 0)
            assert(0);
    }

    return 0;
}

DWORD WINAPI threadToRecv(LPVOID lpParameter)
{
    SOCK_INFO* clientSockInfo = (SOCK_INFO*)lpParameter;
    char datatoRecv[50];

    unsigned long param = 1;
    int errorCode = ioctlsocket(clientSockInfo->socket, FIONBIO, &param);
    if (errorCode != 0)
    {
        assert(0);
    }
    while (true)
    {
        memset(datatoRecv, 0, sizeof(datatoRecv));
        int size = sizeof(gServerSockInfo->target);
        int errorCode = recvfrom(clientSockInfo->socket, (char*)datatoRecv, sizeof(datatoRecv), NULL, (sockaddr*) &gServerSockInfo->target, &size);
        if (errorCode == 0)
            assert(0);

        if( datatoRecv[0] != NULL )
            cout << "data is " << datatoRecv << endl;
    }

    return 0;
}

void Client::Init()
{
    WSADATA wsadata;
    int error = WSAStartup(0x0202, &wsadata);
    if (error)
        return;
    if (wsadata.wVersion != 0x0202)
    {
        WSACleanup();
        return;
    }

    SOCKET& recvSocket = mSockInfo.socket;
    SOCKADDR_IN& target = mSockInfo.target;

    recvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    target.sin_family = AF_INET;
    target.sin_port = htons(3000);
    target.sin_addr.s_addr = htonl(INADDR_ANY);

    int result = bind(recvSocket, (sockaddr*)&target, sizeof(target));
    if (result != 0)
    {
        assert(0);
    }

}

void Client ::ConnectToServer()
{
    gServerSockInfo = new SOCK_INFO;

    ipadressOfServer = "10.206.27.6";
    portNumber = 8082;
    gServerSockInfo->target.sin_family = AF_INET;
    gServerSockInfo->target.sin_port = htons(portNumber);
    gServerSockInfo->target.sin_addr.s_addr = inet_addr(ipadressOfServer);
    gServerSockInfo->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    LockMutex = CreateMutex(NULL, FALSE, NULL);
    HANDLE aThread[2];

    aThread[0] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)threadToSend, &mSockInfo, NULL, NULL);
    aThread[1] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)threadToRecv, &mSockInfo, NULL, NULL);
    WaitForMultipleObjects(2, aThread, TRUE, INFINITE);

    CloseHandle(aThread[0]);
    CloseHandle(aThread[1]);
}

void Client :: CloseSocketConnection()
{
    if (mSockInfo.socket)
    {
        closesocket(mSockInfo.socket);
    }
    delete gServerSockInfo;
}