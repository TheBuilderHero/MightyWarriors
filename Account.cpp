#include <string>
#include <iostream>
#include <climits>
#include <limits>
#include <iomanip>
#include <cstdlib> //this and ctime are for the random number generator
#include <ctime> 

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
        createPlayer(username);
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
        createPlayer(username);
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
        createPlayer(username);
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
        createPlayer(username);
    }
}

void Account::createPlayer(string username){ //This is the inital user setup (should run through Race selection and Kit selection) and this should all be saved to the server
    ReachOutToServer server;
    Cipher code;

    cout << "Welcome to Character creation!" << endl;
    system("pause");
    system("cls");
    int raceChoice = 0;
    char answer;
    bool exitNow = false;
    while(!exitNow){ //while the user has not selected one of the five options it will continue to ask them for an aswer.
        system("cls");
        raceChoice = 0;
        cout << endl << "First step of the process is to choose the race of your Character" << endl;
        cout << "Please type the number corresponding to one of the races from the list below (Note, this cannot be changed later!): "<< endl << endl;
        cout << "1" << setfill(' ') << setw(14) << "Human" << endl;
        cout << "-" << setfill(' ') << setw(49) << "- Human's gain +1 to all stats" << endl;
        cout << "2" << setfill(' ') << setw(14) << "Ghost" << endl;
        cout << "-" << setfill(' ') << setw(49) << "- Human's gain +1 to all stats" << endl;
        cout << "3" << setfill(' ') << setw(14) << "Dino" << endl;
        cout << "-" << setfill(' ') << setw(49) << "- Human's gain +1 to all stats" << endl;
        cout << "4" << setfill(' ') << setw(14) << "Elf" << endl;
        cout << "-" << setfill(' ') << setw(49) << "- Human's gain +1 to all stats" << endl;
        cout << "5" << setfill(' ') << setw(14) << "Dryad" << endl;
        cout << "-" << setfill(' ') << setw(49) << "- Human's gain +1 to all stats" << endl;
        cout << ">";
        cin >> raceChoice;
        if (raceChoice <= 0 || raceChoice > 5) {
            cout << "You have entered an invalid input, Please try again." << endl;
            raceChoice = 0;
            system("pause");
            system("cls");
        } else {
            bool answered = false;
            while(!answered) { //validate the chosen race
                cout << "Your race has been set to option number " << raceChoice << ". Would you like to accept this and continue?(Y/N)" << endl << ">";
                cin >> answer;
                if (answer != 'n' && answer !='N' && answer !='y' && answer !='Y') { //if they did not enter y, Y, n, or, N then we will tell them what they input is invalid and retry.
                    cout << "Unrecognized input." << "   Please enter a valid input." << endl;
                    system("pause");
                    system("cls");
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
                } else if (answer =='y' || answer =='Y') { //if they are statisfied with their choice it will move on and exit both while loops
                    answered = true;
                    exitNow = true;
                } else { //if they are not satisfied with their choice it will exit the loop of asking them if they are stisfied and reask about the race which they want to select.
                    answered = true;
                }
            }
        }
    }
    system("cls");
    //Now that the race has been chosen and validated move on to kit selection
    cout << "Now it is time to select your Kit" << endl;
    system("pause");
    int kitChoice = 0;
    exitNow = false;
    while(!exitNow){ //while the user has not selected one of the four kit options it will continue to ask them for an aswer to kitChoice.
        system("cls");
        kitChoice = 0;
        cout << endl << "Second step of the process is to choose the kit of your Character" << endl;
        cout << "Please type the number corresponding to one of the kits from the list below (Note, this cannot be changed later!): "<< endl << endl;
        cout << "1" << setfill(' ') << setw(14) << "Tank" << endl;
        cout << "-" << setfill(' ') << setw(77) << "- Tanks gain +3 to Armor, Magic Resistance, and Health stats" << endl;
        cout << "2" << setfill(' ') << setw(17) << "Assasin" << endl;
        cout << "-" << setfill(' ') << setw(50) << "- Assasins gain +5 to Attack stat" << endl;
        cout << "3" << setfill(' ') << setw(16) << "Archer" << endl;
        cout << "-" << setfill(' ') << setw(81) << "- Archers gain +2 on Attack and +1 on Armor and Magic Resistance" << endl;
        cout << "4" << setfill(' ') << setw(14) << "Mage" << endl;
        cout << "-" << setfill(' ') << setw(70) << "- Mages gain +2 on Ability and +3 on Magic Resistance" << endl;
        cout << ">";
        cin >> kitChoice;
        if (kitChoice <= 0 || kitChoice > 4) {
            cout << "You have entered an invalid input, Please try again." << endl;
            kitChoice = 0;
            system("pause");
            system("cls");
        } else {
            int answered = 0; // 0 for false :: 1 for true
            while(!answered) { //validate the chosen race
                cout << "Your kit has been set to option number " << kitChoice << ". Would you like to accept this and continue?(Y/N)" << endl << ">";
                cin >> answer;
                if (answer != 'n' && answer !='N' && answer !='y' && answer !='Y') { //if they did not enter y, Y, n, or, N then we will tell them what they input is invalid and retry.
                    cout << "Unrecognized input." << "   Please enter a valid input." << endl;
                    system("pause");
                    system("cls");
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
                } else if (answer =='y' || answer =='Y') { //if they are statisfied with their choice it will move on and exit both while loops
                    answered = 1;
                    exitNow = 1;
                } else { //if they are not satisfied with their choice it will exit the loop of asking them if they are stisfied and reask about the race which they want to select.
                    answered = 1;
                }
            }
        }
    }
    //
    //-Kyle - Please review the following
    //
    server.sendToServer(code.cipher("8", username, to_string(raceChoice), to_string(kitChoice))); //write race and kit to .dat file on server

    //add it an inital stat personalization
    string wasAbleToSave = server.sendToServer(code.cipher("5", username, to_string(health), to_string(attack), to_string(armor), to_string(magicResistance), to_string(agility),
    to_string(stealth))); //These send the data to the server to be saved properly in the [username].stat file
    system("cls");
    cout << "You have complete the Player setup Proccess." << endl;
    system("pause");

    introStory(username); //send the user to the intro story
}

int Account::getHealth(std::string username){ //reuturns the users current Health stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.getItemS(1));
}
int Account::getPhysicalDamage(std::string username){ //reuturns the users current Attack stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.getItemS(4));
}
int Account::getArmor(std::string username){ //reuturns the users current Armor stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username))); 
    return stoi(code.getItemS(2));
}
int Account::getMagicResistance(std::string username){ //reuturns the users current MagicResistance stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.getItemS(3));
}

void Account::displayStats(std::string username, int bypass ,string usernameA){
    Cipher code;
    ReachOutToServer server;
    if (bypass == 0) { //standard user
        cout << "Your stats are as follows: " << endl << "Health: " << setfill(' ') << setw(34) << getHealth(username) << endl << "Attack: " << setfill(' ') << setw(34) << 
        getPhysicalDamage(username) << endl << "Armor: " << setfill(' ') << setw(35) << getArmor(username) << endl << "Magic Resistance: " << setfill(' ') << setw(24) << 
        getMagicResistance(username) << endl;
        system("pause");
    } 
    if (bypass == 1) { //admin account
        if(stoi(server.sendToServer(code.cipher("1", username))) == 0) {
            cout << "Your stats are as follows: " << endl << "Health: " << setfill(' ') << setw(34) << getHealth(username) << endl << "Attack: " << setfill(' ') << setw(34) << 
            getPhysicalDamage(username) << endl << "Armor: " << setfill(' ') << setw(35) << getArmor(username) << endl << "Magic Resistance: " << setfill(' ') << setw(24) << 
            getMagicResistance(username) << endl;
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
    if (username.find(code.getDelimiter()) != std::string::npos || username.find("&") != std::string::npos || username.find("=") != std::string::npos || username.find("'") != std::string::npos || username.find("-") != std::string::npos|| username.find("+") != std::string::npos|| username.find(",") != std::string::npos|| username.find("<") != std::string::npos|| username.find(">") != std::string::npos|| username.find("..") != std::string::npos) { // make sure the username is not using the delimiter and a few other characters //this list was taken from https://support.google.com/mail/answer/9211434?hl=en
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
                server.sendToServer(code.cipher("2", username));
                system("cls");
                account.createPlayer(username); // creates the Character for the user to use in the game

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

void Account::introStory(string username){ //this random story generation should probably be moved onto the server.
    system("cls");
    srand((unsigned)time(0)); //takes a seed for the random number based on the time
    int randomStoryChoice;
    randomStoryChoice = (rand()%3)+1;

    cout << "Welcome to the game Mighty Warriors!" << endl 
    << storyTree(randomStoryChoice) << endl;
    system("pause");

    menuClass.changePass(username); //before sending them to the logon screen they need to set their new account's password.
}

string Account::storyTree(int randomStoryChoice){ // i1 is just a placement value for the actual determing value that should be added to make this more random in chance for story line.
    string output;
    //need to make this all fetched from the server.
    switch(randomStoryChoice){
        case 1:
            output = "[Story 1 for user to read about their Character based on input about it]";
            break;
        case 2:
            output = "[Story 2 for user to read about their Character based on input about it]";
            break;
        case 3:
            output = "[Story 3 for user to read about their Character based on input about it]";
            break;
        default:
            output = "[Story default for user to read about their Character based on input about it]";
    }
    return output;
}