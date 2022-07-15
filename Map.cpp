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
    int pos[tempmaxRow][6];
    int value = 2;
    for (int i = 0; i <= tempmaxRow; i++){ //set all values to null before setting
        pos[i][5] = 0;
        pos[i][4] = 0;
        pos[i][3] = 0;
        pos[i][2] = 0;
        pos[i][1] = 0;
        pos[i][0] = 0;
    }
    //main island asci data:
    pos[value][1] = 34+50;
    pos[value++][0] = 34+50;
    pos[value][1] = 35+50;
    pos[value++][0] = 28+50;
    pos[value][1] = 36+50;
    pos[value++][0] = 26+50;
    pos[value][1] = 42+50;
    pos[value++][0] = 26+50;
    pos[value][1] = 43+50;
    pos[value++][0] = 24+50;
    pos[value][1] = 44+50;
    pos[value++][0] = 23+50;
    pos[value][1] = 45+50;
    pos[value++][0] = 21+50;
    pos[value][1] = 47+50;
    pos[value++][0] = 19+50;
    pos[value][1] = 48+50;
    pos[value++][0] = 18+50;
    pos[value][1] = 50+50;
    pos[value++][0] = 17+50;
    pos[value][1] = 51+50;
    pos[value++][0] = 18+50;
    pos[value][1] = 52+50;
    pos[value++][0] = 19+50;
    pos[value][1] = 53+50;
    pos[value++][0] = 19+50;
    pos[value][1] = 54+50;
    pos[value++][0] = 18+50;
    pos[value][1] = 55+50;
    pos[value++][0] = 18+50;
    pos[value][1] = 57+50;
    pos[value++][0] = 17+50;
    pos[value][1] = 58+50;
    pos[value++][0] = 17+50;
    pos[value][3] = 58+50;
    pos[value][2] = 37+50;
    pos[value][1] = 34+50;
    pos[value++][0] = 17+50;
    pos[value][5] = 60+50;
    pos[value][4] = 42+50;
    pos[value][3] = 40+50;
    pos[value][2] = 39+50;
    pos[value][1] = 34+50;
    pos[value++][0] = 17+50;
    pos[value][5] = 60+50;
    pos[value][4] = 56+50;
    pos[value][3] = 54+50;
    pos[value][2] = 42+50;
    pos[value][1] = 34+50;
    pos[value++][0] = 17+50;
    pos[value][5] = 61+50;
    pos[value][4] = 57+50;
    pos[value][3] = 54+50;
    pos[value][2] = 44+50;
    pos[value][1] = 34+50;
    pos[value++][0] = 18+50;
    pos[value][5] = 61+50;
    pos[value][4] = 59+50;
    pos[value][3] = 54+50;
    pos[value][2] = 46+50;
    pos[value][1] = 34+50;
    pos[value++][0] = 20+50;
    pos[value][3] = 51+50;
    pos[value][2] = 47+50;
    pos[value][1] = 33+50;
    pos[value++][0] = 20+50;
    pos[value][1] = 34+50;
    pos[value++][0] = 20+50;
    pos[value][1] = 35+50;
    pos[value++][0] = 20+50;
    pos[value][1] = 35+50;
    pos[value++][0] = 22+50;
    pos[value][1] = 36+50;
    pos[value++][0] = 22+50;
    pos[value][1] = 37+50;
    pos[value++][0] = 23+50;
    pos[value][1] = 38+50;
    pos[value++][0] = 23+50;
    pos[value][1] = 39+50;
    pos[value++][0] = 24+50;
    pos[value][1] = 39+50;
    pos[value++][0] = 24+50;
    pos[value][1] = 40+50;
    pos[value++][0] = 24+50;
    pos[value][1] = 40+50;
    pos[value++][0] = 25+50;
    pos[value][1] = 37+50;
    pos[value++][0] = 25+50;
    pos[value][1] = 33+50;
    pos[value++][0] = 26+50;
    pos[value][1] = 31+50;
    pos[value++][0] = 28+50;
    pos[value][1] = 31+50;
    pos[value++][0] = 29+50;
    pos[value][1] = 31+50;
    pos[value++][0] = 30+50;
    pos[value][1] = 32+50;
    pos[value++][0] = 30+50;
    while (value < maxRow) {
        pos[value][1] = maxColumn - 1;//-1 for the inside of the outline
        pos[value++][0] = maxColumn;//+1 for the inside of the outline //was minColumn + 1 to fill the entire row
    }

    Menu menu;
    //starting from top to bottom for the first number and left to right for the second number in pos1_1 - pos#_# 
    int posRow = minRow; //+1 for the inside of the outline
    for (int rowCount = minRow+1; rowCount < maxRow; rowCount++){ //added 1 to the minRow since this will then keep the output inside the outline
        int currentPos = pos[rowCount][0];
        int lastInput1_0 = 2;
        //int currentPos = 5;
        while (currentPos <= pos[rowCount][1]){

            if (lastInput1_0 == 2){ //used to put spaces between the 0's to spread out the look of the map
                menu.display(currentPos, rowCount, "0");
                lastInput1_0 = 0;
            } else {
                menu.display(currentPos, rowCount, " ");
                lastInput1_0++;
            }
            currentPos++;
        }
        //menu.display(15, 0, "Part 1"); //writes the 2nd portion of the map
        if(pos[rowCount][2] != 0){
            int currentPos2 = pos[rowCount][2];
            while (currentPos2 <= pos[rowCount][3]){
                if (lastInput1_0 == 2){ //used to put spaces between the 0's to spread out the look of the map
                    menu.display(currentPos2, rowCount, "0");
                    lastInput1_0 = 0;
                } else {
                    menu.display(currentPos2, rowCount, " ");
                    lastInput1_0++;
                }
                currentPos2++;
            }
        }
        //menu.display(30, 0, "Part 2"); //writes the 3rd portion of the map
        if(pos[rowCount][4] != 0){
            int currentPos3 = pos[rowCount][4];
            while (currentPos3 <= pos[rowCount][5]){

                if (lastInput1_0 == 2){ //used to put spaces between the 0's to spread out the look of the map
                    menu.display(currentPos3, rowCount, "0");
                    lastInput1_0 = 0;
                } else {
                    menu.display(currentPos3, rowCount, " ");
                    lastInput1_0++;
                }
                currentPos3++;
            }
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