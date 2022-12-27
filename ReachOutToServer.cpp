#include <string>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <sstream>
#include <cstring>

#include "ReachOutToServer.h"
#include "globalVariables.h"
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
            ZeroMemory(buf, 8192);  //doubled from 4096
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
            statInfo = code.getDelimiterLayer1();
            statInfo += code.getItem(2);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(3);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(4);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(5);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(6);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(7);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(8);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(9);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(10);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(11);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(12);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(13);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(14);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(15);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(16);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(17);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(18);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(19);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(20);
            statInfo += code.getDelimiterLayer1();
            statInfo += code.getItem(21);
            statInfo += code.getDelimiterLayer1();
            return statInfo; //returns the deliminated version of the data from server.  This info can then be proccessed by the function decipherS function making us able to call on itemS1 - 6
            //That is is just trying to say call the function decipherS() on sendToServer() so that you can use the output.
            break;
        case 6:{ //whole message return since option 6 selected. - Able to use subDelimination. //can be used for endless vector delimination:
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
        case 7:{
            string fullMessage;
            fullMessage = ss.str();
            return fullMessage;
            break;
        }
        case 0: //Client version validity check
            return code.getItem(2);
            break;

        default:
            return s[0];
    }
}

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

void ReachOutToServer::requestFromServer(string requestID){
    Cipher code;
    std::string serverData = sendToServer("~"+requestID+"~");
    string token;
    size_t posLayer1 = 0; // position variable for removing the delimiters to view the message
    size_t posLayer2 = 0; // position variable for removing the delimiters to view the message
    vector<string> layer1;
    vector<string> layer2;
    //cout << "STarting Phase 1 interations:" << endl;
    //remove the server send value first before processing the rest of the data:
    posLayer1 = serverData.find(code.getDelimiterLayer1());
    serverData.erase(0, posLayer1 + code.getDelimiterLayer1().length());
    posLayer1 = serverData.find(code.getDelimiterLayer1());
    serverData.erase(0, posLayer1 + code.getDelimiterLayer1().length());
    //Put all the rest of the data in layer1 vector:
    while ((posLayer1 = serverData.find(code.getDelimiterLayer1())) != std::string::npos) {
        token = serverData.substr(0, posLayer1);
        layer1.emplace_back(token);
        serverData.erase(0, posLayer1 + code.getDelimiterLayer1().length());
    }
    bool lastLoopWasDIALOGUE_INFO = false;
    bool lastLoopWasENEMY_INFO= false;
    bool lastLoopWasSTAT_INFO = false;
    //cout << "STarting Phase 2 interations:" << endl;
    //run through the lower layers and convert them into the needed formats and places
    //cout << "layer 1 size: " << layer1.size() << endl;
    for(int i = 0; i < layer1.size(); i++){
        //cout << "STarting Phase 3 interations:" << endl;
        //cout << "current layer 1: " << layer1.at(i) << endl;
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.DIALOGUE_INFO && !lastLoopWasDIALOGUE_INFO){
            //cout << "STarting Phase if interations:" << endl;

            lastLoopWasDIALOGUE_INFO = true;
            continue;
        } else if (lastLoopWasDIALOGUE_INFO){
            //cout << "STarting Phase else interations:" << endl;

            //then we create all the NPCs with the data from the current deliminations
            bool secondLoopLayer2 = false;
            lastLoopWasDIALOGUE_INFO = false;
            //remove the first delimiter at the start or the later2 information:
            if ((posLayer2 = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2 + code.getDelimiterLayer2().length());
            //then run through all the other data and add it to the vector: 
            while ((posLayer2 = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) {
                token = layer1.at(i).substr(0, posLayer2);
                layer2.emplace_back(token);
                layer1.at(i).erase(0, posLayer2 + code.getDelimiterLayer2().length());
            }
            string npcName = "";
            string npcLocation = "";
            //cout << "STarting Phase 4 interations:" << endl;
            //cout << "size of layer 2: " << layer2.size() << endl;
            //for every chracter recived we run through determining their conversations:
            for(int i2 = 0; i2 < layer2.size(); i2++){
                //set name of character since the first iteration will be the name of the character:
                //then increment the current vector position to access the character's location
                npcName = layer2.at(i2++);
                
                //set location of character since the second iteration will be the assigned location of the character:
                //then increment the current vector position to access the character's multple missions of serverData
                npcLocation = layer2.at(i2++);
                
                try{//create the NPCs:
                    string lines = layer2.at(i2);
                    npcs.emplace_back(npcName,stoi(npcLocation),lines);
                }
                catch(invalid_argument){
                    cout << "Critical Failure in \"Interactions::Interactions()\" -> npcs.emplace_back(npcName,stoi(npcLocation),layer2.at(i2));" << endl;
                    system("pause");
                }
            }
        }
        //cout << "End interations:" << endl;


        //maybe we could use this for other things and have it make decisions based on that info:
        /*
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.ENEMY_INFO);
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.STAT_INFO);
        */
    }
    //output all NPC data for testing:
    //cout << "NPCS size: " << npcs.size() << endl;
    npcs.at(0).getAllDialogue();
}