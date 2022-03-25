#include <string>
#include <iostream>
#include <climits>
#include <limits>
#include <iomanip>

#include "Account.h"
#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Menu.h"

using namespace std;
Menu menuClass;

#undef min // these are needed for the cin.ignore statments to clear out the buffer for new data.
#undef max 

/*************************************************************************
The purpose of this file to to manage the user account and Character setup
*************************************************************************/



void Account::setHealth(std::string username){ //initial choice of health stats
    int healthS = 0;
    cout << "Enter the number of points you would like to add to your Health stat: ";
    cin >> healthS;
    if (healthS <= remainingStatPoints) {
        health = healthS;
        remainingStatPoints -= healthS;
    } else {
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        health = attack = armor = magicResistance = 0;
        system("pause");
        createCharacter(username);
    }
}
void Account::setAttack(std::string username){ //initial choice of Attack stats
    int attackS = 0;
    cout << "Enter the number of points you would like to add to your Attack stat: ";
    cin >> attackS;
    if (attackS <= remainingStatPoints) {
        attack = attackS;
        remainingStatPoints -= attackS;
    } else {
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        health = attack = armor = magicResistance = 0;
        system("pause");
        createCharacter(username);
    }
}
void Account::setArmor(std::string username){ //initial choice of Armor stats
    int armorS = 0;
    cout << "Enter the number of points you would like to add to your Armor stat: ";
    cin >> armorS;
    if (armorS <= remainingStatPoints) {
        armor = armorS;
        remainingStatPoints -= armorS;
    } else {
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        health = attack = armor = magicResistance = 0;
        system("pause");
        createCharacter(username);
    }
}
void Account::setMagicResistance(std::string username){ //initial choice of Magic Resistance stats
    int magicResistanceS = 0;
    cout << "Enter the number of points you would like to add to your Magic Resistance stat: ";
    cin >> magicResistanceS;
    if (magicResistanceS <= remainingStatPoints) {
        magicResistance = magicResistanceS;
        remainingStatPoints -= magicResistanceS;
    } else {
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        health = attack = armor = magicResistance = 0;
        system("pause");
        createCharacter(username);
    }
}

void Account::createCharacter(string username){ //running through the stat choosing - This is the inital user setup
    ReachOutToServer server;
    Cipher code;
    remainingStatPoints = 3;
    system("cls");
    cout << "(1ST - Health, 2ND - Attack, 3RD - Armor, 4TH - Magic Resistance)" << endl << "You have 3 points that can be distributed among the above stats" << endl;
    system("pause");
    system("cls");
    cout << "(1ST - Health, 2ND - Attack, 3RD - Armor, 4TH - Magic Resistance)" << endl << "You have 3 points that can be distributed among the above stats" << endl << endl << "Please enter the number of points to add to each stat." << endl << endl;
    setHealth(username);
    if (remainingStatPoints > 0) setAttack(username);
    if (remainingStatPoints > 0) setArmor(username);
    if (remainingStatPoints > 0) setMagicResistance(username);
    if (remainingStatPoints > 0) { //if the user did not use all their stat points we will restart the proccess
        cout << remainingStatPoints << endl;
        system("cls");
        cout << "You did not use all your Stat Points..." << endl << "Restarting this proccess so you can complete this task.";
        system("pause");
        health = attack = armor = magicResistance = 0; //reset all to 0
        createCharacter(username);
    }
    //Need to write the stats to file so that they are stored to be opened again later.
    //if the code makes it to this point then the user is done and will go to main menu.
    system("cls");
    cout << "Your stat points have been to set to the following: " << endl << "Health: " << health << endl << "Attack: " << attack << endl << "Armor: " << armor << endl << "Magic Resistance: " << magicResistance << endl;
    system("pause");
    string wasAbleToSave = server.sendToServer(code.cipher("5", username, to_string(health), to_string(attack), to_string(armor), to_string(magicResistance)));
    if( wasAbleToSave == "wasAbleToSave") {
        string answer;
        //if yes bring them to the logon screen
        while (answer != "y" || answer != "Y" || answer != "n" || answer != "N"){ //confirm that the user is okay with their inital choice of stats.
            cout << endl << "Are you satisfied with the above stats? (Y/N)\n>";
            cin >> answer;
            if(answer == "y" || answer == "Y"){
                menuClass.changePass(username); //before sending them to the logon screen they need to set their new account's password.
            } else if (answer == "n" || answer == "N") { //if they are not then we will start the process again.
                createCharacter(username);
            }
            system("cls");
            cout << "Your answer was not recognized.  Please re-enter your answer." << endl;
            system("pause");
            system("cls");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer

        }
        // HasGoneThroughInitalSetup = true; //sets the value to true because the user has successfully added the 3 inital setup points to their Character.
    }
    cout << "Something went wrong... Please run through the stats proccess again." << endl;
    createCharacter(username);
}

int Account::getHealth(std::string username){ //reuturns the users current Health stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.item1);
}
int Account::getAttack(std::string username){ //reuturns the users current Attack stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.item2);
}
int Account::getArmor(std::string username){ //reuturns the users current Armor stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username))); 
    return stoi(code.item3);
}
int Account::getMagicResistance(std::string username){ //reuturns the users current MagicResistance stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.item4);
}

void Account::displayStats(std::string username, int bypass ,string usernameA){
    Cipher code;
    ReachOutToServer server;
    if (bypass == 0) { //standard user
        cout << "Your stats are as follows: " << endl << "Health: " << setfill(' ') << setw(34) << getHealth(username) << endl << "Attack: " << setfill(' ') << setw(34) << getAttack(username) << endl << "Armor: " << setfill(' ') << setw(35) << getArmor(username) << endl << "Magic Resistance: " << setfill(' ') << setw(24) << getMagicResistance(username) << endl;
        system("pause");
    } 
    if (bypass == 1) { //admin account
        if(stoi(server.sendToServer(code.cipher("1", username))) == 0) {
            cout << "Your stats are as follows: " << endl << "Health: " << setfill(' ') << setw(34) << getHealth(username) << endl << "Attack: " << setfill(' ') << setw(34) << getAttack(username) << endl << "Armor: " << setfill(' ') << setw(35) << getArmor(username) << endl << "Magic Resistance: " << setfill(' ') << setw(24) << getMagicResistance(username) << endl;
            system("pause");
        } else {
            cout << "You did not enter a valid user which has stats to view..." << endl;
            system("pause");
        }
        menuClass.adminMenu(usernameA);
    }
    
}

void Account::logonScreen(int type){ //defualt is case 1 - that is a standard logon... Case 2 is change password logon
    Cipher code;
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
                menuClass.menu(usernameE);
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
                menuClass.changePass(usernameE);
            } else {
                cout << "Invalid Username or Password..." << endl;
                system("pause");
                //logon is invalid
                menuClass.menu(usernameE);
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
                menuClass.adminMenu(usernameE);
            } else {
                cout << "Invalid Username or Password..." << endl;
                system("pause");
                //logon is invalid
                newOrExistingAccout();
            }
            break;
    }
}

void Account::createNewAccount(){ //runs through the code to create a new user account from scratch
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
            cout << "The username " << username << " is valid and you can use it as your username." << endl << "Would you like to continue and create an account with this username? (Y/N)" << endl << "> ";
            cin >> createAccountCheck;
            if(createAccountCheck == "y" || createAccountCheck == "Y"){
                cout << "We will now create the account" << endl;
                server.sendToServer(code.cipher("2", username, "testing account creation..."));
                system("cls");
                account.createCharacter(username); // need to create this function
                //logonScreen(); //move this to the end of character cration
                // gonna need to run through the character creation before sign in

            } else if (createAccountCheck == "N" || createAccountCheck == "n"){
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

void Account::newOrExistingAccout(){ // asks and runs through everything for new accounts and if existing brings the user to the logon screen.
    Cipher code;
    //ask the user if they have an account with MightyWarrior game
    system("cls");
    string answer;
    cout << "Do you have an account yet? (Y/N)" << endl;
    cin >> answer;
    
    //if yes bring them to the logon screen
    if(answer == "y" || answer == "Y"){
        system("cls");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        logonScreen();
    } else if (answer == "n" || answer == "N") {//if no start the signup prossess
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
        cout << "Your answer was not \"Y\" or \"N\"." << endl << "Please try again." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear out cin buffer
        system("pause");//pause the window so the user can read the message, then they can press any key to continue.
        newOrExistingAccout(); // take user to beguining of this function again
    }
}
