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


//Probably will need to add this later if cin starts acting up
/*
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
*/

#undef min // these are needed for the cin.ignore statments to clear out the buffer for new data.
#undef max 

//to be able to use sockets
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "advapi32")

using namespace std;
string delimiter = "~"; //a character that marks the beginning or end of a unit of data


class Decipher {
    public:
    int responseType;
    string item2, item3, item4, item5, item6, item7; // declare the variables that are being used to store the message from the client

    //this function is intended to pull out the delimiters from a message and the data associated with each request
    string decipher(char messageFromClient[]){
        
        string message = messageFromClient; // change the message into a string

        
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
            switch (loopPass){
                case 1://the first item enclosed in delimiters
                if (output.length() > 0) responseType = stoi(output); // we many need to change the variable to an int with stoi(output) later but right now we just want a string version
                break;
                case 2://the second item enclosed in delimiters
                if (output.length() > 0) item2 = output; 
                break;
                case 3://the third item enclosed in delimiters
                if (output.length() > 0) item3 = output; 
                break;
                case 4://the forth item enclosed in delimiters
                if (output.length() > 0) item4 = output; 
                break;
                case 5://the fith item enclosed in delimiters
                if (output.length() > 0) item5 = output; 
                break;
                case 6://the sixth item enclosed in delimiters
                if (output.length() > 0) item6 = output; 
                break;
                case 7://the seventh item enclosed in delimiters
                if (output.length() > 0) item7 = output; 
                break;
            }
            loopPass++;
        }
        return str_file_content;
    }
};

//this functions purpose it to add the delimiters to given items 
string cipher(int typeOfRequest = 0, string username= "", string item3= "", string item4= "", string item5= "", string item6= "", string item7= ""){ // the default values have been set to "" in case no input is given
    int numberOfItems = 7; //max number of items that we can cipher
    string delimiter = "~"; //a character that marks the beginning or end of a unit of data

    string str_file_content;
    int loopPass = 1; // start the loop at 1 so that there is no extra spaces
    while (loopPass != numberOfItems) {
        str_file_content += delimiter; // this will add the seperating delimiter before the a given item
        switch (loopPass){
            case 1:
            if (typeOfRequest > 0) str_file_content += to_string(typeOfRequest);
            break;
            case 2:
            if (username.length() > 0) str_file_content += username;
            break;
            case 3:
            if (item3.length() > 0) str_file_content += item3;
            break;
            case 4:
            if (item4.length() > 0) str_file_content += item4;
            break;
            case 5:
            if (item5.length() > 0) str_file_content += item5;
            break;
            case 6:
            if (item6.length() > 0) str_file_content += item6;
            break;
            case 7:
            if (item7.length() > 0) str_file_content += item7;
            break;
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
        Decipher decode; // declare a new Decipher class
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
                    
                    //decipher the message from the server
                    
                    string output = decode.decipher(buf);

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
        switch (decode.responseType){
            case 1:
            //the server has check to see if the username was valid or not.
            return to_string(decode.responseType);
            break;
            //others will be added to setup the usage of other features like pulling data and cteating accounts

            default:
            return s;
        }
    }

};

void logonScreen(){
    cout << "You are at the logon screen" << endl;
}

void createNewAccount(){
    int valid; // is the username valid or not (1 meaning the username is valid, 0 meaning the username is taken)
    //declare server object to use sendserver function to check if server has someone by this username
    ReachOutToServer server;
    //ask user for the username they would like to use
    string username;
    cout << "What would you like your new account username to be?" << endl << "Please type a valid username: ";
    cin >> username;

    //check to make sure the username is valid and not already taken
    if (username.find(delimiter) >= 0) {
        system("cls");
        cout << "The username is not valid Please enter a different username." << endl;
        system("pause");
        createNewAccount();
    } else {
        cout << endl << endl << "The value is: " << username.find(delimiter);
        system("pause");
        valid = stoi(server.sendToServer(cipher(1, username))); // the response for this will either be 1 or 0 as a string (1 meaning the username is valid, 0 meaning the username is taken)
        switch (valid){
            case 0:
            //the username is invalid so restart the process
            cout << "The username is not valid Please enter a different username." << endl;
            break;
            case 1:
            //username is valid
            string createAccoutnCheck;
            cout << "The username is valid and you can use it as your username." << endl << "Would you like to continue and create an account with this username? (yes or no)" << endl << "> ";
            cin >> createAccoutnCheck;
            if(createAccoutnCheck == "yes"){
                cout << "We will now create the account";
            } else {
                cout << "Input not recognized." << endl;
                system("pause");
                createNewAccount();
            }
            break;
        }
    }
}

void newOrExistingAccout(){ // asks and runs through everything for new accounts and if existing brings the user to the logon screen.
    //ask the user if they have an account with MightyWarrior game
    string answer;
    cout << "Do you have an accout yet? (yes or no)" << endl;
    cin >> answer;
    
    //if yes bring them to the logon screen
    if(answer == "yes"){
        system("cls");
        cout << "You have an acount" << endl << "We will now take you to the logon screen." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        system("pause");//pause the window so the user can read the message, then they can press any key to continue.
        logonScreen();
    } else if (answer == "no") {//if no start the signup prossess
        system("cls");
        cout << "You do not have an account" << endl << "Lets start the procss of creating a new account." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        system("pause");//pause the window so the user can read the message, then they can press any key to continue.
        createNewAccount(); // take user to the function for creatiing accounts 
    } else {
        cout << "Your answer was not yes or no." << endl << "Please try again." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear out cin buffer
        system("pause");//pause the window so the user can read the message, then they can press any key to continue.
        newOrExistingAccout(); // take user to beguining of this function again
    }

}

int main(){

    //ask whether the user has an account or not
    newOrExistingAccout();
    return 0;
}