#include <string>     // std::string, std::stoi
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <sstream>
#include <cstring>

#include "ReachOutToServer.h"
#include "GlobalVariables.h"
#include "Cipher.h"

using namespace std;


string ReachOutToServer::sendToServer(string aMessage) {
    Cipher code; // declare a new Decipher class
    char SERVER_HOSTNAME[] = {"kotaserver.online"}; //updated as of 4/12/2023
    string ipAddress = getIPFromHostName(SERVER_HOSTNAME);
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

void ReachOutToServer::requestFromServer(RequestIDs requestID){
    Cipher code;
    std::string serverData = sendToServer(code.getDelimiterLayer1()+convertRequestIDEnumToString(requestID)+code.getDelimiterLayer1()+player.getUsername()+code.getDelimiterLayer1());
    string token;
    size_t posLayer1 = 0; // position variable for removing the delimiters to view the message
    vector<string> layer1;
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
        //cout << token << endl; //was for troubleshooting to determine the data coming from the server in each layer 1 section
    }
    bool lastLoopWasDIALOGUE_INFO = false;
    bool lastLoopWasSTAT_INFO = false;
    bool lastLoopWasENEMY_INFO= false;
    bool lastLoopWasLOCATION_INFO= false;
    bool lastLoopWasRACE_KIT_WEAPON_INFO= false;
    bool lastLoopWasQUEST_PROGRESS= false;
    bool lastLoopWasINVENTORY_INFO= false;
    bool lastLoopWasABILITY_TYPES_INFO= false;
    bool lastLoopWasLEVEL_XP_INFO= false;
    
    for(int i = 0; i < layer1.size(); i++){
        //also more testing output:
        //cout << "Loop #" << i << endl;
        //cout << "Loop Info: " << layer1.at(i) << endl;
        //complete
        size_t posLayer2DIALOGUE_INFO = 0; // position variable for removing the delimiters to view the message
        vector<string> layer2DIALOGUE_INFO;
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.DIALOGUE_INFO && !lastLoopWasDIALOGUE_INFO){
            lastLoopWasDIALOGUE_INFO = true;
            continue;
        } else if (lastLoopWasDIALOGUE_INFO){

            //then we create all the NPCs with the data from the current deliminations
            bool secondLoopLayer2 = false;
            lastLoopWasDIALOGUE_INFO = false;
            //remove the first delimiter at the start or the layer2DIALOGUE_INFO information:
            if ((posLayer2DIALOGUE_INFO = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2DIALOGUE_INFO + code.getDelimiterLayer2().length());
            //then run through all the other data and add it to the vector: 
            while ((posLayer2DIALOGUE_INFO = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) {
                token = layer1.at(i).substr(0, posLayer2DIALOGUE_INFO);
                layer2DIALOGUE_INFO.emplace_back(token);
                layer1.at(i).erase(0, posLayer2DIALOGUE_INFO + code.getDelimiterLayer2().length());
            }
            string npcName = "";
            string npcMapX = "";
            string npcMapY = "";
            string npcLandmarkX = "";
            string npcLandmarkY = "";
            //cout << "STarting Phase 4 interations:" << endl;
            //cout << "size of layer 2: " << layer2DIALOGUE_INFO.size() << endl;
            //for every chracter recived we run through determining their conversations:
            for(int i2 = 0; i2 < layer2DIALOGUE_INFO.size(); i2++){
                //set name of character since the first iteration will be the name of the character:
                //then increment the current vector position to access the character's location
                npcName = layer2DIALOGUE_INFO.at(i2++);
                
                //set location of character since the second iteration will be the assigned location of the character:
                //then increment the current vector position to access the character's multple missions of serverData
                npcMapX = layer2DIALOGUE_INFO.at(i2++); //mapX
                npcMapY = layer2DIALOGUE_INFO.at(i2++); //mapY
                npcLandmarkX = layer2DIALOGUE_INFO.at(i2++); //landmarkX
                npcLandmarkY = layer2DIALOGUE_INFO.at(i2++); //landmarkY
                
                try{//create the NPCs:
                    string lines = layer2DIALOGUE_INFO.at(i2);
                    //trying to find issue to some error
                    npcs.emplace_back(npcName,stoi(npcMapX),stoi(npcMapY),stoi(npcLandmarkX),stoi(npcLandmarkY),lines);
                }
                catch(invalid_argument){                
                    menu.displayMessageWithPause(0,0,"Critical Failure in ReachOutToServer.cpp -> if (code.convertToDATA_TYPE(layer1.at(i)) == code.DIALOGUE_INFO && !lastLoopWasDIALOGUE_INFO)");
                }
            }
        }
        //complete
        size_t posLayer2STAT_INFO = 0; // position variable for removing the delimiters to view the message
        vector<string> layer2STAT_INFO;
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.STAT_INFO && !lastLoopWasSTAT_INFO){
            lastLoopWasSTAT_INFO = true;
            continue;
        } else if (lastLoopWasSTAT_INFO){
            lastLoopWasSTAT_INFO = false;
            //remove the first delimiter at the start or the layer2 information:
            if ((posLayer2STAT_INFO = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2STAT_INFO + code.getDelimiterLayer2().length());
            
            //then run through all the data and add it to the layer 2 vector: 
            while ((posLayer2STAT_INFO = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) {
                token = layer1.at(i).substr(0, posLayer2STAT_INFO);
                layer2STAT_INFO.emplace_back(token);
                layer1.at(i).erase(0, posLayer2STAT_INFO + code.getDelimiterLayer2().length());
            }
            //new we have the player's stats arranged in order in the vector: health, armor, magicresistance, physicaldamage (min and max), magicdamage (min and max), agility, stealth, NaturalEnergy, mind and, psychicdamage (min and max)

            //Se we can set all the players stats as follows:
            int positionForSTAT_INFO = 0;
            try{
                player.setHealth(stoi(layer2STAT_INFO.at(positionForSTAT_INFO)));
                player.setMaxHealth(stoi(layer2STAT_INFO.at(positionForSTAT_INFO++)));//same as the min health
                player.setArmor(stoi(layer2STAT_INFO.at(positionForSTAT_INFO++)));
                player.setMagicResistance(stoi(layer2STAT_INFO.at(positionForSTAT_INFO++)));
                //find the seperator and pull the values out of it for the min and max:
                string tempPhysicalDamageString = layer2STAT_INFO.at(positionForSTAT_INFO++);
                size_t pos1 = tempPhysicalDamageString.find(code.getDelimiterMinMax());
                player.setPhysicalDamageMin(stoi(tempPhysicalDamageString.substr(0, pos1)));
                tempPhysicalDamageString.erase(0, pos1 + code.getDelimiterMinMax().length());
                player.setPhysicalDamageMax(stoi(tempPhysicalDamageString));
                //find the seperator and pull the values out of it for the min and max:
                string tempMagicDamageString = layer2STAT_INFO.at(positionForSTAT_INFO++);
                pos1 = tempMagicDamageString.find(code.getDelimiterMinMax());
                player.setMagicDamageMin(stoi(tempMagicDamageString.substr(0, pos1)));
                tempMagicDamageString.erase(0, pos1 + code.getDelimiterMinMax().length());
                player.setMagicDamageMax(stoi(tempMagicDamageString));

                player.setAgility(stoi(layer2STAT_INFO.at(positionForSTAT_INFO++)));
                player.setStealth(stoi(layer2STAT_INFO.at(positionForSTAT_INFO++)));
                player.setNaturalEnergy(stoi(layer2STAT_INFO.at(positionForSTAT_INFO++)));
                player.setMind(stoi(layer2STAT_INFO.at(positionForSTAT_INFO)));
                player.setMaxMind(stoi(layer2STAT_INFO.at(positionForSTAT_INFO++)));//same as min mind
                //find the seperator and pull the values out of it for the min and max:
                string tempPsychicDamageString = layer2STAT_INFO.at(positionForSTAT_INFO++);
                pos1 = tempPsychicDamageString.find(code.getDelimiterMinMax());
                player.setPsychicDamageMin(stoi(tempPsychicDamageString.substr(0, pos1)));
                tempPsychicDamageString.erase(0, pos1 + code.getDelimiterMinMax().length());
                player.setPsychicDamageMax(stoi(tempPsychicDamageString));

            }
            catch(invalid_argument){
                menu.displayMessageWithPause(0,0,"Critical Failure in ReachOutToServer.cpp -> if (code.convertToDATA_TYPE(layer1.at(i)) == code.STAT_INFO && !lastLoopWasSTAT_INFO)");
            }
            catch(out_of_range){
                menu.displayMessageWithPause(0,0,"Critical Failure in ReachOutToServer.cpp -> if (code.convertToDATA_TYPE(layer1.at(i)) == code.STAT_INFO && !lastLoopWasSTAT_INFO)");
            }

        }
        //need to determine best way to load dynamic number of enemies:
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.ENEMY_INFO && !lastLoopWasENEMY_INFO){
            lastLoopWasENEMY_INFO = true;
            continue;
        } else if (lastLoopWasENEMY_INFO){
            lastLoopWasENEMY_INFO = false;

        }
        //complete
        size_t posLayer2LOCATION_INFO = 0; // position variable for removing the delimiters to view the message
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.LOCATION_INFO && !lastLoopWasLOCATION_INFO){
            lastLoopWasLOCATION_INFO = true;
            continue;
        } else if (lastLoopWasLOCATION_INFO){
            lastLoopWasLOCATION_INFO = false;
            
            //remove the first delimiter at the start or the layer2 information:
            if ((posLayer2LOCATION_INFO = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2LOCATION_INFO + code.getDelimiterLayer2().length());

            try{
                posLayer2LOCATION_INFO = layer1.at(i).find(code.getDelimiterLayer2());
                token = layer1.at(i).substr(0, posLayer2LOCATION_INFO);
                int x = stoi(token);
                layer1.at(i).erase(0, posLayer2LOCATION_INFO + code.getDelimiterLayer2().length());
                
                posLayer2LOCATION_INFO = layer1.at(i).find(code.getDelimiterLayer2());
                token = layer1.at(i).substr(0, posLayer2LOCATION_INFO);
                int y = stoi(token);
                layer1.at(i).erase(0, posLayer2LOCATION_INFO + code.getDelimiterLayer2().length());

                player.setMapLocation(x,y);
            }
            catch(invalid_argument){
                menu.displayMessageWithPause(0,0,"Critical Failure in ReachOutToServer.cpp -> if (code.convertToDATA_TYPE(layer1.at(i)) == code.LOCATION_INFO && !lastLoopWasLOCATION_INFO)");
            }

        }
        // probably complete
        size_t posLayer2RACE_KIT_WEAPON_INFO = 0; // position variable for removing the delimiters to view the message
        vector<string> layer2RACE_KIT_WEAPON_INFO;
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.RACE_KIT_WEAPON_INFO && !lastLoopWasRACE_KIT_WEAPON_INFO){
            lastLoopWasRACE_KIT_WEAPON_INFO = true;
            continue;
        } else if (lastLoopWasRACE_KIT_WEAPON_INFO){
            lastLoopWasRACE_KIT_WEAPON_INFO = false;
            
            //remove the first delimiter at the start or the layer2RACE_KIT_WEAPON_INFO information:
            if ((posLayer2RACE_KIT_WEAPON_INFO = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2RACE_KIT_WEAPON_INFO + code.getDelimiterLayer2().length());

            //then run through all the data and add it to the layer 2 vector: 
            while ((posLayer2RACE_KIT_WEAPON_INFO = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) {
                token = layer1.at(i).substr(0, posLayer2RACE_KIT_WEAPON_INFO);
                layer2RACE_KIT_WEAPON_INFO.emplace_back(token);
                layer1.at(i).erase(0, posLayer2RACE_KIT_WEAPON_INFO + code.getDelimiterLayer2().length());
            }
            int positionForRACE_KIT_WEAPON_INFO = 0;
            string race = layer2RACE_KIT_WEAPON_INFO.at(positionForRACE_KIT_WEAPON_INFO++);
            string kit = layer2RACE_KIT_WEAPON_INFO.at(positionForRACE_KIT_WEAPON_INFO++);
            string weapon = layer2RACE_KIT_WEAPON_INFO.at(positionForRACE_KIT_WEAPON_INFO++);
            player.setRace(race);
            player.setKit(kit);
            player.setWeapon(weapon);
        }
        //probably complete
        size_t posLayer2QUEST_PROGRESS = 0; // position variable for removing the delimiters to view the message
        vector<string> layer2QUEST_PROGRESS;
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.QUEST_PROGRESS && !lastLoopWasQUEST_PROGRESS){
            lastLoopWasQUEST_PROGRESS = true;
            continue;
        } else if (lastLoopWasQUEST_PROGRESS){
            lastLoopWasQUEST_PROGRESS = false;
            
            //remove the first delimiter at the start or the layer2QUEST_PROGRESS information:
            if ((posLayer2QUEST_PROGRESS = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2QUEST_PROGRESS + code.getDelimiterLayer2().length());

            //then run through all the data and add it to the layer 2 vector: 
            while ((posLayer2QUEST_PROGRESS = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) {
                token = layer1.at(i).substr(0, posLayer2QUEST_PROGRESS);
                layer2QUEST_PROGRESS.emplace_back(token);
                layer1.at(i).erase(0, posLayer2QUEST_PROGRESS + code.getDelimiterLayer2().length());
            }
            //unsigned short indexQUEST_PROGRESS = 0;
            //save to player info:
            try{
                for(int i = 0; i+1 < layer2QUEST_PROGRESS.size(); i++){
                    player.addQuest(stoi(layer2QUEST_PROGRESS.at(i)), stoi(layer2QUEST_PROGRESS.at(++i)), "[NAME]", "DESC...");
                    //player.setQuest1Progress(stoi(layer2QUEST_PROGRESS.at(i)),stoi(layer2QUEST_PROGRESS.at(++i))); //quest number, progress
                }
            } catch(const std::exception & ex){
                cerr << endl << ex.what() << endl;
                system("pause");
            }
            //quest number, progress
        }
        //probably complete
        size_t posLayer2INVENTORY_INFO = 0; // position variable for removing the delimiters to view the message
        vector<string> layer2INVENTORY_INFO;
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.INVENTORY_INFO && !lastLoopWasINVENTORY_INFO){
            lastLoopWasINVENTORY_INFO = true;
            continue;
        } else if (lastLoopWasINVENTORY_INFO){
            lastLoopWasINVENTORY_INFO = false;
            
            //remove the first delimiter at the start or the layer2INVENTORY_INFO information:
            if ((posLayer2INVENTORY_INFO = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2INVENTORY_INFO + code.getDelimiterLayer2().length());

            //then run through all the data and add it to the layer 2 vector: 
            while ((posLayer2INVENTORY_INFO = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) {
                token = layer1.at(i).substr(0, posLayer2INVENTORY_INFO);
                layer2INVENTORY_INFO.emplace_back(token);
                layer1.at(i).erase(0, posLayer2INVENTORY_INFO + code.getDelimiterLayer2().length());
            }
            unsigned short indexINVENTORY_INFO = 0;
            //save to player info:
            for (int index = 0; index < layer2INVENTORY_INFO.size(); index++ ){
                //adds every weapon to the inventory in the order in which they were stored in the file
                player.setInventory(index,stoi(layer2INVENTORY_INFO.at(index)));
            }

        }
        //probably complete
        size_t posLayer2ABILITY_TYPES_INFO = 0; // position variable for removing the delimiters to view the message
        vector<string> layer2ABILITY_TYPES_INFO;
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.ABILITY_TYPES_INFO && !lastLoopWasABILITY_TYPES_INFO){
            lastLoopWasABILITY_TYPES_INFO = true;
            continue;
        } else if (lastLoopWasABILITY_TYPES_INFO){
            lastLoopWasABILITY_TYPES_INFO = false;
            
            //remove the first delimiter at the start or the layer2ABILITY_TYPES_INFO information:
            if ((posLayer2ABILITY_TYPES_INFO = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2ABILITY_TYPES_INFO + code.getDelimiterLayer2().length());

            //then run through all the data and add it to the layer 2 vector: 
            while ((posLayer2ABILITY_TYPES_INFO = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) {
                token = layer1.at(i).substr(0, posLayer2ABILITY_TYPES_INFO);
                layer2ABILITY_TYPES_INFO.emplace_back(token);
                layer1.at(i).erase(0, posLayer2ABILITY_TYPES_INFO + code.getDelimiterLayer2().length());
            }
            unsigned short indexABILITY_TYPES_INFO = 0;
            //save to player info:
            player.setQDamageType(layer2ABILITY_TYPES_INFO.at(indexABILITY_TYPES_INFO++));
            player.setWDamageType(layer2ABILITY_TYPES_INFO.at(indexABILITY_TYPES_INFO++));
            player.setEDamageType(layer2ABILITY_TYPES_INFO.at(indexABILITY_TYPES_INFO++));
            player.setRDamageType(layer2ABILITY_TYPES_INFO.at(indexABILITY_TYPES_INFO++));
        }
        //probably complete
        //first level, then current xp, then xp till next level
        size_t posLayer2LEVEL_XP_INFO = 0; // position variable for removing the delimiters to view the message
        vector<string> layer2LEVEL_XP_INFO;
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.LEVEL_XP_INFO && !lastLoopWasLEVEL_XP_INFO){
            lastLoopWasLEVEL_XP_INFO = true;
            continue;
        } else if (lastLoopWasLEVEL_XP_INFO){
            lastLoopWasLEVEL_XP_INFO = false;
            
            //remove the first delimiter at the start or the layer2LEVEL_XP_INFO information:
            if ((posLayer2LEVEL_XP_INFO = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2LEVEL_XP_INFO + code.getDelimiterLayer2().length());

            //then run through all the data and add it to the layer 2 vector: 
            while ((posLayer2LEVEL_XP_INFO = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) {
                token = layer1.at(i).substr(0, posLayer2LEVEL_XP_INFO);
                layer2LEVEL_XP_INFO.emplace_back(token);
                layer1.at(i).erase(0, posLayer2LEVEL_XP_INFO + code.getDelimiterLayer2().length());
            }
            unsigned short indexLEVEL_XP_INFO = 0;
            //save to player info:
            player.setLevel(stoi(layer2LEVEL_XP_INFO.at(indexLEVEL_XP_INFO++)));
            player.setCurrentXP(stoi(layer2LEVEL_XP_INFO.at(indexLEVEL_XP_INFO++)));
            player.setXPForNextLevel(stoi(layer2LEVEL_XP_INFO.at(indexLEVEL_XP_INFO++)));

        }
    }
    //output all NPC data for testing:
    //cout << "NPCS size: " << npcs.size() << endl;
    //npcs.at(0).getAllDialogue();
}

string ReachOutToServer::convertRequestIDEnumToString(RequestIDs id){
    return to_string(id);
}