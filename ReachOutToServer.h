#include <iostream>
#include <WinSock2.h>

#pragma once

class ReachOutToServer{
private:
    std::string message;
    char buf[4096];
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

public:
    std::string sendToServer(std::string aMessage);

};