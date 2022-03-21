#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <string>
#include <fstream>
#include <climits>
#include <iomanip>

#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Account.h"

#undef min // these are needed for the cin.ignore statments to clear out the buffer for new data.
#undef max 

#pragma comment(lib, "ws2_32")   //to be able to use sockets
#pragma comment(lib, "advapi32")

//********************************************
const int gameVersion     = 1;
const int gameMajorBuild  = 0;
const int gameMinorBuild  = 0;
const int gamePatch       = 0;
//********************************************

using namespace std; //so I dont have to type "std::"
Cipher code; //declare the new instance of Cipher class

void logonScreen(int type = 1);
void menu(string username){ //bring up the menu for the passing in the username
    system("cls");
    int value;
    cout << setfill(' ') << setw(44) << "Menu of options:\nChange Password" << setfill(' ') << setw(25) << "(type number \"1\")" << endl;
    cout << "Logout" << setfill(' ') << setw(34) <<"(type number \"2\")" << endl;
    cout << "Exit" << setfill(' ') << setw(39) <<"(type number \"0\")\n> ";
    
    if(cin >> value){
        switch (value)
        {
        case 1:
            //change password
            logonScreen(2);
            break;
        case 2:
            system("cls");
            logonScreen();
            break;
        case 0:
            exit(1);
            break;
        }
    } else {
        cout << "\nPlease enter a valid number." << endl;
        system("pause");
        system("cls");
        menu(username);
    }
}

void adminMenu (string username){ //The admin menu that will have more advanced options later
    system("cls");
    int value;
    cout << setfill(' ') << setw(44) << "Menu of options:\nChange Password" << setfill(' ') << setw(25) << "(type number \"1\")" << endl;
    cout << "Logout" << setfill(' ') << setw(34) <<"(type number \"2\")" << endl;
    cout << "Exit" << setfill(' ') << setw(39) <<"(type number \"0\")\n> ";
    
    if(cin >> value){
        switch (value)
        {
        case 1:
            //change password
            logonScreen(2);
            break;
        case 2:
            system("cls");
            logonScreen();
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

void changePass(string username){ //changes the users password
    system("cls");
    ReachOutToServer server;
    string passwordNew;
    string passwordConf;
    cout << "Please enter the new password for your account\n> ";
    cin >> passwordNew;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
    cout << "Please enter the new password again for your account\n> ";
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


void newOrExistingAccout();
void logonScreen(int type){ //defualt is case 1 - that is a standard logon... Case 2 is change password logon
    system("cls");
    ReachOutToServer server;
    string usernameE;
    string passwordE;
    int validLogon;
    switch (type){
        case 1:
            cout << "You are at the logon screen" << endl << "Please enter your username\n> ";
            cin >> usernameE;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
            cout << "Please enter the password for the account\n> ";
            cin >> passwordE;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
            validLogon = stoi(server.sendToServer(code.cipher("3", usernameE, passwordE)));
            if (validLogon == 1){//logon is valid
                menu(usernameE);
            } else {
                cout << "Invalid Username or Password..." << endl;
                system("pause");
                //logon is invalid
                newOrExistingAccout();
            }
            break;
        case 2: //change password verification
            system("cls");
            cout << "Please confirm your current credentials" << endl << "Please enter your username\n> ";
            cin >> usernameE;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
            cout << "Please enter the CURRENT password for the account\n> ";
            cin >> passwordE;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
            validLogon = stoi(server.sendToServer(code.cipher("3", usernameE, passwordE)));
            if (validLogon == 1){//logon is valid
                system("cls");
                changePass(usernameE);
            } else {
                cout << "Invalid Username or Password..." << endl;
                system("pause");
                //logon is invalid
                menu(usernameE);
            }
            break;
        case 3: // adminbypass panel
            cout << "You are at the admin bypass panel" << endl << "Please enter the admin username\n> ";
            cin >> usernameE;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
            cout << "Please enter the password for the account\n> ";
            cin >> passwordE;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
            validLogon = stoi(server.sendToServer(code.cipher("3", usernameE, passwordE)));
            if (validLogon == 1){//logon is valid
                adminMenu(usernameE);
            } else {
                cout << "Invalid Username or Password..." << endl;
                system("pause");
                //logon is invalid
                newOrExistingAccout();
            }
            break;
    }
}

void createNewAccount(){ //runs through the code to create a new account
    int valid; // is the username valid or not (1 meaning the username is valid, 0 meaning the username is taken)
    ReachOutToServer server;//declare server object to use sendserver function to check if server has someone by this username
    Cipher code; //declare the Cipher class so that I can use the functions cipher and decipher
    Account account;
    string username; //declare the local username for the user creating their account

    //ask user for the username they would like to use
    cout << "What would you like the username of your new account to be?" << endl << "Please type a valid username.\n> ";
    cin >> username;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
    system("cls");

    //check to make sure the username is valid and not already taken
    if (username.find(code.delimiter) != std::string::npos || username.find("&") != std::string::npos || username.find("=") != std::string::npos || username.find("'") != std::string::npos || username.find("-") != std::string::npos|| username.find("+") != std::string::npos|| username.find(",") != std::string::npos|| username.find("<") != std::string::npos|| username.find(">") != std::string::npos|| username.find("..") != std::string::npos) { // make sure the username is not using the delimiter and a few other characters //this list was taken from https://support.google.com/mail/answer/9211434?hl=en
        system("cls");
        cout << "The username " << username << " is not valid Please enter a different username." << endl;
        system("pause");
        createNewAccount();
    } else {
        valid = stoi(server.sendToServer(code.cipher("1", username))); // the response for this will either be 1 or 0 as a string (1 meaning the username is valid, 0 meaning the username is taken)
        switch (valid){
            case 0:
            //the username is invalid so restart the process
            cout << "The username " << username << " is not valid. Please enter a different username." << endl;
            system("pause");
            system("cls");
            createNewAccount();
            break;
            case 1:
            //username is valid
            string createAccountCheck;
            cout << "The username " << username << " is valid and you can use it as your username." << endl << "Would you like to continue and create an account with this username? (yes or no)" << endl << "> ";
            cin >> createAccountCheck;
            if(createAccountCheck == "yes"){
                cout << "We will now create the account" << endl;
                server.sendToServer(code.cipher("2", username, "testing account creation..."));
                system("cls");
                account.createCharacter(username); // need to create this function
                //logonScreen(); //move this to the end of character cration
                // gonna need to run through the character creation before sign in

            } else if (createAccountCheck == "no"){
                cout << "Account will not be created." << endl;
                system("pause");
                newOrExistingAccout();
            } else {
                cout << "Input not recognized." << endl;
                system("pause");
                newOrExistingAccout();
            }
            break;
        }
    }
}

void newOrExistingAccout(){ // asks and runs through everything for new accounts and if existing brings the user to the logon screen.
    //ask the user if they have an account with MightyWarrior game
    system("cls");
    string answer;
    cout << "Do you have an account yet? (yes or no)" << endl;
    cin >> answer;
    
    //if yes bring them to the logon screen
    if(answer == "yes"){
        system("cls");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        logonScreen();
    } else if (answer == "no") {//if no start the signup prossess
        system("cls");
        cout << "Lets start the procss of creating a new account." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        system("pause");//pause the window so the user can read the message, then they can press any key to continue.
        createNewAccount(); // take user to the function for creatiing accounts 
    } else if (answer == "adminbypass"){
        system("cls");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        logonScreen(3);
    } else {
        cout << "Your answer was not \"yes\" or \"no\"." << endl << "Please try again." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear out cin buffer
        system("pause");//pause the window so the user can read the message, then they can press any key to continue.
        newOrExistingAccout(); // take user to beguining of this function again
    }
}

int main(){
    ReachOutToServer server; //declare a new instance of ReachOutToServer called server
    string serverVersionResponse = server.sendToServer(code.cipher("0", "", to_string(gameVersion), to_string(gameMajorBuild), to_string(gameMinorBuild), to_string(gamePatch)));//check to see if the version the client is running is allowed to continue - the reponse is stored in "serverVersionResponse"
    //Before doing anything else... request required client version from server.
    if (serverVersionResponse == "true"){ //if it is true then the program will start
        //This is the start of the program
        newOrExistingAccout(); //ask whether the user has an account or not
    } else if (serverVersionResponse == "FailedConnect") { //If the client is unable to connect to the server inform the client
        cout << "The Server is currently Offline for either maintanance or other reasons..." << endl << "Please try again later..." << endl;
        system("pause");
    } else{//if version check fails we inform user and close the client
        cout << "You are not running the needed version. Please update to the latest version and try again." << endl;
        system("pause");
    }
    
    return 0;
}