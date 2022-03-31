#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

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

void Menu::getGameVersion(){
    cout << "Client Version: " << to_string(gameVersion) << "." << to_string(gameMajorBuild) << "." << to_string(gameMinorBuild) << "." << to_string(gamePatch) << endl;
    system("pause");
}

void Menu::menu(string username){ //bring up the menu for the passing in the username
    system("cls");
    int value;
    cout << setfill(' ') << setw(61) << "Menu of options:" << 
    endl << setfill(' ') << setw(48) << "Change Password" << setfill(' ') << setw(25) << "(type number \"1\")" << endl;
    cout << setfill(' ') << setw(39) << "Logout" << setfill(' ') << setw(34) <<"(type number \"2\")" << endl;
    cout << setfill(' ') << setw(38) << "Stats" << setfill(' ') << setw(35) <<"(type number \"3\")" << endl;
    cout << setfill(' ') << setw(37) << "Info" << setfill(' ') << setw(36) <<"(type number \"4\")" << endl;
    cout << setfill(' ') << setw(39) << "Battle" << setfill(' ') << setw(34) <<"(type number \"5\")" << endl;
    cout << setfill(' ') << setw(37) << "Exit" << setfill(' ') << setw(36) <<"(type number \"0\")" << 
    endl << setfill(' ') << setw(35) << "> ";
    
    if(cin >> value){
        switch (value)
        {
        case 1: //change password
            //change password
            account.logonScreen(2);
            break;
        case 2://logout
            system("cls");
            account.logonScreen();
            break;
        case 3://display stats
            system("cls");
            account.displayStats(username);
            menu(username);
            break;
        case 4://display version and info
            system("cls");
            getGameVersion();
            menu(username);
            break;
        case 5: //start battle
            system("cls");
            battle.startBattle(username);//start battle code will go here.
            break;
        case 0:
            exit(1);
            break;
        case 10:
            system("cls");
            cout << "October is a Beautiful month to get Married!" << endl;
            system("pause");
            menu(username);
            break;
        case 14:
            system("cls");
            cout << "Dakota loves Beautiful!" << endl;
            system("pause");
            menu(username);
            break;
        }
    } else {
        cout << "\nPlease enter a valid number." << endl;
        system("pause");
        system("cls");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        menu(username);
    }
}

void Menu::adminMenu (string username){ //The admin menu that will have more advanced options later
    ReachOutToServer server;
    string usernameE;
    system("cls");
    int value;
    cout << setfill(' ') << setw(44) << "Menu of options:\nChange Password" << setfill(' ') << setw(25) << "(type number \"1\")" << endl;
    cout << "Logout" << setfill(' ') << setw(34) <<"(type number \"2\")" << endl;
    cout << "Stats" << setfill(' ') << setw(35) <<"(type number \"3\")" << endl;
    cout << "Info" << setfill(' ') << setw(36) <<"(type number \"4\")" << endl;
    cout << "Exit" << setfill(' ') << setw(39) <<"(type number \"0\")\n> ";
    
    if(cin >> value){
        switch (value)
        {
        case 1:
            //change password
            account.logonScreen(2);
            break;
        case 2:
            system("cls");
            account.logonScreen();
            break;
        case 3:
            system("cls");
            cout << "Please enter the username of the user for which you would like to view stats.\n>";
            cin >> usernameE;
            account.displayStats(usernameE, 1, username);
            usernameE = "";
            menu(username);
            break;
        case 4:
            system("cls");
            getGameVersion();
            menu(username);
            break;
        case 0:
            exit(1);
            break;
        case 14:
            system("cls");
            cout << "Dakota loves Beautiful!" << endl;
            system("pause");
            break;
        }
    } else {
        cout << "\nPlease enter a valid number." << endl;
        system("pause");
        system("cls");
        menu(username);
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
        system("pause");
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
