#include <string.h>

#include "Main.h"
#include "ReachOutToServer.h"
#include "Account.h"
#include "Cipher.h"
#include "Menu.h"
#include "Battle.h"
#include "DataGuard.h"

#include "NPCData/NPC.h"
#include <vector>

using namespace std;

//global variable declarations:
Menu menu;
Map map;
DataGuard guard;
Interactions interactions;
std::vector<NPC> npcs;
static int currentID = 0;
 
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
            menu.ClearConsoleInputBuffer();
            //pull interaction data:
            interactions.pullInteractionsAndNPCs(); //get all npc dialogue from the server
            //present the logon screen:
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

void Main::setupConsole(){
    maxsc();
    //fullsc();
    setTextSize(8);
    CONSOLE_SCREEN_BUFFER_INFOEX consolesize;

	consolesize.cbSize=sizeof(consolesize);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfoEx(hConsole,&consolesize);

	COORD c;
	c.X = 237;
	c.Y = 120;
	consolesize.dwSize = c;

	consolesize.srWindow.Left = 0;
	consolesize.srWindow.Right = 237;
	consolesize.srWindow.Top = 0;
	consolesize.srWindow.Bottom = 120;

	SetConsoleScreenBufferInfoEx(hConsole, &consolesize);
}

void Main::setTextSize(int size){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = size;  //8                 // Width of each character in the font
    cfi.dwFontSize.Y = 2*size; //16                 // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void Main::preLoadGameTest(){
    ReachOutToServer server;
    Cipher code;
    cout << "message:" << endl;
    string info = server.sendToServer("~27~");
    cout << info << endl;
    system("pause");
}

void Main::maxsc()
{
    HWND Hwnd = GetForegroundWindow();
    ShowWindow(Hwnd, SW_MAXIMIZE);
}
void Main::fullsc()
{
    HWND Hwnd = GetForegroundWindow();
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    LONG winstyle = GetWindowLong(Hwnd, GWL_STYLE);
    SetWindowLong(Hwnd, GWL_STYLE, (winstyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
    SetWindowPos(Hwnd,HWND_TOP,0,0,x,y,0);

}

unsigned int setUIDForNPC(){
    return currentID++;
}

unsigned int getLastAssignedUIDForNPC(){
    return currentID-1;
}