#include <iostream>
#include <WinSock2.h>

#pragma once

class ReachOutToServer{
private:
    std::string message;
    char buf[8192]; //doubled to 8192 from 4096
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

public:
    enum RequestIDs {LOAD_ALL_PLAYER_DATA = 28, GET_ALL_DIALOGUE_DATA = 27};
    std::string sendToServer(std::string aMessage);
    std::string getIPFromHostName(char * hostname);
    void requestFromServer(RequestIDs requestID);
    std::string convertRequestIDEnumToString(RequestIDs id);

};