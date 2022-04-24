#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdio.h>

#include "Account.h"
#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Menu.h"
#include "Battle.h"

#undef min // these are needed for the cin.ignore statments to clear out the buffer for new data.
#undef max 

using namespace std;
Cipher code; //declare the new instance of Cipher class
Account account;
Battle battle;

void Menu::ClearConsoleInputBuffer()
{
    PINPUT_RECORD ClearingVar1 = new INPUT_RECORD[256];
    DWORD ClearingVar2;
    ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE),ClearingVar1,256,&ClearingVar2);
    delete[] ClearingVar1;
}

void Menu::getGameVersion(){
    cout << "Client Version: " << to_string(gameVersion) << "." << to_string(gameMajorBuild) << "." << to_string(gameMinorBuild) << "." << to_string(gamePatch) << endl;
    system("pause");
}

void Menu::menu(string username){ //bring up the menu for the passing in the username
    system("cls");
    bool oneKeyPressedLastLoop = false, twoKeyPressedLastLoop = false, threeKeyPressedLastLoop = false, fourKeyPressedLastLoop = false, fiveKeyPressedLastLoop = false, 
    zeroKeyPressedLastLoop = false, nKeyPressedLastLoop = false, iKeyPressedLastLoop = false, aKeyPressedLastLoop = false, controlKeyPressedLastLoop = false, 
    altKeyPressedLastLoop = false ,kKeyPressedLastLoop = false;
    int value;
    cout << setfill(' ') << setw(61) << "Menu of options:" << 
    endl << setfill(' ') << setw(48) << "Change Password" << setfill(' ') << setw(25) << "(type number \"1\")" << endl;
    cout << setfill(' ') << setw(39) << "Logout" << setfill(' ') << setw(34) <<"(type number \"2\")" << endl;
    cout << setfill(' ') << setw(38) << "Stats" << setfill(' ') << setw(35) <<"(type number \"3\")" << endl;
    cout << setfill(' ') << setw(37) << "Info" << setfill(' ') << setw(36) <<"(type number \"4\")" << endl;
    cout << setfill(' ') << setw(39) << "Battle" << setfill(' ') << setw(34) <<"(type number \"5\")" << endl;
    cout << setfill(' ') << setw(37) << "Exit" << setfill(' ') << setw(36) <<"(type number \"0\")" << endl;// << setfill(' ') << setw(35) << "> ";
    while (1){
        if (GetKeyState('1') < 0 && !oneKeyPressedLastLoop) { //checks to make sure that the 1 key is pressed and makes sure it was not pressed last check
            oneKeyPressedLastLoop = true;
            value = 1;
            break;
        } else if (GetKeyState('1') >= 0){ // else 1 not pressed
            oneKeyPressedLastLoop = false;
        }
        if (GetKeyState('2') < 0 && !twoKeyPressedLastLoop) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
            twoKeyPressedLastLoop = true;
            value = 2;
            break;
        } else if (GetKeyState('2') >= 0){ // else 1 not pressed
            twoKeyPressedLastLoop = false;
        }
        if (GetKeyState('3') < 0 && !threeKeyPressedLastLoop) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
            threeKeyPressedLastLoop = true;
            value = 3;
            break;
        } else if (GetKeyState('3') >= 0){ // else 1 not pressed
            threeKeyPressedLastLoop = false;
        }
        if (GetKeyState('4') < 0 && !fourKeyPressedLastLoop) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
            fourKeyPressedLastLoop = true;
            value = 4;
            break;
        } else if (GetKeyState('4') >= 0){ // else 1 not pressed
            fourKeyPressedLastLoop = false;
        }
        if (GetKeyState('5') < 0 && !fiveKeyPressedLastLoop) { //checks to make sure that the 3 key is pressed and makes sure it was not pressed last check
            fiveKeyPressedLastLoop = true;
            value = 5;
            break;
        } else if (GetKeyState('Q') >= 0){ // else 1 not pressed
            fiveKeyPressedLastLoop = false;
        }
        if (GetKeyState('0') < 0 && !zeroKeyPressedLastLoop) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
            zeroKeyPressedLastLoop = true;
            value = 0;
            break;
        } else if (GetKeyState('0') >= 0){ // else 1 not pressed
            zeroKeyPressedLastLoop = false;
        }

        //hidden features:
        if (GetKeyState('N') < 0 && GetKeyState('I') < 0 && GetKeyState('A') < 0) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
            nKeyPressedLastLoop = true;
            iKeyPressedLastLoop = true;
            aKeyPressedLastLoop = true;
            value = 14;
            break;
        } else if (GetKeyState('N') >= 0 || GetKeyState('I') >= 0 || GetKeyState('A') >= 0){ // else 1 not pressed
            nKeyPressedLastLoop = false;
            iKeyPressedLastLoop = false;
            aKeyPressedLastLoop = false;
        }
        //admin menu:
        if (GetKeyState(VK_CONTROL) < 0 && GetKeyState(VK_MENU) < 0 && GetKeyState('K') < 0) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
            controlKeyPressedLastLoop = true;
            altKeyPressedLastLoop = true;
            kKeyPressedLastLoop = true;
            value = 15;
            break;
        } else if (GetKeyState(VK_CONTROL) >= 0 || GetKeyState(VK_MENU) >= 0 || GetKeyState('K') >= 0){ // else 1 not pressed
            controlKeyPressedLastLoop = false;
            altKeyPressedLastLoop = false;
            kKeyPressedLastLoop = false;
        }
    }
    switch (value)
    {
    case 0:
        exit(1);
        break;
    case 1: //change password
        //change password
        system("cls");
        ClearConsoleInputBuffer();
        account.logonScreen(2);
        break;
    case 2://logout
        system("cls");
        ClearConsoleInputBuffer();
        account.logonScreen();
        break;
    case 3://display stats
        system("cls");
        ClearConsoleInputBuffer();
        account.displayStats(username);
        menu(username);
        break;
    case 4://display version and info
        system("cls");
        ClearConsoleInputBuffer();
        getGameVersion();
        menu(username);
        break;
    case 5: //start battle
        system("cls");
        ClearConsoleInputBuffer();
        battle.startBattle(username);//start battle code will go here.
        break;
    case 14:
        system("cls");
        ClearConsoleInputBuffer();
        cout << "October is a Beautiful month to get Married!" << endl;
        cout << "Dakota loves Beautiful!" << endl;
        system("pause");
        menu(username);
        break;
    case 15:
        system("cls");
        ClearConsoleInputBuffer();
        adminMenu(username);
        break;
    default:
        system("cls");
        ClearConsoleInputBuffer();
        cout << "Invalid input, Please try again..." << endl;
        system("pause");
        menu(username);
        break;
    }
}

void Menu::adminMenu (string username){ //The admin menu that will have more advanced options later
    ReachOutToServer server;
    string usernameE;
    system("cls");
    int value;
    bool oneKeyPressedLastLoop = false, twoKeyPressedLastLoop = false, threeKeyPressedLastLoop = false, fourKeyPressedLastLoop = false, fiveKeyPressedLastLoop = false, 
    zeroKeyPressedLastLoop = false, nKeyPressedLastLoop = false, iKeyPressedLastLoop = false, aKeyPressedLastLoop = false, controlKeyPressedLastLoop = false, 
    altKeyPressedLastLoop = false ,kKeyPressedLastLoop = false;
    cout << setfill(' ') << setw(65) << "Admin Menu of options:" << 
    endl << setfill(' ') << setw(48) << "Change Password" << setfill(' ') << setw(25) << "(type number \"1\")" << endl;
    cout << setfill(' ') << setw(39) << "Logout" << setfill(' ') << setw(34) <<"(type number \"2\")" << endl;
    cout << setfill(' ') << setw(38) << "Stats" << setfill(' ') << setw(35) <<"(type number \"3\")" << endl;
    cout << setfill(' ') << setw(37) << "Info" << setfill(' ') << setw(36) <<"(type number \"4\")" << endl;
    cout << setfill(' ') << setw(39) << "Battle" << setfill(' ') << setw(34) <<"(type number \"5\")" << endl;
    cout << setfill(' ') << setw(37) << "Exit" << setfill(' ') << setw(36) <<"(type number \"0\")" << endl;
    
    while (1){
        //change password
        if (GetKeyState('1') < 0 && !oneKeyPressedLastLoop) { //checks to make sure that the 1 key is pressed and makes sure it was not pressed last check
            oneKeyPressedLastLoop = true;
            value = 1;
            break;
        } else if (GetKeyState('1') >= 0){ // else 1 not pressed
            oneKeyPressedLastLoop = false;
        }
        //Logout
        if (GetKeyState('2') < 0 && !twoKeyPressedLastLoop) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
            twoKeyPressedLastLoop = true;
            value = 2;
            break;
        } else if (GetKeyState('2') >= 0){ // else 2 not pressed
            twoKeyPressedLastLoop = false;
        }
        //Stats of any user
        if (GetKeyState('3') < 0 && !threeKeyPressedLastLoop) { //checks to make sure that the 3 key is pressed and makes sure it was not pressed last check
            threeKeyPressedLastLoop = true;
            value = 3;
            break;
        } else if (GetKeyState('3') >= 0){ // else 3 not pressed
            threeKeyPressedLastLoop = false;
        }
        //Info - game version
        if (GetKeyState('4') < 0 && !fourKeyPressedLastLoop) { //checks to make sure that the 4 key is pressed and makes sure it was not pressed last check
            fourKeyPressedLastLoop = true;
            value = 4;
            break;
        } else if (GetKeyState('4') >= 0){ // else 4 not pressed
            fourKeyPressedLastLoop = false;
        }
        //Battle start
        if (GetKeyState('5') < 0 && !fiveKeyPressedLastLoop) { //checks to make sure that the 5 key is pressed and makes sure it was not pressed last check
            fiveKeyPressedLastLoop = true;
            value = 5;
            break;
        } else if (GetKeyState('5') >= 0){ // else 5 not pressed
            fiveKeyPressedLastLoop = false;
        }
        //Exit program
        if (GetKeyState('0') < 0 && !zeroKeyPressedLastLoop) { //checks to make sure that the 0 key is pressed and makes sure it was not pressed last check
            zeroKeyPressedLastLoop = true;
            value = 0;
            break;
        } else if (GetKeyState('0') >= 0){ // else 0 not pressed
            zeroKeyPressedLastLoop = false;
        }

        //hidden feature: 
        //Nina's surprise
        if (GetKeyState('N') < 0 && GetKeyState('I') < 0 && GetKeyState('A') < 0) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
            nKeyPressedLastLoop = true;
            iKeyPressedLastLoop = true;
            aKeyPressedLastLoop = true;
            value = 14;
            break;
        } else if (GetKeyState('N') >= 0 || GetKeyState('I') >= 0 || GetKeyState('A') >= 0){ // else 1 not pressed
            nKeyPressedLastLoop = false;
            iKeyPressedLastLoop = false;
            aKeyPressedLastLoop = false;
        }
    }
    switch (value)
    {
    case 0: //exit program
        exit(0);
        break;
    case 1: //change password
        //change password
        system("cls");
        cout << "Taking you to the change password screen." << endl;
        system("pause");
        account.logonScreen(2);
        break;
    case 2://logout
        system("cls");
        cout << "You are now logging out." << endl;
        system("pause");
        account.logonScreen();
        break;
    case 3://display stats
        system("cls");
        cout << "Taking you to the screen for viewing stats" << endl;
        system("pause");
        system("cls");
        cout << "Please enter the username of the user for which you would like to view stats." << endl << ">";
        cin >> usernameE;
        account.displayStats(usernameE, 1, username);
        usernameE = "";
        adminMenu(username);
        break;
    case 4://display version and info
        system("cls");
        getGameVersion();
        adminMenu(username);
        break;
    case 5: //start battle
        system("cls");
        battle.startBattle(username);//start battle code will go here.
        break;
    case 14:
        system("cls");
        cout << "October is a Beautiful month to get Married!" << endl;
        cout << "Dakota loves Beautiful!" << endl;
        system("pause");
        adminMenu(username);
        break;
    default:
        system("cls");
        cout << "Invalid input, Please try again..." << endl;
        system("pause");
        adminMenu(username);
        break;
    }
}

void Menu::changePass(string username){ //changes the users password
    system("cls");
    ReachOutToServer server;
    string passwordNew;
    string passwordConf;
    bool validPassword = false;
    char nonValidPasswordCharacters[] = {'~', '!', '?', '`', '\'', '\"', '\\', '(', ')', '{', '}', '\[', ']', '|', '`','!','$','%','^','&','*','<',',','>',':',';','#','_','-','+','=','@','.','"','"'};
    while (!validPassword) {
        cout << "Please enter a new password for your account\n> ";
        cin >> passwordNew; //get the user's new password
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        int len = sizeof(nonValidPasswordCharacters)/sizeof(nonValidPasswordCharacters[0]); //length of array of non valid password Charaters
        for (int lengthOfArray = len; lengthOfArray >= 0; lengthOfArray--){ //loop through all the nonValidPasswordCharacters to make sure the user is not trying to use any of them.
            if (passwordNew.find(nonValidPasswordCharacters[lengthOfArray]) != std::string::npos || passwordNew.length() < 4 || passwordNew.find(username) != std::string::npos) {
                //found the character
                //password is invalid
                validPassword = false;
                cout << "The password you entered is invalid, Please try a different password." << endl << "Note, the password cannot contain: (){}[]|`¬¦! \"£$%^&*\"<>:;#~_-+=,@." << endl << "The password must also be atleast 4 charaters in length and not the same as your username." << endl;
                break;
            } else {
                //password does not contain character
                validPassword = true;
            }
        }
        system("cls");
    }
    cout << "Please enter a new password again for your account\n> ";
    cin >> passwordConf;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        
    if (passwordNew == passwordConf){
        server.sendToServer(code.cipher("4", username, passwordNew));
        menu(username);
    } else {
        cout << "Your passwords did not match, please try again..." << endl;
        system("pause");
        system("cls");
        changePass(username);
    }
    
    
}

char Menu::yesOrNo(){ //waits for a user to click the y or n key
    bool yKeyPressedLastLoop = false;
    bool nKeyPressedLastLoop = false;
    while (1){
        if (GetKeyState('Y') < 0 || GetKeyState('y') < 0 && !yKeyPressedLastLoop) { //checks to make sure that the 3 key is pressed and makes sure it was not pressed last check
            yKeyPressedLastLoop = true;
            return 'y';
        } else if (GetKeyState('y') >= 0 || GetKeyState('Y') >= 0){ // else 1 not pressed
            yKeyPressedLastLoop = false;
        }
        if (GetKeyState('N') < 0 || GetKeyState('n') < 0 && !nKeyPressedLastLoop) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
            nKeyPressedLastLoop = true;
            return 'n';
        } else if (GetKeyState('n') >= 0 || GetKeyState('n') >= 0){ // else 1 not pressed
            nKeyPressedLastLoop = false;
        }
    }
    ClearConsoleInputBuffer();
}