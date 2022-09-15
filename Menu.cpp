#include <string>
#include <String>
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdio.h>
#include <sstream>

#include "Main.h"
#include "Account.h"
#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Menu.h"
#include "Battle.h"
#include "Map.h"
#include "WorldMap.h"
#include "Quests.h"
#include "DataGuard.h"
#include "Items.h"

#undef min // these are needed for the cin.ignore statments to clear out the buffer for new data.
#undef max 

using namespace std;

Cipher code; //declare the new instance of Cipher class
Account account;
Battle battle;
WorldMap worldMap;
Map map;
Quests quest;

void fnExit(); //prototype from source.cpp

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
    //the following is program close code:
    atexit(fnExit);
    guard.on(username);
    //guard.updateGuardData(getPlayer());
    //end of program close code.

    bool oneKeyPressedLastLoop = false, twoKeyPressedLastLoop = false, threeKeyPressedLastLoop = false, fourKeyPressedLastLoop = false, fiveKeyPressedLastLoop = false, zeroKeyPressedLastLoop = false,
    nKeyPressedLastLoop = false, iKeyPressedLastLoop = false, aKeyPressedLastLoop = false, 
    controlKeyPressedLastLoop = false, altKeyPressedLastLoop = false ,kKeyPressedLastLoop = false;
    int value;
    bool stayInMenu = true;
    while(stayInMenu){
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        display(50, 1, "Menu");
        display(32, 2, "Go Questing");          display(53, 2, "(Press \"1\")");
        display(32, 3, "Travel");               display(53, 3, "(Press \"2\")");
        display(32, 4, "Stats");                display(53, 4, "(Press \"3\")");
        display(32, 5, "Inventory");            display(53, 5, "(Press \"4\")");
        display(32, 6, "Account Info");         display(53, 6, "(Press \"5\")");
        display(32, 7, "Exit");                 display(53, 7, "(Press \"0\")");
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
            if (GetKeyState('5') < 0 && !fiveKeyPressedLastLoop) { //checks to make sure that the 5 key is pressed and makes sure it was not pressed last check
                fiveKeyPressedLastLoop = true;
            } else if (GetKeyState('5') >= 0 && fiveKeyPressedLastLoop){ // else 5 not pressed
                fiveKeyPressedLastLoop = false;
                value = 5;
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
        case 1:{//"Go Questing"//map for traveling and questing 
                //We probably need a separate questing menu
            //Map map;
            display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
            //map.listAvalibleLocations(username);
            quest.setPlayer(player);
            quest.getAvailableQuests();
            setPlayer(quest.getPlayer());
            break;
        }
        case 2://travel option
            display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
            ClearConsoleInputBuffer();
            stillTraveling = true;
            do {
            travelMenu(username);
            } while(stillTraveling);
            break;
        case 3://display stats
            display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
            ClearConsoleInputBuffer();
            displayStats();
            //account.displayStats(username);
            break;
        case 4:{
            displayInventory();
            break;
        }
        case 5:{
            accountInfo(username);
            break;
        }
        case 14:
            display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
            ClearConsoleInputBuffer();
            display(3,3,"October is a Beautiful month to get Married!");
            display(3,4,"Dakota loves Beautiful!", false);
            system("pause");
            break;
        case 15:
            display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
            ClearConsoleInputBuffer();
            exitAdminMenu = false; //logon menu loop variable
            while (!exitAdminMenu) adminMenu(username);
            break;
        default:
            display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
            ClearConsoleInputBuffer();
            display(3, 3, "Invalid input, Please try again...", false);
            system("pause");
            break;
        }
    }
}

void Menu::travelMenu(string username){ //bring up the menu for travel
    display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");

    display(50, 1, "Travel");
    display(16, 2, worldMap.getMapDescription(player.getLocation()));//Dakota please help me load the user's current location
    display(32, 4, "Use Arrow Keys to navegate the Map");
    display(32, 5, "Press 0 to Return to Menu");
    map.displayMapOutline(map.getMapStandardMaxColumn(), map.getMapStandardMaxRow()); //draw the map outline to the screen
    map.fillInMap();
    map.writeLandmarks();
    setStillSimpleTraveling(true);// for the do while loop so we do not have to refresh the whole cmd
    int tempCurrentLocation = -1; //no location
    bool lastLoopFailedTravel = false;
    do{
        if (tempCurrentLocation == -1){
            tempCurrentLocation = map.getCurrentLocation();
            display(map.getPossibleTravelLocationsX(map.getCurrentLocation()), map.getPossibleTravelLocationsY(map.getCurrentLocation()), map.getMapFilled(),true,false, 44);
        } else {
            if (!lastLoopFailedTravel){
                display(map.getPossibleTravelLocationsX(tempCurrentLocation), map.getPossibleTravelLocationsY(tempCurrentLocation), map.getMapUnfilled(), true, false, 44);
                display(map.getPossibleTravelLocationsX(map.getCurrentLocation()), map.getPossibleTravelLocationsY(map.getCurrentLocation()), map.getMapFilled(),true,false, 44);
                tempCurrentLocation = map.getCurrentLocation(); 
            } else {
                for(int i = 0; i <= 50; i+=5){
                    display(i,0, "     ");
                }
                lastLoopFailedTravel = false;
            }
        }
        int value = arrowPressWait(true);
        switch (value){
        case 0://Return to menu
            //menu(username); //causing duplicate menus
            stillTraveling = false;
            setStillSimpleTraveling(false);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            ClearConsoleInputBuffer();
            worldMap.setPlayer(player);
            worldMap.travel(value, lastLoopFailedTravel); //changes current location
            setPlayer(worldMap.getPlayer());
            //cout << "still Traveling? " << getStillSimpleTraveling(); // for testing
            //waitForEnter(getEnterKeyState());// for testing
            //map.setCurrentLocation(1);
            //menu(username);
            break;
        default:
            display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
            ClearConsoleInputBuffer();
            display(3, 3, "menu value somehow set impossibly!", false);
            system("pause");
            //menu(username);
            break;
        }
    } while (getStillSimpleTraveling());
    
}

void Menu::displayStats(){
    Items itemHandler;
    string physicalDamageAbilities = "Physical Damage Abilities: ";
    string magicDamageAbilities = "Magic Damage Abilities: ";
    string psychicDamageAbilities = "Psychic Damage Abilities: ";
    if (player.getQDamageType() == "Physical") physicalDamageAbilities += " Q";
    else if (player.getQDamageType() == "Psychic") psychicDamageAbilities += " Q";
    else magicDamageAbilities += " Q";
    if (player.getWDamageType() == "Physical") physicalDamageAbilities += " W";
    else if (player.getWDamageType() == "Psychic") psychicDamageAbilities += " W";
    else magicDamageAbilities += " W";
    if (player.getEDamageType() == "Physical") physicalDamageAbilities += " E";
    else if (player.getEDamageType() == "Psychic") psychicDamageAbilities += " E";
    else magicDamageAbilities += " E";
    if (player.getRDamageType() == "Physical") physicalDamageAbilities += " R";
    else if (player.getRDamageType() == "Psychic") psychicDamageAbilities += " R";
    else magicDamageAbilities += " R";

    stringstream currentXP, totalXP;
    currentXP << fixed << setprecision(0) << player.getCurrentXP(); //format the XP
    totalXP << fixed << setprecision(0) << player.getXPForNextLevel(); //format the XP
    string currentXPFormatted = currentXP.str();
    string totalXPFormatted = totalXP.str();
    string playerLevelInfo = "Player Level: " + to_string(player.getLevel()) +  " With " + currentXPFormatted + "XP of " + totalXPFormatted + "XP";
    string healthString = to_string(player.getHealth()) + " / " + to_string(player.getMaxHealth());
    string mindString = to_string(player.getMind()) + " / " + to_string(player.getMaxMind());
    string physicalDamageString = to_string(player.getPhysicalDamageMin()) + " - " + to_string(player.getPhysicalDamageMax());
    string magicDamageString = to_string(player.getMagicDamageMin()) + " - " + to_string(player.getMagicDamageMax());
    string psychicDamageString = to_string(player.getPsychicDamageMin()) + " - " + to_string(player.getPsychicDamageMax());

    display(0, 0, "Your stats are as follows:\n");
    cout << "\n" << setfill('=') << setw(92) << "=";
    display(0, 2, "Health:");               display(42 - healthString.size(), 2, healthString);
    display(48, 2, playerLevelInfo);        display(48, 3, "Player Race: " + player.getRace());
    cout << "\n\n\n" << setfill('-') << setw(42) << "-";
    display(0, 4, "Armor:");                display(42 - to_string(player.getArmor()).size(), 4, to_string(player.getArmor()));
    display(48, 4, "Player Kit: " + player.getKit()); display(48, 5, "Primary Weapon: " + itemHandler.getName(player.getPrimaryHand()));
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
    display(0, 18, "NaturalEnergy:");                display(42 - to_string(player.getNaturalEnergy()).size(), 18, to_string(player.getNaturalEnergy()));
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << setfill('-') << setw(42) << "-";
    display(0, 20, "Mind:");                display(42 - mindString.size(), 20, mindString);
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << setfill('-') << setw(42) << "-";
    display(0, 22, "Psychic Damage:");      display(42 - psychicDamageString.size(), 22, psychicDamageString);
    display(48, 22, psychicDamageAbilities);
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
        << "NaturalEnergy: " << setfill(' ') << setw(36) << player.getNaturalEnergy() << endl << setfill('-') << setw(42) << "-" << endl; //This cout statement prints out all the stats for the user to see.
    */

    system("pause");    
}
void Menu::displayInventory(){
    Items itemHandler;
    bool keepLooping = false;
    do{
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        ClearConsoleInputBuffer();
        display(1, 1, "You are carrying the following:");                                   display(64, 1, "You can:");
        display(1, 2, "Main Hand: " + itemHandler.getName(player.getPrimaryHand()));        display(64, 2, "Move Weapon to Primary Hand (Press \"1\")");
        display(1, 3, "Off Hand: " + itemHandler.getName(player.getOffHand()));             display(64, 3, "Move Weapon to Off Hand     (Press \"2\")");
        display(1, 5, "Pack:");                                                             display(64, 4, "Exit                        (Press \"0\")");
        for(int i = 0; i < player.getInventorySize(); i++){
            if(player.getInventory(i) == 0){
                if(i == 0){
                    display(1, 6, "Empty", false);
                }
                i = 24;
            }else{
                display(1, 6 + i, itemHandler.getName(player.getInventory(i)), false);
            }        
        }

        int choice = numberPressWait(2, true);
        if(choice == 1 || choice == 2){
            int items = 0;
            keepLooping = true;
            display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
            ClearConsoleInputBuffer();
            display(1, 1, "Trade which item?");
            for(int i = 0; i < 8; i++){
                display(1, 2 + i, itemHandler.getName(player.getInventory(i))); display(32, 2 + i, ("Press \"" + to_string(i + 1) + "\""));
                items++;
                if(player.getInventory(i) == 0){
                    i = 24;
                }
            }
            display(24, 2 + items, "Cancel: Press \"0\"");
            int choice2 = numberPressWait(items, true);
            if(choice2 == 0){

            }else{
                int tempItem;
                tempItem = (choice == 1) ? player.getPrimaryHand() : player.getOffHand();
                (choice == 1) ? player.setPrimaryHand(player.getInventory(choice2 - 1)) : player.setOffHand(player.getInventory(choice2 - 1));
                player.setInventory(choice2 - 1, tempItem);
                player.sortInventory();
            }
        }else{
            keepLooping = false;
        }
    }while(keepLooping);
}

void Menu::accountInfo(string username){
    int answer;
    display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
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
        //menu(username); //causing duplicate menus
        break;
    case 1: //change password
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        ClearConsoleInputBuffer();
        account.logonScreen(2);
        break;
    case 2://logout
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        ClearConsoleInputBuffer();
        account.logonScreen();
        break;
    case 3://display version and info
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        ClearConsoleInputBuffer();
        getGameVersion();
        //menu(username);
        break;
    default:
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
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
    display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    int value;
    bool oneKeyPressedLastLoop = false, twoKeyPressedLastLoop = false, threeKeyPressedLastLoop = false, fourKeyPressedLastLoop = false, fiveKeyPressedLastLoop = false, 
    zeroKeyPressedLastLoop = false, nKeyPressedLastLoop = false, iKeyPressedLastLoop = false, aKeyPressedLastLoop = false, controlKeyPressedLastLoop = false, 
    altKeyPressedLastLoop = false ,kKeyPressedLastLoop = false;
    display(50, 1, "Admin Menu of options:");
    display(32, 2, "Change Password");          display(63, 2, "(type number \"1\")");
    display(32, 3, "Logout");                   display(63, 3, "(type number \"2\")");
    display(32, 4, "Stats");                    display(63, 4, "(type number \"3\")");
    display(32, 5, "Info");                     display(63, 5, "(type number \"4\")");
    display(32, 6, "Test Questing");            display(63, 6, "(type number \"5\")");
    display(32, 7, "Map Test");                 display(63, 7, "(type number \"6\")");
    display(32, 8, "Message Test SubCipher");   display(63, 8, "(type number \"7\")");
    display(32, 9, "Show Text Color");          display(63, 9, "(type number \"8\")");
    display(32, 10, "Exit Admin Menu");         display(63, 10, "(type number \"0\")", false);
    
    value = numberPressWait(8, true);
    switch (value)
    {
    case 0: //exit admin menu program
        //exit(0); //no longer end program
        exitAdminMenu = true; //exit the admin menu
        break;
    case 1: //change password
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        account.logonScreen(2);
        break;
    case 2://logout
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        account.logonScreen();
        break;
    case 3://display stats
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        display(3,3,"Please enter the username of the user for which you would like to view stats.");
        display(3,4,">",false,false);
        cin >> usernameE;
        account.displayStats(usernameE, 1, username);
        usernameE = "";
        //adminMenu(username);
        break;
    case 4://display version and info
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        getGameVersion();
        //adminMenu(username);
        break;
    case 5:{ //test Quests
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        Quests tempQuest;
        int tempStep  = numberPressWait(8, true);//enter step number
        tempQuest.quest1(username, tempStep);
        //adminMenu(username);
        break;}
    case 6:{
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        //Map map;
        map.displayMapOutline(map.getMapStandardMaxColumn(), map.getMapStandardMaxRow());
        waitForEnter(getEnterKeyState());
        break;
    }
    case 7:{
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        ReachOutToServer serverMessage;
        string output;
        cout << serverMessage.sendToServer(code.cipher("22", code.subCipher("2test1","2test2","2test3","2test4","2test5","2test6","2test7","2test8","2test9","2test10","2test11","2test12","2test13","2test14","2test15","2test16","2test17","2test18","2test19","2test20","2test21","2test22")/**/, code.subCipher("3test1","3test2","3test3","3test4","3test5","3test6","3test7","3test8","3test9","3test10","3test11","3test12","3test13","3test14","3test15","3test16","3test17","3test18","3test19","3test20","3test21","3test22"), code.subCipher("4test1","4test2","4test3","4test4","4test5","4test6","4test7","4test8","4test9","4test10","4test11","4test12","4test13","4test14","4test15","4test16","4test17","4test18","4test19","4test20","4test21","4test22"), code.subCipher("5test1","5test2","5test3","5test4","5test5","5test6","5test7","5test8","5test9","5test10","5test11","5test12","5test13","5test14","5test15","5test16","5test17","5test18","5test19","5test20","5test21","5test22"), code.subCipher("6test1","6test2","6test3","6test4","6test5","6test6","6test7","6test8","6test9","6test10","6test11","6test12","6test13","6test14","6test15","6test16","6test17","6test18","6test19","6test20","6test21","6test22"), code.subCipher("7test1","7test2","7test3","7test4","7test5","7test6","7test7","7test8","7test9","7test10","7test11","7test12","7test13","7test14","7test15","7test16","7test17","7test18","7test19","7test20","7test21","7test22"), code.subCipher("8test1","8test2","8test3","8test4","8test5","8test6","8test7","8test8","8test9","8test10","8test11","8test12","8test13","8test14","8test15","8test16","8test17","8test18","8test19","8test20","8test21","8test22"), code.subCipher("9test1","9test2","9test3","9test4","9test5","9test6","9test7","9test8","9test9","9test10","9test11","9test12","9test13","9test14","9test15","9test16","9test17","9test18","9test19","9test20","9test21","9test22"), code.subCipher("10test1","10test2","10test3","10test4","10test5","10test6","10test7","10test8","10test9","10test10","10test11","10test12","10test13","10test14","10test15","10test16","10test17","10test18","10test19","10test20","10test21","10test22"), code.subCipher("11test1","11test2","11test3","11test4","11test5","11test6","11test7","11test8","11test9","11test10","11test11","11test12","11test13","11test14","11test15","11test16","11test17","11test18","11test19","11test20","11test21","11test22"), code.subCipher("12test1","12test2","12test3","12test4","12test5","12test6","12test7","12test8","12test9","12test10","12test11","12test12","12test13","12test14","12test15","12test16","12test17","12test18","12test19","12test20","12test21","12test22"), code.subCipher("13test1","13test2","13test3","13test4","13test5","13test6","13test7","13test8","13test9","13test10","13test11","13test12","13test13","13test14","13test15","13test16","13test17","13test18","13test19","13test20","13test21","13test22"), code.subCipher("14test1","14test2","14test3","14test4","14test5","14test6","14test7","14test8","14test9","14test10","14test11","14test12","14test13","14test14","14test15","14test16","14test17","14test18","14test19","14test20","14test21","14test22"), code.subCipher("15test1","15test2","15test3","15test4","15test5","15test6","15test7","15test8","15test9","15test10","15test11","15test12","15test13","15test14","15test15","15test16","15test17","15test18","15test19","15test20","15test21","15test22"), code.subCipher("16test1","16test2","16test3","16test4","16test5","16test6","16test7","16test8","16test9","16test10","16test11","16test12","16test13","16test14","16test15","16test16","16test17","16test18","16test19","16test20","16test21","16test22"), code.subCipher("17test1","17test2","17test3","17test4","17test5","17test6","17test7","17test8","17test9","17test10","17test11","17test12","17test13","17test14","17test15","17test16","17test17","17test18","17test19","17test20","17test21","17test22"), code.subCipher("18test1","18test2","18test3","18test4","18test5","18test6","18test7","18test8","18test9","18test10","18test11","18test12","18test13","18test14","18test15","18test16","18test17","18test18","18test19","18test20","18test21","18test22"), code.subCipher("19test1","19test2","19test3","19test4","19test5","19test6","19test7","19test8","19test9","19test10","19test11","19test12","19test13","19test14","19test15","19test16","19test17","19test18","19test19","19test20","19test21","19test22"), code.subCipher("20test1","20test2","20test3","20test4","20test5","20test6","20test7","20test8","20test9","20test10","20test11","20test12","20test13","20test14","20test15","20test16","20test17","20test18","20test19","20test20","20test21","20test22"), code.subCipher("21test1","21test2","21test3","21test4","21test5","21test6","21test7","21test8","21test9","21test10","21test11","21test12","21test13","21test14","21test15","21test16","21test17","21test18","21test19","21test20","21test21","21test22"), code.subCipher("22test1","22test2","22test3","22test4","22test5","22test6","22test7","22test8","22test9","22test10","22test11","22test12","22test13","22test14","22test15","22test16","22test17","22test18","22test19","22test20","22test21","22test22")/**/));
        //display(2,2, output, false, true);
        system("pause");
        break;
    }
    case 8:{
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        // you can loop k higher to see more color choices
        for(int k = 1; k < 255; k++)
        {
            // pick the colorattribute k you want
            SetConsoleTextAttribute(hConsole, k);
            cout << k << " I want to be nice today!" << endl;
        }
        system("pause");
        break;
    }
    default:
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        display(3,3,"Invalid input, Please try again...", false);
        system("pause");
        //adminMenu(username);
        break;
    }
}

void Menu::changePass(string username){ //changes the users password
    display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
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
                display(3,5,"The password must also be atleast 4 charaters in length and not the same as your username.", false, true);
                system("pause");
                break;
            } else {
                //password does not contain character
                validPassword = true;
            }
        }
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
    }
    display(3,3,"Please enter a new password again for your account");
    display(3,4,"> ",false,false);
    cin >> passwordConf;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
    
        
    if (passwordNew == passwordConf){
        server.sendToServer(code.cipher("4", username, passwordNew));
        //menu(username);
    } else {
        display(3,3,"Your passwords did not match, please try again...", false);
        system("pause");
        display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
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
int Menu::numberPressWaitSpecial(int maxRange, char key1, char key2, char key3, char key4, char key5, char key6, char key7, bool hasZeroOption){ //returns a value based on the key pressed
    bool oneKeyPressedLastLoop = false, twoKeyPressedLastLoop = false, threeKeyPressedLastLoop = false, fourKeyPressedLastLoop = false, fiveKeyPressedLastLoop = false, sixKeyPressedLastLoop = false,sevenKeyPressedLastLoop = false,eightKeyPressedLastLoop = false,nineKeyPressedLastLoop = false, zeroKeyPressedLastLoop = false;
    bool keyOnePressedLastLoop = false, keyTwoPressedLastLoop = false, keyThreePressedLastLoop = false, keyFourPressedLastLoop = false, keyFivePressedLastLoop = false, keySixPressedLastLoop = false, keySevenPressedLastLoop = false;

    while (1){
        if (key1 != 0 && key2 != 0 && key3 != 0 && key4 != 0 && key5 != 0 && key6 != 0 && key7 != 0){
            if (GetAsyncKeyState(key1) < 0 && !keyOnePressedLastLoop) { //checks to make sure that the special keys are pressed and makes sure it was not pressed last check
                keyOnePressedLastLoop = true;
            } else if (GetAsyncKeyState(key2) < 0 && !keyTwoPressedLastLoop){
                keyTwoPressedLastLoop = true;
            } else if (GetAsyncKeyState(key3) < 0 && !keyThreePressedLastLoop){
                keyThreePressedLastLoop = true;
            } else if (GetAsyncKeyState(key4) < 0 && !keyFourPressedLastLoop){
                keyFourPressedLastLoop = true;
            } else if (GetAsyncKeyState(key5) < 0 && !keyFivePressedLastLoop){
                keyFivePressedLastLoop = true;
            } else if (GetAsyncKeyState(key6) < 0 && !keySixPressedLastLoop){
                keySixPressedLastLoop = true;
            } else if (GetAsyncKeyState(key7) < 0 && !keySevenPressedLastLoop){
                keySevenPressedLastLoop = true;
            }
            if (keyOnePressedLastLoop && keyTwoPressedLastLoop && keyThreePressedLastLoop && keyFourPressedLastLoop && keyFivePressedLastLoop && keySixPressedLastLoop && keySevenPressedLastLoop) return 100; //if all keys have been pressed at some point without letting up on all of them they are good. 
        } else if (key1 != 0 && key2 != 0 && key3 != 0 && key4 != 0 && key5 != 0 && key6 != 0){
            if (GetAsyncKeyState(key1) < 0 && !keyOnePressedLastLoop) { //checks to make sure that the special keys are pressed and makes sure it was not pressed last check
                keyOnePressedLastLoop = true;
            } else if (GetAsyncKeyState(key2) < 0 && !keyTwoPressedLastLoop){
                keyTwoPressedLastLoop = true;
            } else if (GetAsyncKeyState(key3) < 0 && !keyThreePressedLastLoop){
                keyThreePressedLastLoop = true;
            } else if (GetAsyncKeyState(key4) < 0 && !keyFourPressedLastLoop){
                keyFourPressedLastLoop = true;
            } else if (GetAsyncKeyState(key5) < 0 && !keyFivePressedLastLoop){
                keyFivePressedLastLoop = true;
            } else if (GetAsyncKeyState(key6) < 0 && !keySixPressedLastLoop){
                keySixPressedLastLoop = true;
            }
            if (keyOnePressedLastLoop && keyTwoPressedLastLoop && keyThreePressedLastLoop && keyFourPressedLastLoop && keyFivePressedLastLoop && keySixPressedLastLoop) return 100; //if all keys have been pressed at some point without letting up on all of them they are good. 
        } else if (key1 != 0 && key2 != 0 && key3 != 0 && key4 != 0 && key5 != 0){
            if (GetAsyncKeyState(key1) < 0 && !keyOnePressedLastLoop) { //checks to make sure that the special keys are pressed and makes sure it was not pressed last check
                keyOnePressedLastLoop = true;
            } else if (GetAsyncKeyState(key2) < 0 && !keyTwoPressedLastLoop){
                keyTwoPressedLastLoop = true;
            } else if (GetAsyncKeyState(key3) < 0 && !keyThreePressedLastLoop){
                keyThreePressedLastLoop = true;
            } else if (GetAsyncKeyState(key4) < 0 && !keyFourPressedLastLoop){
                keyFourPressedLastLoop = true;
            } else if (GetAsyncKeyState(key5) < 0 && !keyFivePressedLastLoop){
                keyFivePressedLastLoop = true;
            }
            if (keyOnePressedLastLoop && keyTwoPressedLastLoop && keyThreePressedLastLoop && keyFourPressedLastLoop && keyFivePressedLastLoop) return 100; //if all keys have been pressed at some point without letting up on all of them they are good. 

        } else if (key1 != 0 && key2 != 0 && key3 != 0 && key4 != 0){
            if (GetAsyncKeyState(key1) < 0 && !keyOnePressedLastLoop) { //checks to make sure that the special keys are pressed and makes sure it was not pressed last check
                keyOnePressedLastLoop = true;
            } else if (GetAsyncKeyState(key2) < 0 && !keyTwoPressedLastLoop){
                keyTwoPressedLastLoop = true;
            } else if (GetAsyncKeyState(key3) < 0 && !keyThreePressedLastLoop){
                keyThreePressedLastLoop = true;
            } else if (GetAsyncKeyState(key4) < 0 && !keyFourPressedLastLoop){
                keyFourPressedLastLoop = true;
            }
            if (keyOnePressedLastLoop && keyTwoPressedLastLoop && keyThreePressedLastLoop && keyFourPressedLastLoop) return 100; //if all keys have been pressed at some point without letting up on all of them they are good.
        } else if (key1 != 0 && key2 != 0 && key3 != 0){
            if ( GetKeyState(key1) < 0 && GetKeyState(key2) < 0 && GetKeyState(key3) < 0) { //checks to make sure that the special keys are pressed and makes sure it was not pressed last check
                keyOnePressedLastLoop = keyTwoPressedLastLoop = keyThreePressedLastLoop = keyFourPressedLastLoop = keyFivePressedLastLoop = keySixPressedLastLoop = keySevenPressedLastLoop = true;
                return 100;
            } else if (GetKeyState(key1) >= 0 || GetKeyState(key2) >= 0 || GetKeyState(key3) >= 0){ // else special keys are not pressed
                keyOnePressedLastLoop = keyTwoPressedLastLoop = keyThreePressedLastLoop = keyFourPressedLastLoop = keyFivePressedLastLoop = keySixPressedLastLoop = keySevenPressedLastLoop = false;
            }
        } else if (key1 != 0 && key2 != 0){
            if ( GetKeyState(key1) < 0 && GetKeyState(key2) < 0) { //checks to make sure that the special keys are pressed and makes sure it was not pressed last check
                keyOnePressedLastLoop = keyTwoPressedLastLoop = keyThreePressedLastLoop = keyFourPressedLastLoop = keyFivePressedLastLoop = keySixPressedLastLoop = keySevenPressedLastLoop = true;
                return 100;
            } else if (GetKeyState(key1) >= 0 || GetKeyState(key2) >= 0){ // else special keys are not pressed
                keyOnePressedLastLoop = keyTwoPressedLastLoop = keyThreePressedLastLoop = keyFourPressedLastLoop = keyFivePressedLastLoop = keySixPressedLastLoop = keySevenPressedLastLoop = false;
            }
        } else if(key1 != 0){
            if ( GetKeyState(key1) < 0 && !keyOnePressedLastLoop) { //checks to make sure that the special key one is pressed and makes sure it was not pressed last check
                keyOnePressedLastLoop = keyTwoPressedLastLoop = keyThreePressedLastLoop = keyFourPressedLastLoop = keyFivePressedLastLoop = keySixPressedLastLoop = keySevenPressedLastLoop = true;
            } else if (GetKeyState(key1) >= 0 && keyOnePressedLastLoop){ // else special key one not pressed
                keyOnePressedLastLoop = keyTwoPressedLastLoop = keyThreePressedLastLoop = keyFourPressedLastLoop = keyFivePressedLastLoop = keySixPressedLastLoop = keySevenPressedLastLoop = false;
                return 100;
            }
        }







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
int Menu::arrowPressWait(bool hasZeroOption){ //returns a value based on the key pressed
    bool upKeyPressedLastLoop = false, rightKeyPressedLastLoop = false, downKeyPressedLastLoop = false, leftKeyPressedLastLoop = false, zeroKeyPressedLastLoop = false;
    while (1){
        if (GetKeyState(VK_UP) < 0 && !upKeyPressedLastLoop) { //checks to make sure that the VK_UP key is pressed and makes sure it was not pressed last check
            upKeyPressedLastLoop = true;
        } else if (GetKeyState(VK_UP) >= 0 && upKeyPressedLastLoop){ // else VK_UP not pressed
            upKeyPressedLastLoop = false;
            return 1;
            break;
        }
        if (GetKeyState(VK_RIGHT) < 0 && !rightKeyPressedLastLoop) { //checks to make sure that the 2 key is pressed and makes sure it was not pressed last check
            rightKeyPressedLastLoop = true;
        } else if (GetKeyState(VK_RIGHT) >= 0 && rightKeyPressedLastLoop){ // else 2 not pressed
            rightKeyPressedLastLoop = false;
            return 2;
            break;
        }
        if (GetKeyState(VK_DOWN) < 0 && !downKeyPressedLastLoop) { //checks to make sure that the 3 key is pressed and makes sure it was not pressed last check
            downKeyPressedLastLoop = true;
        } else if (GetKeyState(VK_DOWN) >= 0 && downKeyPressedLastLoop){ // else 3 not pressed
            downKeyPressedLastLoop = false;
            return 3;
            break;
        }
        if (GetKeyState(VK_LEFT) < 0 && !leftKeyPressedLastLoop) { //checks to make sure that the 4 key is pressed and makes sure it was not pressed last check
            leftKeyPressedLastLoop = true;
        } else if (GetKeyState(VK_LEFT) >= 0 && leftKeyPressedLastLoop){ // else 4 not pressed
            leftKeyPressedLastLoop = false;
            return 4;
            break;
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

void Menu::display(int column, int row, string outputString, bool resetCursorPosition, bool addExtraRow, int color) { //sets the display position of the text on the consol (allowing to display anywhere on the consol)
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
    // pick the colorattribute k you want
    SetConsoleTextAttribute(screen, color);

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

void Menu::display(int column, int row, std::string outputString, int lengthOfString, bool resetCursorPosition, bool addExtraRow){
    display(column, row, outputString, resetCursorPosition, addExtraRow);
    display(column+lengthOfString, row, " ", resetCursorPosition, addExtraRow);
}

void Menu::clearDisplayRow(int row){
    for(int i = 0; i <= 200; i++){
    display(i, row, " ", true, false);
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