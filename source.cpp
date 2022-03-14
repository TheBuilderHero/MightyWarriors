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


//this function is intended to pull out the delimiters from a message and the data associated with each request
string decipher(char messageFromClient[]){
    string delimiter = "~"; //a character that marks the beginning or end of a unit of data
    string message = messageFromClient; // change the message into a string

    string item1, item2, item3, item4, item5, item6, item7; // declare the variables that are being used to store the message from the client
    // the above variables may later be replaced with a more wide veriety of variables however, for testing we are using all strings
    string s = messageFromClient;
    string str_file_content;
    string token, output;
    int loopPass = 0;
    size_t pos = 0; // position variable for removing the delimiters to view the message
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        output = token;
        str_file_content += std::string(token); // we do not need to add spaces between the information for now so I removed: + std::string(" ")
        s.erase(0, pos + delimiter.length());
        if (loopPass == 1) {
            //first item after delimiter
            if (output.length() > 0) item1 = output; // we many need to change the variable to an int with stoi(output) later but right now we just want a string version
        } else if (loopPass == 2) {
            //second item after delimiter
            if (output.length() > 0) item2 = output;
        } else if (loopPass == 3) {
            //third item after delimiter
            if (output.length() > 0) item3 = output;
        } else if (loopPass == 4) {
            //forth item after delimiter
            if (output.length() > 0) item4 = output;
        } else if (loopPass == 5) {
            //fith item after delimiter
            if (output.length() > 0) item5 = output;
        } else if (loopPass == 6) {
            //sixth item after delimiter
            if (output.length() > 0) item6 = output;
        } else if (loopPass == 7) {
            //seventh item after delimiter
            if (output.length() > 0) item7 = output;
        }
        loopPass++;
    }
    return str_file_content;
}

//this functions purpose it to add the delimiters to given items 
string cipher(string item1 = "", string item2= "", string item3= "", string item4= "", string item5= "", string item6= "", string item7= ""){ // the default values have been set to "" in case no input is given
    int numberOfItems = 7; //max number of items that we can cipher
    string delimiter = "~"; //a character that marks the beginning or end of a unit of data

    string str_file_content;
    int loopPass = 1; // start the loop at 1 so that there is no extra spaces
    while (loopPass != numberOfItems) {
        str_file_content += delimiter; // this will add the seperating delimiter before the a given item
        if (loopPass == 1) {
            //first item after delimiter
            if (item1.length() > 0) str_file_content += item1;
        } else if (loopPass == 2) {
            //second item after delimiter
            if (item2.length() > 0) str_file_content += item2;
        } else if (loopPass == 3) {
            //third item after delimiter
            if (item3.length() > 0) str_file_content += item3;
        } else if (loopPass == 4) {
            //second item after delimiter
            if (item2.length() > 0) str_file_content += item4;
        } else if (loopPass == 5) {
            //third item after delimiter
            if (item3.length() > 0) str_file_content += item5;
        } else if (loopPass == 6) {
            //second item after delimiter
            if (item2.length() > 0) str_file_content += item6;
        } else if (loopPass == 7) {
            //third item after delimiter
            if (item3.length() > 0) str_file_content += item7;
        }
        str_file_content += delimiter; // this will add the seperating delimiter after the given item
        loopPass++;
    }
    return str_file_content;
}

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
        message = cipher(message); // we are going to need a decision tree put in place to determine what data is being sent and thus what item slot to send it within.
        //for now we are just going to use the above to test.

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

                    string output = decipher(buf);

                    //Echo response to console  //uncomment only for troubleshooting:
                     
                    cout << "SERVER> " << output << endl; // before we were using cipher we used string(buf, 0, bytesRecived) as the output

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
    //test commit comment
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