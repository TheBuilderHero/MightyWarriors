#include <iostream>
#include <string>

#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Account.h"

//********************************************
const int gameVersion     = 1;
const int gameMajorBuild  = 0;
const int gameMinorBuild  = 0;
const int gamePatch       = 0;
//********************************************

using namespace std; //so I dont have to type "std::"

int main(){
    ReachOutToServer server; //declare a new instance of ReachOutToServer called server
    Account account; //declare a new instance of the Account class
    Cipher code;
    string serverVersionResponse = server.sendToServer(code.cipher("0", "", to_string(gameVersion), to_string(gameMajorBuild), to_string(gameMinorBuild), to_string(gamePatch)));//check to see if the version the client is running is allowed to continue - the reponse is stored in "serverVersionResponse"
    //Before doing anything else... request required client version from server.
    if (serverVersionResponse == "true"){ //if it is true then the program will start
        //This is the start of the program
        account.newOrExistingAccout(); //ask whether the user has an account or not
    } else if (serverVersionResponse == "FailedConnect") { //If the client is unable to connect to the server inform the client
        cout << "The Server is currently Offline for either maintanance or other reasons..." << endl << "Please try again later..." << endl;
        system("pause");
    } else{//if version check fails we inform user and close the client
        cout << "You are not running the needed version. Please update to the latest version and try again." << endl;
        system("pause");
    }
    
    return 0;
}