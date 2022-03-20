#include <iostream>
#include <WinSock2.h>

#pragma once

using namespace std;

class ReachOutToServer{
public:
    string message;
    char buf[4096];
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    string sendToServer(string aMessage);

};