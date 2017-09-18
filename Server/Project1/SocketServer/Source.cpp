#include <iostream>
#include "ServerManager.h"

void Init()
{
    SERVER_MANAGER->Create();
    
    bool result = false;
    result |= SERVER_MANAGER->Init();
    result |= SERVER_MANAGER->InitializeNewServer("Chat Server!", 8082);
}

int main()
{
    Init();
    while (1);

    return 0;
}