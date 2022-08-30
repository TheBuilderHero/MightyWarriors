#include <string>
#include <iostream>

#include "Main.h"
#include "Map.h"
#include "WorldMap.h"
#include "Menu.h"
#include "Account.h"
#include "Battle.h"
#include "Quests.h"

using namespace std;

//extern Menu menu;

void Map::listAvalibleLocations(string username){
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
    //Menu menu;
    int optionsHeight = 8;
    maxColumn = 170; //was 210
    maxRow = 42 + optionsHeight; //was 62
    int initalPosRow = minRow = 1 + optionsHeight;
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
    int optionsHeight = 8;
    int const tempmaxRow = maxRow;
    int pos[tempmaxRow][6];
    int value = 2 + optionsHeight;
    for (int i = 0; i <= tempmaxRow; i++){ //set all values to null before setting
        pos[i][5] = 0;
        pos[i][4] = 0;
        pos[i][3] = 0;
        pos[i][2] = 0;
        pos[i][1] = 0;
        pos[i][0] = 0;
    }
    //main island asci data:
    pos[value][1] = 36+50;
    pos[value++][0] = 34+50;//36
    pos[value][1] = 38+50;
    pos[value++][0] = 22+50;//35
    pos[value][1] = 42+50;
    pos[value++][0] = 18+50;//34
    pos[value][1] = 52+50;
    pos[value++][0] = 16+50;//33
    pos[value][1] = 54+50;
    pos[value++][0] = 14+50;//32
    pos[value][1] = 56+50;
    pos[value++][0] = 14+50;//31
    pos[value][1] = 58+50;
    pos[value++][0] = 10+50;//30
    pos[value][1] = 64+50;
    pos[value++][0] = 6+50;//29
    pos[value][1] = 66+50;
    pos[value++][0] = 2+50;//28
    pos[value][1] = 70+50;
    pos[value++][0] = 4+50;//27
    pos[value][1] = 74+50;
    pos[value++][0] = 4+50;//26
    pos[value][1] = 76+50;
    pos[value++][0] = 4+50;//25
    pos[value][1] = 78+50;
    pos[value++][0] = 4+50;//24
    pos[value][1] = 78+50;
    pos[value++][0] = 4+50;//23
    pos[value][1] = 80+50;
    pos[value++][0] = 4+50;//22
    pos[value][3] = 82+50;
    pos[value][2] = 42+50;
    pos[value][1] = 36+50;
    pos[value++][0] = 2+50;//21
    pos[value][3] = 84+50;
    pos[value][2] = 48+50;
    pos[value][1] = 36+50;
    pos[value++][0] = 2+50;//20
    pos[value][5] = 86+50;
    pos[value][4] = 78+50;
    pos[value][3] = 74+50;
    pos[value][2] = 50+50;
    pos[value][1] = 36+50;
    pos[value++][0] = 2+50;//19
    pos[value][5] = 88+50;
    pos[value][4] = 80+50;
    pos[value][3] = 74+50;
    pos[value][2] = 54+50;
    pos[value][1] = 36+50;
    pos[value++][0] = 4+50;//18
    pos[value][5] = 88+50;
    pos[value][4] = 86+50;
    pos[value][3] = 72+50;
    pos[value][2] = 60+50;
    pos[value][1] = 34+50;
    pos[value++][0] = 4+50;//17
    pos[value][1] = 34+50;
    pos[value++][0] = 8+50;//16
    pos[value][1] = 36+50;
    pos[value++][0] = 8+50;//15
    pos[value][1] = 38+50;
    pos[value++][0] = 10+50;//14
    pos[value][1] = 38+50;
    pos[value++][0] = 12+50;//13
    pos[value][1] = 40+50;
    pos[value++][0] = 12+50;//12
    pos[value][1] = 42+50;
    pos[value++][0] = 14+50;//11
    pos[value][1] = 42+50;
    pos[value++][0] = 16+50;//10
    pos[value][1] = 46+50;
    pos[value++][0] = 16+50;//9
    pos[value][1] = 50+50;
    pos[value++][0] = 14+50;//8
    pos[value][1] = 42+50;
    pos[value++][0] = 16+50;//7
    pos[value][3] = 98+50;
    pos[value][2] = 86+50; 
    pos[value][1] = 42+50;
    pos[value++][0] = 18+50;//6
    pos[value][3] = 104+50;
    pos[value][2] = 80+50;
    pos[value][1] = 34+50;
    pos[value++][0] = 20+50;//5
    pos[value][3] = 108+50;
    pos[value][2] = 80+50;
    pos[value][1] = 32+50;
    pos[value++][0] = 24+50;//4
    pos[value][3] = 110+50;
    pos[value][2] = 84+50;
    pos[value][1] = 32+50;
    pos[value++][0] = 28+50;//3
    pos[value][1] = 32+50;
    pos[value++][0] = 30+50;//2
    pos[value][1] = 32+50;
    pos[value++][0] = 30+50;//1
    while (value < maxRow) {
        pos[value][1] = maxColumn - 1;//-1 for the inside of the outline
        pos[value++][0] = maxColumn;//+1 for the inside of the outline //was minColumn + 1 to fill the entire row
    }

    //Menu menu;
    int locationConfirmedCount = 0;
    //starting from top to bottom for the first number and left to right for the second number in pos1_1 - pos#_# 
    int posRow = minRow; //+1 for the inside of the outline
    for (int rowCount = minRow+1; rowCount < maxRow; rowCount++){ //added 1 to the minRow since this will then keep the output inside the outline
        //mapUnfilled = to_string(locationConfirmedCount); //tesing value
        int currentPos = pos[rowCount][0];
        int lastInput1_0 = 1;
        //int currentPos = 5;
        while (currentPos <= pos[rowCount][1]){

            if (lastInput1_0 == 1){ //used to put spaces between the 0's to spread out the look of the map
                locationConfirmedCount++;
                menu.display(currentPos, rowCount, getMapUnfilled() ,false,false);
                possibleTravelLocations[locationConfirmedCount].x = currentPos;
                possibleTravelLocations[locationConfirmedCount].y = rowCount;
                //these two lines record all of the locations on the map so people can travel to them.
                    //worldMap.locationsRecord(locationConfirmedCount, rowCount, currentPos); //map.setPossibleTravelLocations(locationConfirmedCount, rowCount, currentPos);
                    // Testing output:  cout << "Y: " + to_string(rowCount) + "X: " + to_string(currentPos) << endl;

                lastInput1_0 = 0;
            } else {
                menu.display(currentPos, rowCount, getMapBlank());
                lastInput1_0++;
            }
            currentPos++;
        }

        // next map step:

        lastInput1_0 = 1;
        //menu.display(15, 0, "Part 1"); //writes the 2nd portion of the map
        if(pos[rowCount][2] != 0){
            int currentPos2 = pos[rowCount][2];
            while (currentPos2 <= pos[rowCount][3]){
                if (lastInput1_0 == 1){ //used to put spaces between the 0's to spread out the look of the map
                    locationConfirmedCount++;
                    menu.display(currentPos2, rowCount, getMapUnfilled(),false,false);
                    possibleTravelLocations[locationConfirmedCount].x = currentPos2;
                    possibleTravelLocations[locationConfirmedCount].y = rowCount;
                    //worldMap.locationsRecord(locationConfirmedCount, rowCount, currentPos); //map.setPossibleTravelLocations(locationConfirmedCount, rowCount, currentPos);
                    // Testing output:  cout << "Y: " + to_string(rowCount) + "X: " + to_string(currentPos) << endl;

                    lastInput1_0 = 0;
                } else {
                    menu.display(currentPos2, rowCount, getMapBlank());
                    lastInput1_0++;
                }
                currentPos2++;
            }
        }

        //next map step:

        lastInput1_0 = 1;
        //menu.display(30, 0, "Part 2"); //writes the 3rd portion of the map
        if(pos[rowCount][4] != 0){
            int currentPos3 = pos[rowCount][4];
            while (currentPos3 <= pos[rowCount][5]){

                if (lastInput1_0 == 1){ //used to put spaces between the 0's to spread out the look of the map
                    locationConfirmedCount++;
                    menu.display(currentPos3, rowCount, getMapUnfilled(),false,false);
                    possibleTravelLocations[locationConfirmedCount].x = currentPos3;
                    possibleTravelLocations[locationConfirmedCount].y = rowCount;
                    //worldMap.locationsRecord(locationConfirmedCount, rowCount, currentPos); //map.setPossibleTravelLocations(locationConfirmedCount, rowCount, currentPos);
                    // Testing output:  cout << "Y: " + to_string(rowCount) + "X: " + to_string(currentPos) << endl;

                    lastInput1_0 = 0;
                } else {
                    menu.display(currentPos3, rowCount, getMapBlank());
                    lastInput1_0++;
                }
                currentPos3++;
            }
        }
        /*
        if (worldMap.getMapLocationValue() >= 0){
            //value is set properly
        } else {
            //value was not set
            worldMap.setMapLocationValue(433);
        }
        worldMap.setMapLocationValue(433);
        */
        /*
        for (int i = 0; i <= locationCount; i++){
            cout << " X: " + to_string(map.getPossibleTravelLocationsX(worldMap.getMapLocationValue())) + " Y: " + to_string(map.getPossibleTravelLocationsY(worldMap.getMapLocationValue())) << endl;
        }*/
        //menu.display(worldMap.getLocationX(worldMap.getMapLocationValue()), worldMap.getLocationY(worldMap.getMapLocationValue()), mapFilled);
        menu.display(0, 51, "Total number of locations: " + to_string(locationConfirmedCount)); //display the number of locations on the map
        //menu.display(0, 52, "map value: " + to_string(worldMap.getMapLocationValue()));
    }
}

bool Map::canMoveFromCurrentLocation(int directionValue) { //1 for north, 2 for east, 3 for south, 4 for west
    switch (directionValue)
    {
        case 1:{
            int endVal = 0;
            for (int i = 0; i <= locationCount; i++){
                if (possibleTravelLocations[i].x == possibleTravelLocations[getCurrentLocation()].x){
                    if (possibleTravelLocations[i].y == possibleTravelLocations[getCurrentLocation()].y - 1){
                        setCurrentLocation(i);
                        return true;
                    }
                }
                endVal++;
            }
            if (endVal >= locationCount){
                //cout << "location travel failed" << endl;
                //system("pause");
                return false;
            }
            break;
        }
        case 2:{
            int endVal = 0;
            for (int i = 0; i <= locationCount; i++){
                if (possibleTravelLocations[i].x == possibleTravelLocations[getCurrentLocation()].x + 2){
                    if (possibleTravelLocations[i].y == possibleTravelLocations[getCurrentLocation()].y){
                        setCurrentLocation(i);
                        return true;
                    }
                }
                endVal++;
            }
            if (endVal >= locationCount){
                //cout << "location travel failed" << endl;
                //system("pause");
                return false;
            }
            break;
        }
        case 3:{
            int endVal = 0;
            for (int i = 0; i <= locationCount; i++){
                if (possibleTravelLocations[i].x == possibleTravelLocations[getCurrentLocation()].x){
                    if (possibleTravelLocations[i].y == possibleTravelLocations[getCurrentLocation()].y + 1){
                        setCurrentLocation(i);
                        return true;
                    }
                }
                endVal++;
            }
            if (endVal >= locationCount){
                //cout << "location travel failed" << endl;
                //system("pause");
                return false;
            }
            break;
        }
        case 4:{
            int endVal = 0;
            for (int i = 0; i <= locationCount; i++){
                if (possibleTravelLocations[i].x == possibleTravelLocations[getCurrentLocation()].x - 2){
                    if (possibleTravelLocations[i].y == possibleTravelLocations[getCurrentLocation()].y){
                        setCurrentLocation(i);
                        return true;
                    }
                }
                endVal++;
            }
            if (endVal >= locationCount){
                //cout << "location travel failed" << endl;
                //system("pause");
                return false;
            }
            break;
        }
    
        default:{
            return false;
        }
    }
    return false;
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