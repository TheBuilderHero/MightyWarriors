#include <string.h>

#include "Main.h"
#include "ReachOutToServer.h"
#include "Account.h"
#include "Cipher.h"
#include "Menu.h"
#include "Battle.h"
#include "DataGuard.h"

using namespace std;

//global variable declarations:
Menu menu;
DataGuard guard;
Interactions interactions;
 
void Main::attemptStartGame(){
    string answer;
    ReachOutToServer server; //declare a new instance of ReachOutToServer called server
    Account account; //declare a new instance of the Account class
    Cipher code;
    double attempts = 0;
    while (!(answer == "n" || answer == "N")) { //This do while loop is intended to get them connected to the server.  If it fails it will prompt the user Y/N to retry connecting.
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        //answer = ""; // set the answer variable to some other value on the start of each loop.
        string runningCurrentVersion = server.sendToServer(code.cipher("0", "", to_string(gameVersion), to_string(gameMajorBuild), to_string(gameMinorBuild), to_string(gamePatch)));//check to see if the version the client is running is allowed to continue - the reponse is stored in "runningCurrentVersion"
        //Before doing anything else... request required client version from server.
        //runningCurrentVersion = "true"; //for testing hard set true
        if (runningCurrentVersion == "true"){ //if we are running the current version then the program will start
            //this was causing an issues with pausing the logon screen from apearing//menu.ClearConsoleInputBuffer();//clear keyboard input from the yesNo prompt - this seems to remove the keyboard input
            //This is the start of the program
            account.logonScreen(); //ask whether the user has an account or not
        } else if (runningCurrentVersion == "FailedConnect") { //If the client is unable to connect to the server inform the client
            cout << "The Server is currently Offline for either maintanance or other reasons..." << endl << "Would you like to try connecting again? (Y/N) [Attempt: " << attempts << "]\n>";
            answer = menu.yesOrNo();
            while (!(answer == "n" || answer == "N" || answer == "y" || answer == "Y")) { 
                //cout << endl << answer << endl;
                //answer = 'A';// set the answer variable to some other value on the start of each loop.
                cout << "Your input was not recognized." << endl << "Would you like to try connecting again? (Y/N) [Attempt: " << attempts << "]";
                answer = menu.yesOrNo();
            }
        } else{//if version check fails we inform user and close the client because their current version is not acceptable on the server side.
            cout << "You are not running the needed version. Please update to the latest version and try again." << endl;
            system("pause");
        }
        attempts++;
    } //; //while the user has not selected to stop trying to connect loop
}