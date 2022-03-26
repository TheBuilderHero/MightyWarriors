#include <iostream>
#include <string>

#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Account.h"
#include "Menu.h"

Menu menu;
//Change the version number in the menu.h header file.
//********************************************
const int gameVersion     = menu.gameVersion;
const int gameMajorBuild  = menu.gameMajorBuild;
const int gameMinorBuild  = menu.gameMinorBuild;
const int gamePatch       = menu.gamePatch;
//********************************************

using namespace std; //so I dont have to type "std::"

int main(){ //Starts the program if the clients version is compatable with the server's version
    string answer;
    ReachOutToServer server; //declare a new instance of ReachOutToServer called server
    Account account; //declare a new instance of the Account class
    Cipher code;
    double attempts = 0;
    while (!(answer == "n" || answer == "N")) { //This do while loop is intended to get them connected to the server.  If it fails it will prompt the user Y/N to retry connecting.
        system("cls");
        //answer = ""; // set the answer variable to some other value on the start of each loop.
        string serverVersionResponse = server.sendToServer(code.cipher("0", "", to_string(gameVersion), to_string(gameMajorBuild), to_string(gameMinorBuild), to_string(gamePatch)));//check to see if the version the client is running is allowed to continue - the reponse is stored in "serverVersionResponse"
        //Before doing anything else... request required client version from server.
        if (serverVersionResponse == "true"){ //if it is true then the program will start
            //This is the start of the program
            account.newOrExistingAccout(); //ask whether the user has an account or not
        } else if (serverVersionResponse == "FailedConnect") { //If the client is unable to connect to the server inform the client
            cout << "The Server is currently Offline for either maintanance or other reasons..." << endl << "Would you like to try connecting again? (Y/N) [Attempt: " << attempts << "]\n>";
            cin >> answer;
            while (!(answer == "n" || answer == "N" || answer == "y" || answer == "Y")) { 
                cout << endl << answer << endl;
                //answer = 'A';// set the answer variable to some other value on the start of each loop.
                cout << "Your input was not recognized." << endl << "Would you like to try connecting again? (Y/N) [Attempt: " << attempts << "]\n>";
                cin >> answer;
                
            }
        } else{//if version check fails we inform user and close the client because their current version is not acceptable on the server side.
            cout << "You are not running the needed version. Please update to the latest version and try again." << endl;
            system("pause");
        }
        attempts++;
    } //; //while the user has not selected to stop trying to connect loop
    return 0;
}