#pragma comment(lib, "Ws2_32.lib")
#include<iostream>
#include "Client.h"
using namespace std;

int main()
{
    Client *client = new Client();
    client->Init();
    client->ConnectToServer();
    client->CloseSocketConnection();

    getchar();
    return 0;
}

