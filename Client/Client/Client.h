#include<WinSock.h>
#include<iostream>
using namespace std;
#define receiveBufferSize 50;

typedef struct sockInfo
{
    SOCKET socket;
    SOCKADDR_IN target;
} SOCK_INFO;

class Client 
{
public:
    void Init();
    void ConnectToServer();
    void CloseSocketConnection();

private:
    SOCK_INFO mSockInfo;
    
    const char *ipadressOfServer;
    int portNumber;
    
    
};
