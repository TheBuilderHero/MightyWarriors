#include <string>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <sstream>

#include "ReachOutToServer.h"
#include "Cipher.h"

using namespace std;


string ReachOutToServer::sendToServer(string aMessage) {
    Cipher decode; // declare a new Decipher class
    string ipAddress = "174.86.47.26";  //IP of server192.168.1.13  // ip of home 174.86.47.26  // change this back
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
                
                //decipher the message from the server
                
                string output = decode.decipher(buf);

                //Echo response to console  //uncomment only for troubleshooting:
                //cout << "SERVER> " << output << endl; 
                //before we were using cipher we used string(buf, 0, bytesRecived) as the output

                ss << buf;
                s = ss.str();
            }
        }
        if (secondtimethrough != true) {
            secondtimethrough = true;
            //system("pause"); //removed because it seems to be working fine sending and recieving data without it in place
        }
        else {
            timesthrough++;
        }

    } while (timesthrough == 0);


    //Gracefully close down everything
    closesocket(sock);
    WSACleanup();
    decode.decipher(buf);
    switch (decode.responseType){
        case 1:
        //the server has check to see if the username was valid or not.
        return decode.item2;
        break;
        //others will be added to setup the usage of other features like pulling data and cteating accounts
        case 2: //user creation
        return s;
        break;
        case 3: //logon reutrn from the server
        return decode.item2;
        break;

        default:
        return s;
    }
}
