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
                quests.doQuest(username, answer, 1);
                /*system("cls");
                menu.ClearConsoleInputBuffer();
                battle.startBattle(username);*/
                break;
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

void Map::displayMapOutline(){
    Menu menu;
    maxColumn = 170; //was 210
    maxRow = 42; //was 62
    int initalPosRow = minRow = 1;
    int initalPosColumn = minColumn = 2;
    menu.display(initalPosColumn,initalPosRow,"+");
    for (int posRow = initalPosRow+1; posRow < maxRow; posRow++){
        menu.display(initalPosColumn,posRow,"|");
    }
    menu.display(initalPosColumn,maxRow,"+");
    for (int posColumn = initalPosColumn+1; posColumn < maxColumn; posColumn++){
        menu.display(posColumn,maxRow,"-");
    }
    menu.display(maxColumn, maxRow,"+");
    for (int posRow = maxRow-1; initalPosRow < posRow; posRow--){
        menu.display(maxColumn,posRow,"|");
    }
    menu.display(maxColumn, initalPosRow,"+");
    for (int posColumn = maxColumn-1; initalPosColumn < posColumn; posColumn--){
        menu.display(posColumn,initalPosRow,"-");
    }
}

void Map::displayLocations(){
    int const tempmaxRow = maxRow;
    int pos[tempmaxRow][2];
    int value = 1;
    //main island asci data:
    pos[value][1] = 80;
    pos[value++][0] = 70;
    pos[value][1] = 90;
    pos[value++][0] = 60;
    pos[value][1] = 100;
    pos[value++][0] = 50;
    pos[value][1] = 105;
    pos[value++][0] = 47;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 45;
    pos[value][1] = 105;
    pos[value++][0] = 50;
    pos[value][1] = 103;
    pos[value++][0] = 55;
    pos[value][1] = 102;
    pos[value++][0] = 58;
    pos[value][1] = 100;
    pos[value++][0] = 66;
    pos[value][1] = 100;
    pos[value++][0] = 70;
    pos[value][1] = 100;
    pos[value++][0] = 70;
    pos[value][1] = 100;
    pos[value++][0] = 60;
    pos[value][1] = 100;
    pos[value++][0] = 60;
    pos[value][1] = 100;
    pos[value++][0] = 60;
    pos[value][1] = 94;
    pos[value++][0] = 71;
    pos[value][1] = 96;
    pos[value++][0] = 70;
    pos[value][1] = 100;
    pos[value++][0] = 67;
    pos[value][1] = 95;
    pos[value++][0] = 69;
    pos[value][1] = 94;
    pos[value++][0] = 68;
    pos[value][1] = 89;
    pos[value++][0] = 70;
    pos[value][1] = 90;
    pos[value++][0] = 69;
    pos[value][1] = 87;
    pos[value++][0] = 70;
    pos[value][1] = 80;
    pos[value++][0] = 73;
    pos[value][1] = 80;
    pos[value++][0] = 74;
    pos[value][1] = 80;
    pos[value++][0] = 75;
    while (value < maxRow) {
        pos[value][1] = maxColumn - 1;//-1 for the inside of the outline
        pos[value++][0] = minColumn + 1;//+1 for the inside of the outline
    }

    Menu menu;
    //starting from top to bottom for the first number and left to right for the second number in pos1_1 - pos#_# 
    int posRow = minRow; //+1 for the inside of the outline
    for (int rowCount = minRow+1; rowCount < maxRow; rowCount++){ //added 1 to the minRow since this will then keep the output inside the outline
        int currentPos = pos[rowCount][0];
        //int currentPos = 5;
        while (currentPos <= pos[rowCount][1]){
            menu.display(currentPos, rowCount, "O");
            currentPos++;
        }
    }
}

void Map::displayLocations(int city){
    switch(city){
        case 1:
            break;
        case 2:
            break;
        default:
            break;

    }
}

void Map::displayLocations(int city, int town){
    
}