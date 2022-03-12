#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include <ws2tcpip.h>
#include <climits>
#include <WinSock2.h>



//to be able to use sockets
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "advapi32")

using namespace std;

class ReachOutToServer{
public:
    string message;
    char buf[4096];
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);


    string sendToServer(string aMessage) {
        string ipAddress = "192.168.1.15";  //IP of server192.168.1.13  // ip of home 174.86.47.26  // change this back
        int port = 7000;                    //Listening Port # of Server
        std::string s;
        std::stringstream ss;

        //init winsock
        WSAData data;
        WORD ver = MAKEWORD(2, 2);
        int wsResult = WSAStartup(ver, &data);
        if (wsResult != WSAStartup(ver, &data)) {
            cerr << "Can't start Winsock, Err #" << wsResult << endl;
            return "failed";
        }

        //create socket
          /// moved to top: SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) {
            cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
            return "failed";
        }

        //fill in kint structure
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(port);
        inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

        //connect to server
        int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
        if (connResult == SOCKET_ERROR) {
            cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
            closesocket(sock);
            WSACleanup();
            return "failed";
        }

        //Do-Wile loop to send and recieve data
          /// Moved to top: char buf[4096];

        message = aMessage;
        bool secondtimethrough = false;
        int timesthrough = 0;
        //message = "3.5";
        do {
            int sendResult = send(sock, message.c_str(), message.size() + 1, 0);
            if (sendResult != SOCKET_ERROR) {
                //wait for response
                ZeroMemory(buf, 4096);
                int bytesRecived = recv(sock, buf, 4096, 0);
                if (bytesRecived > 0) {
                    
                    //Echo response to console  //uncomment only for troubleshooting:
                    // 
                    cout << "SERVER> " << string(buf, 0, bytesRecived) << endl;

                    ss << buf;
                    s = ss.str();
                }
            }
            if (secondtimethrough != true) {
                secondtimethrough = true;
                system("pause");
            }
            else {
                timesthrough++;
            }

        } while (timesthrough == 0);


        //Gracefully close down everything
        closesocket(sock);
        WSACleanup();

        return s;
    }

};

int main(){
    //declare a new instance of the ReachOutToServer class
    ReachOutToServer server;
    //declare the string to hold our message
    string messageToServer;

    
    //ask user for the message they wish to send
    cout << "Hello User (type \"exit\" to close this program)" << endl << "Enter messageToServer: ";
    getline(cin, messageToServer);
    server.sendToServer(messageToServer);

    return 0;
}