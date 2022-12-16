#include <string>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <sstream>
#include <cstring>

#include "ReachOutToServer.h"
#include "Cipher.h"

using namespace std;


string ReachOutToServer::sendToServer(string aMessage) {
    Cipher code; // declare a new Decipher class
    char SERVER_HOSTNAME[] = {"kotaserver.xyz"};
    string ipAddress = getIPFromHostName(SERVER_HOSTNAME);//"174.86.238.171"; //(as of 8/8/2022)
    if(ipAddress == "failed"){
        system("pause");
        return "FailedConnect";
    }
    int port = 7000;                    //Listening Port # of Server
    std::string s[2];
    std::stringstream ss;

    //init winsock
    WSAData data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != WSAStartup(ver, &data)) {
        cerr << "Can't start Winsock, Err #" << wsResult << endl;
        return "failedwinsock";
    }

    //create socket
        /// moved to top: SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
        return "failedsock";
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
        return "FailedConnect";
    }

    //Do-Wile loop to send and recieve data
        /// Moved to top: char buf[4096];

    message = aMessage;

    bool secondtimethrough = false;
    int timesthrough = 0;
    int messageFromSeverLength;
    //message = "3.5";
    do {
        int sendResult = send(sock, (to_string(message.size() + 1)  + "~").c_str(), (to_string(message.size() + 1)  + "~").size() + 1, 0); //first is used to get length info of data to server prior to sending it.
        if (sendResult != SOCKET_ERROR) {
            //wait for response
            ZeroMemory(buf, 8192); //doubled from 4096
            int bytesRecived = recv(sock, buf, 8192, 0);
            //cout << buf << endl; //this was four trouble shooting
            //system("pause");
            if (bytesRecived > 0) {
                stringstream ssConvert;
                string responseVerified;
                ssConvert << buf;
                responseVerified = ssConvert.str();
                //These were for testing:
                //cout << "Recv: " << responseVerified << " Sent Item: " << message << endl;
                //system("pause");
            }
        }
        int sendResult2 = send(sock, message.c_str(), message.size() + 1, 0); //sends the data to the server. (server then responds with length of data it will send back)
        if (sendResult2 != SOCKET_ERROR) {
            //wait for response
            ZeroMemory(buf, 8192); //doubled from 4096
            int bytesRecived = recv(sock, buf, 8192, 0);
            //cout << buf << endl; //this was four trouble shooting
            //system("pause");
            if (bytesRecived > 0) {
                stringstream ssConvert;
                string responseLengthVerified;
                ssConvert << buf;
                responseLengthVerified = ssConvert.str();
                //This was for testing:
                //cout << responseLengthVerified << endl;
                try{
                    messageFromSeverLength = stoi(responseLengthVerified);
                } catch(invalid_argument){
                    cout << "int sendResult2 = send(sock, message.c_str(), message.size() + 1, 0); //sends the data to the server. (server then responds with length of data it will send back)" << endl;
                    system("pause");
                }
            }
        }
        int sendResult3 = send(sock, to_string(messageFromSeverLength).c_str(), to_string(messageFromSeverLength).size() + 1, 0); //Tell the server we know the length of the data that is going to be sent. It can send it now.
        if (sendResult3 != SOCKET_ERROR) {
            //wait for response
            ZeroMemory(buf, 8192); //doubled from 4096
            int bytesRecived = recv(sock, buf, messageFromSeverLength, MSG_WAITALL);
            //cout << buf << endl; //this was four trouble shooting
            //system("pause");
            if (bytesRecived > 0) {
                
                //decipher the message from the server
                
                string output = code.decipher(buf);

                //Echo response to console  //uncomment only for troubleshooting:
                //cout << "SERVER> " << output << endl; 
                //before we were using cipher we used string(buf, 0, bytesRecived) as the output

                ss << buf;
                s[timesthrough] = ss.str(); //using for long messages
            }
        }
        if (secondtimethrough != true) {
            secondtimethrough = true;
        }
        else {
            timesthrough++;
        }

    } while (timesthrough == 0); //run through until it has all data

    //Gracefully close down everything
    closesocket(sock);
    WSACleanup();
    code.decipher(buf);
    string statInfo;
    switch (code.getResponseType()){
        case 1:
            //the server has check to see if the username was valid or not.
            return code.getItem(2);
            break;
            //others will be added to setup the usage of other features like pulling data and cteating accounts
        case 2: //user creation
            return s[0];
            break;
        case 3: //logon reutrn from the server
            return code.getItem(2);
            break;
        case 4: //more than one purpose - added the purpose of returning battle attack values and level of player
            return code.getItem(2);
            break;
        case 5: //this is going to be used to get all the items sent from the server
            statInfo = code.getDelimiter();
            statInfo += code.getItem(2);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(3);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(4);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(5);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(6);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(7);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(8);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(9);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(10);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(11);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(12);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(13);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(14);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(15);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(16);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(17);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(18);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(19);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(20);
            statInfo += code.getDelimiter();
            statInfo += code.getItem(21);
            statInfo += code.getDelimiter();
            return statInfo; //returns the deliminated version of the data from server.  This info can then be proccessed by the function decipherS function making us able to call on itemS1 - 6
            //That is is just trying to say call the function decipherS() on sendToServer() so that you can use the output.
            break;
        case 6:{ //whole message return since option 6 selected. - Able to use subDelimination.
            int workingInt = 0;
            if (s[0].length() > 0) {
                //cout << s[0] << endl << endl; //used for testing the large cipher messages
                workingInt = 0;
            } else {
                //cout << s[1] << endl << endl; //used for testing the large cipher messages
                workingInt = 1;
            }
            //system("pause"); //used for testing the large cipher messages
            return s[workingInt]; //return the whole message from the server without editting it.
            break;
        }
        case 0: //Client version validity check
            return code.getItem(2);
            break;

        default:
            return s[0];
    }
}


//# include <winsock.h>
//# include <iostream>
//using namespace std;

string ReachOutToServer::getIPFromHostName(char * hostname) {    
  WSADATA ws;
    int res;
    // Initializing winsock
    // Before using any of the winsock constructs, the library must be initialized by calling the WSAStartup function. 
    res = WSAStartup ( MAKEWORD(2, 2), &ws );
    if ( res != 0 )
  {
        cout << "Failed to initialize winsock : " << res;
        return "failed";
    }
    
    //char * hostname;  
    struct hostent * host_info;
    struct in_addr addr;
    DWORD dw;
    int i = 0;
    
    //hostname = (char *)"codespeedy.com"; // hostname for which we want the IP address
    host_info = gethostbyname ( hostname ); // gethostbyname function retrieves host information.
  // gethostbyname returns a pointer of type struct hostent.
  //A null pointer is returned if an error occurs. The specific error number can be known by calling WSAGetLastError.
  
    if ( host_info == NULL ) 
  {
        dw = WSAGetLastError ();
        if ( dw != 0 )
    {
            if ( dw == WSAHOST_NOT_FOUND )
      {
                cout << "Host is not found";
                return "failed";
            }
      else if ( dw == WSANO_DATA )
      {
                cout << "No data record is found";
                return "failed"; //1
            }
      else
      {
                cout << "Function failed with an error : " << dw;
                return "failed";
            }
        }
    }
  else
  {
        //cout << "Hostname : " << host_info->h_name << endl;
        while ( host_info->h_addr_list[i] != 0 )
    {
            addr.s_addr = *(u_long *) host_info->h_addr_list[i++];
            //cout<<"\nIP Address "<< inet_ntoa(addr); // inet_ntoa function converts IPv4 address to ASCII string in Internet standard dotted-decimal format.
        }
    }
    return inet_ntoa(addr);
}