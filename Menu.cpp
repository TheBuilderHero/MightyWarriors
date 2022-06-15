#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdio.h>
#include <sstream>

#include "Account.h"
#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Menu.h"
#include "Battle.h"
#include "Map.h"
#include "WorldMap.h"
#include "Quests.h"

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
    display(3, 3, "Client Version: " + to_string(gameVersion) + "." + to_string(gameMajorBuild) + "." + to_string(gameMinorBuild) + "." + to_string(gamePatch), false);
    system("pause");
}

void Menu::menu(string username){ //bring up the menu for the passing in the username
    bool oneKeyPressedLastLoop = false, twoKeyPressedLastLoop = false, threeKeyPressedLastLoop = false, fourKeyPressedLastLoop = false, zeroKeyPressedLastLoop = false,
    nKeyPressedLastLoop = false, iKeyPressedLastLoop = false, aKeyPressedLastLoop = false, 
    controlKeyPressedLastLoop = false, altKeyPressedLastLoop = false ,kKeyPressedLastLoop = false;
    int value;
    bool stayInMenu = true;
    while(stayInMenu){
        system("cls");
        display(50, 1, "Menu");
        display(32, 2, "Go Questing");          display(53, 2, "(Press \"1\")");
        display(32, 3, "Travel");               display(53, 3, "(Press \"2\")");
        display(32, 4, "Stats");                display(53, 4, "(Press \"3\")");
        display(32, 5, "Account Info");         display(53, 5, "(Press \"4\")");
        display(32, 6, "Exit");                 display(53, 6, "(Press \"0\")");
        while (1){
            if (GetKeyState('0') < 0 && !zeroKeyPressedLastLoop) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
                zeroKeyPressedLastLoop = true;
            } else if (GetKeyState('0') >= 0 && zeroKeyPressedLastLoop){ // else 1 not pressed
                zeroKeyPressedLastLoop = false;
                value = 0;
                break;
            }
            if (GetKeyState('1') < 0 && !oneKeyPressedLastLoop) { //checks to make sure that the 1 key is pressed and makes sure it was not pressed last check
                oneKeyPressedLastLoop = true;
            } else if (GetKeyState('1') >= 0 && oneKeyPressedLastLoop){ // else 1 not pressed
                oneKeyPressedLastLoop = false;
                value = 1;
                break;
            }
            if (GetKeyState('2') < 0 && !twoKeyPressedLastLoop) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
                twoKeyPressedLastLoop = true;
            } else if (GetKeyState('2') >= 0 && twoKeyPressedLastLoop){ // else 1 not pressed
                twoKeyPressedLastLoop = false;
                value = 2;
                break;
            }
            if (GetKeyState('3') < 0 && !threeKeyPressedLastLoop) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
                threeKeyPressedLastLoop = true;
            } else if (GetKeyState('3') >= 0 && threeKeyPressedLastLoop){ // else 1 not pressed
                threeKeyPressedLastLoop = false;
                value = 3;
                break;
            }
            if (GetKeyState('4') < 0 && !fourKeyPressedLastLoop) { //checks to make sure that the 4 key is pressed and makes sure it was not pressed last check
                fourKeyPressedLastLoop = true;
            } else if (GetKeyState('4') >= 0 && fourKeyPressedLastLoop){ // else 4 not pressed
                fourKeyPressedLastLoop = false;
                value = 4;
                break;
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
        case 1:{ //"Go Questing"//map for traveling and questing 
                 //We probably need a separate questing menu
            Map map;
            Quests quest;
            system("cls");
            //map.listAvalibleLocations(username);
            quest.setPlayer(player);
            quest.getAvailableQuests();
            setPlayer(quest.getPlayer());
            break;
        }
        case 2://travel option
            system("cls");
            ClearConsoleInputBuffer();
            travelMenu(username);
            break;
        case 3://display stats
            system("cls");
            ClearConsoleInputBuffer();
            displayStats();
            //account.displayStats(username);
            //menu(username);
            break;
        case 4:{
            accountInfo(username);
            break;
        }
        case 14:
            system("cls");
            ClearConsoleInputBuffer();
            display(3,3,"October is a Beautiful month to get Married!");
            display(3,4,"Dakota loves Beautiful!", false);
            system("pause");
            //menu(username);
            break;
        case 15:
            system("cls");
            ClearConsoleInputBuffer();
            adminMenu(username);
            break;
        default:
            system("cls");
            ClearConsoleInputBuffer();
            display(3, 3, "Invalid input, Please try again...", false);
            system("pause");
            //menu(username);
            break;
        }
    }
}

void Menu::travelMenu(string username){ //bring up the menu for travel
    system("cls");
    WorldMap worldMap;
    bool oneKeyPressedLastLoop = false, twoKeyPressedLastLoop = false, threeKeyPressedLastLoop = false, fourKeyPressedLastLoop = false, zeroKeyPressedLastLoop = false,
    nKeyPressedLastLoop = false, iKeyPressedLastLoop = false, aKeyPressedLastLoop = false, 
    controlKeyPressedLastLoop = false, altKeyPressedLastLoop = false ,kKeyPressedLastLoop = false;
    display(50, 1, "Travel");
    display(16, 2, worldMap.getMapDescription(player.getLocation()));//Dakota please help me load the user's current location
    display(32, 3, "Go North");             display(53, 3, "(Press \"1\")");
    display(32, 4, "Go East");              display(53, 4, "(Press \"2\")");
    display(32, 5, "Go South");             display(53, 5, "(Press \"3\")");
    display(32, 6, "Go West");              display(53, 6, "(Press \"4\")");
    display(32, 7, "Return to Menu");       display(53, 7, "(Press \"0\")");
    int value = numberPressWait(4, true);
    switch (value){
    case 0://Return to menu
        menu(username);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        system("cls");
        ClearConsoleInputBuffer();
        display(16, 1, worldMap.getTravelMessage(player.getLocation(), value));//Still need to save this data to files on server side
        player.setLocation(worldMap.travel(player.getLocation(), value));
        waitForEnter(getEnterKeyState());
        //menu(username);
        break;
    case 15:
        system("cls");
        ClearConsoleInputBuffer();
        adminMenu(username);
        break;
    default:
        system("cls");
        ClearConsoleInputBuffer();
        display(3, 3, "menu value somehow set impossibly!", false);
        system("pause");
        //menu(username);
        break;
    }
}

void Menu::displayStats(){
    string physicalDamageAbilities = "Physical Damage Abilities: ";
    string magicDamageAbilities = "Magic Damage Abilities: ";
    if (player.getQDamageType() == "Physical") physicalDamageAbilities += " Q";
    else magicDamageAbilities += " Q";
    if (player.getWDamageType() == "Physical") physicalDamageAbilities += " W";
    else magicDamageAbilities += " W";
    if (player.getEDamageType() == "Physical") physicalDamageAbilities += " E";
    else magicDamageAbilities += " E";
    if (player.getRDamageType() == "Physical") physicalDamageAbilities += " R";
    else magicDamageAbilities += " R";

    stringstream currentXP, totalXP;
    currentXP << fixed << setprecision(0) << player.getCurrentXP(); //format the XP
    totalXP << fixed << setprecision(0) << player.getXPForNextLevel(); //format the XP
    string currentXPFormatted = currentXP.str();
    string totalXPFormatted = totalXP.str();
    string playerLevelInfo = "Player Level: " + to_string(player.getLevel()) +  " With " + currentXPFormatted + "XP of " + totalXPFormatted + "XP";
    string physicalDamageString = to_string(player.getPhysicalDamageMin()) + " - " + to_string(player.getPhysicalDamageMax());
    string magicDamageString = to_string(player.getMagicDamageMin()) + " - " + to_string(player.getMagicDamageMax());
    string psychicDamageString = to_string(player.getPsychicDamageMin()) + " - " + to_string(player.getPsychicDamageMax());

    display(0, 0, "Your stats are as follows:\n");
    cout << "\n" << setfill('=') << setw(92) << "=";
    display(0, 2, "Health:");               display(42 - to_string(player.getHealth()).size(), 2, to_string(player.getHealth()));
    display(48, 2, playerLevelInfo);        display(48, 3, "Player Race: " + player.getRace());
    cout << "\n\n\n" << setfill('-') << setw(42) << "-";
    display(0, 4, "Armor:");                display(42 - to_string(player.getArmor()).size(), 4, to_string(player.getArmor()));
    display(48, 4, "Player Kit: " + player.getKit()); display(48, 5, "Player Weapon: " + player.getWeapon());
    cout << "\n\n\n\n\n" << setfill('-') << setw(42) << "-";
    display(0, 6, "Magic Resistance:");     display(42 - to_string(player.getMagicResistance()).size(), 6, to_string(player.getMagicResistance()));
    cout << "\n\n\n\n\n\n\n" << setfill('-') << setw(42) << "-";
    display(0, 8, "Physical Damage:");      display(42 - physicalDamageString.size(), 8, physicalDamageString);
    display(48, 8, physicalDamageAbilities);
    cout << "\n\n\n\n\n\n\n\n\n" << setfill('-') << setw(42) << "-";
    display(0, 10, "Magic Damage:");        display(42 - magicDamageString.size(), 10, magicDamageString);
    display(48, 10, magicDamageAbilities);
    cout << "\n\n\n\n\n\n\n\n\n\n\n" << setfill('-') << setw(42) << "-";
    display(0, 12, "Agility:");             display(42 - to_string(player.getAgility()).size(), 12, to_string(player.getAgility()));
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n" << setfill('-') << setw(42) << "-";
    display(0, 14, "Stealth:");             display(42 - to_string(player.getStealth()).size(), 14, to_string(player.getStealth()));
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << setfill('-') << setw(42) << "-";
    display(0, 16, "Stamina:");             display(42 - to_string(player.getStamina()).size(), 16, to_string(player.getStamina()));
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << setfill('-') << setw(42) << "-";
    display(0, 18, "Mana:");                display(42 - to_string(player.getMana()).size(), 18, to_string(player.getMana()));
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << setfill('-') << setw(42) << "-";
    display(0, 20, "Mind:");                display(42 - to_string(player.getMind()).size(), 20, to_string(player.getMind()));
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << setfill('-') << setw(42) << "-";
    display(0, 22, "Psychic Damage:");      display(42 - psychicDamageString.size(), 22, psychicDamageString);
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << setfill('-') << setw(42) << "-" << "\n\n";

   /* 
    cout << "Your stats are as follows: " << endl << setfill('=') << setw(92) << "=" << endl 
        << "Health: " << setfill(' ') << setw(34) << player.getHealth() << endl << setfill('-') << setw(42) << "-" << endl 
        << "Armor: " << setfill(' ') << setw(35) << player.getArmor() << endl << setfill('-') << setw(42) << "-" << endl 
        << "Magic Resistance: " << setfill(' ') << setw(24) << player.getMagicResistance() << endl << setfill('-') << setw(42) << "-" << endl 
        << "Physical Damage: " << setfill(' ') << setw(20) << player.getPhysicalDamageMin() << " - " << player.getPhysicalDamageMax() << setfill(' ') <<  endl << setfill('-') << setw(42) << "-" << endl 
        << "Magic Damage: " << setfill(' ') << setw(23) << player.getMagicDamageMin() << " - " << player.getMagicDamageMax() << setfill(' ') << endl << setfill('-') << setw(42) << "-" << endl 
        << "Agility: " << setfill(' ') << setw(33) << player.getAgility() << endl << setfill('-') << setw(42) << "-" << endl 
        << "Stealth: " << setfill(' ') << setw(33) << player.getStealth() << endl << setfill('-') << setw(42) << "-" << endl 
        << "Stamina: " << setfill(' ') << setw(33) << player.getStamina() << endl << setfill('-') << setw(42) << "-" << endl 
        << "Mana: " << setfill(' ') << setw(36) << player.getMana() << endl << setfill('-') << setw(42) << "-" << endl; //This cout statement prints out all the stats for the user to see.
    */

    system("pause");    
}

void Menu::accountInfo(string username){
    int answer;
    system("cls");
    display(44, 1, "Accout Info");
    display(32, 2, "Change Password");      display(53, 2, "(Press \"1\")");
    display(32, 3, "Logout");               display(53, 3, "(Press \"2\")");
    display(32, 4, "Info");                 display(53, 4, "(Press \"3\")");
    display(32, 5, "Back to Main Menu");    display(53, 5, "(Press \"0\")");
    answer = numberPressWait(3, true);
    switch (answer)
    {
    case 0: //back to main menu
        menu(username);
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
    case 3://display version and info
        system("cls");
        ClearConsoleInputBuffer();
        getGameVersion();
        menu(username);
        break;
    default:
        system("cls");
        ClearConsoleInputBuffer();
        display(3, 3, "Invalid input, Please try again...", false);
        system("pause");
        accountInfo(username);
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
    display(44, 1, "Admin Menu of options:");
    display(32, 2, "Change Password");      display(53, 2, "(type number \"1\")");
    display(32, 3, "Logout");               display(53, 3, "(type number \"2\")");
    display(32, 4, "Stats");                display(53, 4, "(type number \"3\")");
    display(32, 5, "Info");                 display(53, 5, "(type number \"4\")");
    display(32, 6, "Test Questing");        display(53, 6, "(type number \"5\")");
    display(32, 7, "Map Test");             display(53, 7, "(type number \"6\")");
    display(32, 8, "Exit");                 display(53, 8, "(type number \"0\")", false);
    
    value = numberPressWait(6, true);
    switch (value)
    {
    case 0: //exit program
        exit(0);
        break;
    case 1: //change password
        //change password
        system("cls");
        account.logonScreen(2);
        break;
    case 2://logout
        system("cls");
        account.logonScreen();
        break;
    case 3://display stats
        system("cls");
        display(3,3,"Please enter the username of the user for which you would like to view stats.");
        display(3,4,">",false,false);
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
    case 5:{ //test Quests
        system("cls");
        Quests tempQuest;
        int tempStep  = numberPressWait(8, true);//enter step number
        tempQuest.quest1(username, tempStep);
        adminMenu(username);
        break;}
    case 6:{
        system("cls");
        Map map;
        map.displayMapOutline();
        waitForEnter(getEnterKeyState());
        break;
    }
    default:
        system("cls");
        display(3,3,"Invalid input, Please try again...", false);
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
        display(3,3,"Please enter a new password for your account");
        display(3,4,"> ", false, false);
        cin >> passwordNew; //get the user's new password
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        int len = sizeof(nonValidPasswordCharacters)/sizeof(nonValidPasswordCharacters[0]); //length of array of non valid password Charaters
        for (int lengthOfArray = len; lengthOfArray >= 0; lengthOfArray--){ //loop through all the nonValidPasswordCharacters to make sure the user is not trying to use any of them.
            if (passwordNew.find(nonValidPasswordCharacters[lengthOfArray]) != std::string::npos || passwordNew.length() < 4 || passwordNew.find(username) != std::string::npos) {
                //found the character
                //password is invalid
                validPassword = false;
                display(3,3,"The password you entered is invalid, Please try a different password.");
                display(3,4,"Note, the password cannot contain: (){}[]|`¬¦! \"£$%^&*\"<>:;#~_-+=,@.");
                display(3,5,"The password must also be atleast 4 charaters in length and not the same as your username.");
                break;
            } else {
                //password does not contain character
                validPassword = true;
            }
        }
        system("cls");
    }
    display(3,3,"Please enter a new password again for your account");
    display(3,4,"> ",false,false);
    cin >> passwordConf;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        
    if (passwordNew == passwordConf){
        server.sendToServer(code.cipher("4", username, passwordNew));
        menu(username);
    } else {
        display(3,3,"Your passwords did not match, please try again...", false);
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
            ClearConsoleInputBuffer();
            return 'y';
        } else if (GetKeyState('y') >= 0 || GetKeyState('Y') >= 0){ // else 1 not pressed
            yKeyPressedLastLoop = false;
        }
        if (GetKeyState('N') < 0 || GetKeyState('n') < 0 && !nKeyPressedLastLoop) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
            nKeyPressedLastLoop = true;
            ClearConsoleInputBuffer();
            return 'n';
        } else if (GetKeyState('n') >= 0 || GetKeyState('n') >= 0){ // else 1 not pressed
            nKeyPressedLastLoop = false;
        }
    }
    ClearConsoleInputBuffer();
}
int Menu::numberPressWait(int maxRange, bool hasZeroOption){ //returns a value based on the key pressed
    bool oneKeyPressedLastLoop = false, twoKeyPressedLastLoop = false, threeKeyPressedLastLoop = false, fourKeyPressedLastLoop = false, fiveKeyPressedLastLoop = false, sixKeyPressedLastLoop = false,sevenKeyPressedLastLoop = false,eightKeyPressedLastLoop = false,nineKeyPressedLastLoop = false, zeroKeyPressedLastLoop = false;
    while (1){
        if (GetKeyState('1') < 0 && !oneKeyPressedLastLoop) { //checks to make sure that the 1 key is pressed and makes sure it was not pressed last check
            oneKeyPressedLastLoop = true;
        } else if (GetKeyState('1') >= 0 && oneKeyPressedLastLoop){ // else 1 not pressed
            oneKeyPressedLastLoop = false;
            return 1;
            break;
        }
        if(maxRange > 1){
            if (GetKeyState('2') < 0 && !twoKeyPressedLastLoop) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
                twoKeyPressedLastLoop = true;
            } else if (GetKeyState('2') >= 0 && twoKeyPressedLastLoop){ // else 2 not pressed
                twoKeyPressedLastLoop = false;
                return 2;
                break;
            }
        }
        if(maxRange > 2){
            if (GetKeyState('3') < 0 && !threeKeyPressedLastLoop) { //checks to make sure that the 3 key is pressed and makes sure it was not pressed last check
                threeKeyPressedLastLoop = true;
            } else if (GetKeyState('3') >= 0 && threeKeyPressedLastLoop){ // else 3 not pressed
                threeKeyPressedLastLoop = false;
                return 3;
                break;
            }
        }
        if(maxRange > 3){
            if (GetKeyState('4') < 0 && !fourKeyPressedLastLoop) { //checks to make sure that the 4 key is pressed and makes sure it was not pressed last check
                fourKeyPressedLastLoop = true;
            } else if (GetKeyState('4') >= 0 && fourKeyPressedLastLoop){ // else 4 not pressed
                fourKeyPressedLastLoop = false;
                return 4;
                break;
            }
        }
        if(maxRange > 4){
            if (GetKeyState('5') < 0 && !fiveKeyPressedLastLoop) { //checks to make sure that the 5 key is pressed and makes sure it was not pressed last check
                fiveKeyPressedLastLoop = true;
            } else if (GetKeyState('5') >= 0 && fiveKeyPressedLastLoop){ // else 5 not pressed
                fiveKeyPressedLastLoop = false;
                return 5;
                break;
            }
        }
        if(maxRange > 5){
            if (GetKeyState('6') < 0 && !sixKeyPressedLastLoop) { //checks to make sure that the 6 key is pressed and makes sure it was not pressed last check
                sixKeyPressedLastLoop = true;
            } else if (GetKeyState('6') >= 0 && sixKeyPressedLastLoop){ // else 6 not pressed
                sixKeyPressedLastLoop = false;
                return 6;
                break;
            }
        }
        if(maxRange > 6){
            if (GetKeyState('7') < 0 && !sevenKeyPressedLastLoop) { //checks to make sure that the 7 key is pressed and makes sure it was not pressed last check
                sevenKeyPressedLastLoop = true;
            } else if (GetKeyState('7') >= 0 && sevenKeyPressedLastLoop){ // else 7 not pressed
                sevenKeyPressedLastLoop = false;
                return 7;
                break;
            }
        }
        if(maxRange > 7){
            if (GetKeyState('8') < 0 && !eightKeyPressedLastLoop) { //checks to make sure that the 8 key is pressed and makes sure it was not pressed last check
                eightKeyPressedLastLoop = true;
            } else if (GetKeyState('8') >= 0 && eightKeyPressedLastLoop){ // else 8 not pressed
                eightKeyPressedLastLoop = false;
                return 8;
                break;
            }
        }
        if(maxRange > 8){
            if (GetKeyState('9') < 0 && !nineKeyPressedLastLoop) { //checks to make sure that the 9 key is pressed and makes sure it was not pressed last check
                nineKeyPressedLastLoop = true;
            } else if (GetKeyState('9') >= 0 && nineKeyPressedLastLoop){ // else 9 not pressed
                nineKeyPressedLastLoop = false;
                return 9;
                break;
            }
        }
        if (hasZeroOption == true){
            if (GetKeyState('0') < 0 && !zeroKeyPressedLastLoop) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
                zeroKeyPressedLastLoop = true;
            } else if (GetKeyState('0') >= 0 && zeroKeyPressedLastLoop){ // else 1 not pressed
                zeroKeyPressedLastLoop = false;
                return  0;
                break;
            }
        }
    }
}
void Menu::waitForEnter(int enterCurrentlyPressed){ //waits for a user to click the enter key
    bool enterKeyPressedLastLoop = false;
    while (1){
        if (GetKeyState(VK_RETURN) < 0 && !enterKeyPressedLastLoop && enterCurrentlyPressed >= 0) { //checks to make sure that the enter key is pressed and makes sure it was not pressed last check
            enterKeyPressedLastLoop = true;
            ClearConsoleInputBuffer();
            return;
        } else if (GetKeyState(VK_RETURN) >= 0){ // else enter not pressed
            enterKeyPressedLastLoop = false;
            enterCurrentlyPressed = 0;
        }
    }
    ClearConsoleInputBuffer();
}
//I am shaking my head at my own function //Lol... You did good...
int Menu::getEnterKeyState(){
    return GetKeyState(VK_RETURN);
}

void Menu::display(int column, int row, string outputString, bool resetCursorPosition, bool addExtraRow) { //sets the display position of the text on the consol (allowing to display anywhere on the consol)
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;

	position.X = column; //column
	position.Y = row; //row

	SetConsoleCursorPosition(screen, position);
	cout << outputString;

    if (resetCursorPosition) {//rest the position to 0, 0 to prevent issues in other text:
        position.X = 0; //column
        position.Y = 0; //row
        SetConsoleCursorPosition(screen, position);
    } else { //set the position to the row following the current
        if(addExtraRow){
            position.X = column; //column
            position.Y = ++row; //row
            SetConsoleCursorPosition(screen, position);
        } else {
            position.X = ++column; //column
            position.Y = row; //row
            SetConsoleCursorPosition(screen, position);
        }
    }
}

string Menu::numberFormatting(double decimalNumber, int numberOfDecimals) { //formats a decimal value to a given number of decimal places and returns it in string form
	stringstream formattedNumber;
	string formatNumberOutput;
	formattedNumber << setprecision(numberOfDecimals) << fixed << showpoint << decimalNumber;
	formattedNumber >> formatNumberOutput;
	return formatNumberOutput;
}

void Menu::setPlayer(TempEntity playerE){
    player = playerE;
}
TempEntity Menu::getPlayer(){
    return player;
}