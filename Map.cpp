#include <string>
#include <iostream>
#include "Map.h"
#include "Menu.h"
#include "Account.h"
#include "Battle.h"
#include "Quests.h"

using namespace std;

void Map::listAvalibleLocations(string username){
    Menu menu;
    Account account;
    Battle battle;
    int currentLevel = account.getLevel(username);
    int unlockedLocationsNum = 1;
    system("cls");
    menu.display(3,1, "Please select a place to go Questing by typing the corresponding number.");
    menu.display(3,2, "1 - Basic Fights");
    if (currentLevel >= 3) {
        menu.display(3,3, "2 - Capital Fights");
        unlockedLocationsNum++;
    }
    if (currentLevel >= 7) {
        menu.display(3,4, "3 - Cage Fights");
        unlockedLocationsNum++;
    }
    if (currentLevel >= 10) {
        menu.display(3,5, "4 - Boss Fights (Honestly Suicide...)");
        unlockedLocationsNum++;
    }
    if (currentLevel >= 25) {
        menu.display(3,6, "5 - City of Treck");
        unlockedLocationsNum++;
    }
    if (currentLevel >= 50) {
        menu.display(3,7, "6 - City of Brime");
        unlockedLocationsNum++;
    }
    if (currentLevel >= 60) {
        menu.display(3,8, "7 - City of Kelp");
        unlockedLocationsNum++;
    }
    if (currentLevel >= 80) {
        menu.display(3,9, "8 - City of Correr");
        unlockedLocationsNum++;
    }
    if (currentLevel >= 100) {
        menu.display(3,10, "9 - Monster City (A.K.A. End Times City)");
        unlockedLocationsNum++;
    }
    menu.display(3,11,"0 - Back to Menu");
    menu.display(3,12,"> ", false, false);
    int answer = menu.numberPressWait(unlockedLocationsNum, true);
    //start battle
    if (answer == 0){
        menu.menu(username);
    } else{
        Quests quests;
        switch(answer){ //need battle groups for this to work:
            case 1:
                quests.getAvailableQuests(username, 1);
                /*system("cls");
                menu.ClearConsoleInputBuffer();
                battle.startBattle(username);
                break;*/
            case 2:
                quests.getAvailableQuests(username, 2);
                break;
            case 3:
                quests.getAvailableQuests(username, 3);
                break;
            case 4:
                quests.getAvailableQuests(username, 4);
                break;
            case 5:
                quests.getAvailableQuests(username, 5);
                break;
            case 6:
                quests.getAvailableQuests(username, 6);
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            default:
                menu.display(3,0,"Failed Battle Selection...");
                system("pause");
                break;
        }
    }
}

