#pragma comment(lib, "Ws2_32.lib")
#include<Windows.h>
#include<WinSock.h>
#include<iostream>

SOCKET connections[100];
int numOfConnections=0;
SOCKET sock;
WSADATA wsdata;
SOCKADDR_IN target;
int port;

typedef struct ClientDetails 
{
    SOCKET socket;
    HANDLE threadHandle;
} ClientDetails;

DWORD WINAPI SendThread(LPVOID lpParam)
{
    int isConnected = 1;
    while (isConnected != SOCKET_ERROR)
    {
        char buffer[50];
        std::cin.getline(buffer, sizeof(buffer));
        for (int index = 0; index < numOfConnections; index++)
        {
            isConnected = send(connections[index], buffer, sizeof(buffer), NULL);
        }
     }

    return 0;
}

DWORD WINAPI ReceiveThread(LPVOID lpParam)
{
    ClientDetails* details = (ClientDetails*)lpParam;
    SOCKET socket = details->socket;
    HANDLE handle = details->threadHandle;

    std::cout << "Client Connected! --- Handle: " << handle << std::endl;;
	while(true)
	{
        char receivedData[50];

        int errorCode = recv(socket, (char*)receivedData, sizeof(receivedData), NULL);
        if (errorCode == SOCKET_ERROR)
            break;

        for (int index = 0; index < numOfConnections; index++)
        {
            send(connections[index], receivedData, sizeof(receivedData), NULL);
        }

        std::cout << receivedData << std::endl;
    }

    return false;
}

DWORD WINAPI AcceptConnection(LPVOID lpParam)
{
    int len = sizeof(target);

    while (true) {
        SOCKADDR_IN client;
        client.sin_family = AF_INET;
        SOCKET clientSocket = accept(sock, (LPSOCKADDR)&client, &len);
        connections[numOfConnections++] = clientSocket;
        
        std::cout << "IP: " << inet_ntoa(client.sin_addr) << std::endl;
        std::cout << "Port: " << client.sin_port << std::endl;

        ClientDetails details;
        details.socket = clientSocket;
        HANDLE receiveHandle = CreateThread(NULL, 0, ReceiveThread, &details, 0, NULL);
        HANDLE sendHandle = CreateThread(NULL, 0, SendThread, &details, 0, NULL);
        details.threadHandle = receiveHandle;
    }

    return false;
}

bool ListenOnPort(int portno)
{
    port = portno;
 
    int error = WSAStartup(0x0202, &wsdata);
    if (error)
        return false;

    target.sin_port = htons(port);
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = htonl(INADDR_ANY);
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == INVALID_SOCKET)
    {
        return false;
    }
    if (bind(sock, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
    {
        return false;
    }
    listen(sock, 1);

    HANDLE accepthandle = CreateThread(NULL, 0, AcceptConnection, NULL, 0, NULL);

    return true;
}

void closeconnection()
{
	if(sock)
	{
		closesocket(sock);
	}
	 WSACleanup();
}