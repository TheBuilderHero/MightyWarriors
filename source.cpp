#include <iostream>
#include <string>

#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Account.h"
#include "Menu.h"
#include "Battle.h"

Menu menu;
//Change the version number in the menu.h header file.
//********************************************
const int gameVersion     = menu.gameVersion;
const int gameMajorBuild  = menu.gameMajorBuild;
const int gameMinorBuild  = menu.gameMinorBuild;
const int gamePatch       = menu.gamePatch;
//********************************************

using namespace std; //so I dont have to type "std::"

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
        // Handle the CTRL-C signal.
    case CTRL_C_EVENT:
        printf("Ctrl-C event\n\n");
        Beep(750, 300);
        return TRUE;

        // CTRL-CLOSE: confirm that the user wants to exit.
    case CTRL_CLOSE_EVENT:
        Beep(600, 200);
        printf("Ctrl-Close event\n\n");
        return TRUE;

        // Pass other signals to the next handler.
    case CTRL_BREAK_EVENT:
        Beep(900, 200);
        printf("Ctrl-Break event\n\n");
        return FALSE;

    case CTRL_LOGOFF_EVENT:
        Beep(1000, 200);
        printf("Ctrl-Logoff event\n\n");
        return FALSE;

    case CTRL_SHUTDOWN_EVENT:
        Beep(750, 500);
        printf("Ctrl-Shutdown event\n\n");
        return FALSE;

    default:
        return FALSE;
    }
}

int main(){ //Starts the program if the clients version is compatable with the server's versions

    //This is another test of apllication closing ability with saving user data:
    /*if (SetConsoleCtrlHandler(CtrlHandler, TRUE)) //controls exit
    {
        printf("\nThe Control Handler is installed.\n");
        printf("\n -- Now try pressing Ctrl+C or Ctrl+Break, or");
        printf("\n    try logging off or closing the console...\n");
        printf("\n(...waiting in a loop for events...)\n\n");

        while (1) {}
    }
    else
    {
        printf("\nERROR: Could not set control handler");
        return 1;
    }*/


    string answer;
    ReachOutToServer server; //declare a new instance of ReachOutToServer called server
    Account account; //declare a new instance of the Account class
    Cipher code;
    double attempts = 0;
    while (!(answer == "n" || answer == "N")) { //This do while loop is intended to get them connected to the server.  If it fails it will prompt the user Y/N to retry connecting.
        system("cls");
        //answer = ""; // set the answer variable to some other value on the start of each loop.
        string runningCurrentVersion = server.sendToServer(/*"31" + */code.cipher("0", "", to_string(gameVersion), to_string(gameMajorBuild), to_string(gameMinorBuild), to_string(gamePatch)));//check to see if the version the client is running is allowed to continue - the reponse is stored in "runningCurrentVersion"
        //Before doing anything else... request required client version from server.
        if (runningCurrentVersion == "true"){ //if we are running the current version then the program will start
            menu.ClearConsoleInputBuffer();//clear keyboard input from the yesNo prompt - this seems to remove the keyboard input
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
    return 0;
}