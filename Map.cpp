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

Map::Map(){
    static int i = 0;
    allLandmarks.landmarkLocation.resize(inCityLocations.size());
    allLandmarks.iconType.resize(inCityLocations.size());
    //cout << i++ << endl;
    for(int i = 0; i <= inCityLocations.size()-1; i++) {
        allLandmarks.landmarkLocation[i].resize(locationCountLandmark);
        allLandmarks.iconType[i].resize(locationCountLandmark);
    }
    for(int i = 1; i <= inCityLocations.size()-1; i++) allLandmarks.landmarkLocation[i][0] = 1; //set all city locations to 1
    for(int i = 1; i <= inCityLocations.size()-1; i++) allLandmarks.iconType[i][0] = getMapCity(); //set all city icons to standard

    for(int i = 1; i <= inCityLocations.size()-1; i++) allLandmarks.landmarkLocation[i][0] = city.location.at(i); //set locations of each city

    for(int i = 1; i <= maxCityObjectCount; i++) {
        for(int i1 = 1; i1 <= inCityLocations.size()-1; i1++) allLandmarks.landmarkLocation[i1][i] = 0; //set all landmarks in city locations to 0
        for(int i2 = 1; i2 <= inCityLocations.size()-1; i2++) allLandmarks.iconType[i2][i] = getMapCity(); //set city objects to standard city icon
    }
    for(int city = 1; city <= inCityLocations.size()-1; city++){
        for(int i = 1; i <= inCityLocations[city].size()-1; i++) { //change out interactiveLandmarkCount[city] for inCityLocations[1].size()
            allLandmarks.landmarkLocation[city][i] = inCityLocations[city][i];
            allLandmarks.iconType[city][i] = getMapCity(); //allows to ease expansion
        }
    }
}

void Map::listAvalibleLocations(string username){
    Account account;
    Battle battle;
    int currentLevel = account.getLevel(username);
    int unlockedLocationsNum = 1;
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
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
                /*
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

void Map::displayMapOutline(int maxColumnInput, int maxRowInput, int minColumnInput, int MinRowInput){
    maxColumn = maxColumnInput;
    maxRow = maxRowInput + optionsHeight;
    initalPosRow = minRow = MinRowInput + optionsHeight;
    initalPosColumn = minColumn = minColumnInput;
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

void Map::fillInMap(){
    int const tempmaxRow = maxRow;
    int pos[tempmaxRow][6];
    int value = 2 + optionsHeight;
    int smartNumber = 1;
    for (int i = 0; i <= tempmaxRow; i++){ //set all values to null before setting
        pos[i][5] = 0;
        pos[i][4] = 0;
        pos[i][3] = 0;
        pos[i][2] = 0;
        pos[i][1] = 0;
        pos[i][0] = 0;
    }
    //main island asci data:
    pos[value][1] = 36+smartNumber;
    pos[value++][0] = 34+smartNumber;//36
    pos[value][1] = 38+smartNumber;
    pos[value++][0] = 22+smartNumber;//35
    pos[value][1] = 42+smartNumber;
    pos[value++][0] = 18+smartNumber;//34
    pos[value][1] = 52+smartNumber;
    pos[value++][0] = 16+smartNumber;//33
    pos[value][1] = 54+smartNumber;
    pos[value++][0] = 14+smartNumber;//32
    pos[value][1] = 56+smartNumber;
    pos[value++][0] = 14+smartNumber;//31
    pos[value][1] = 58+smartNumber;
    pos[value++][0] = 10+smartNumber;//30
    pos[value][1] = 64+smartNumber;
    pos[value++][0] = 6+smartNumber;//29
    pos[value][1] = 66+smartNumber;
    pos[value++][0] = 2+smartNumber;//28
    pos[value][1] = 70+smartNumber;
    pos[value++][0] = 4+smartNumber;//27
    pos[value][1] = 74+smartNumber;
    pos[value++][0] = 4+smartNumber;//26
    pos[value][1] = 76+smartNumber;
    pos[value++][0] = 4+smartNumber;//25
    pos[value][1] = 78+smartNumber;
    pos[value++][0] = 4+smartNumber;//24
    pos[value][1] = 78+smartNumber;
    pos[value++][0] = 4+smartNumber;//23
    pos[value][1] = 80+smartNumber;
    pos[value++][0] = 4+smartNumber;//22
    pos[value][3] = 82+smartNumber;
    pos[value][2] = 42+smartNumber;
    pos[value][1] = 36+smartNumber;
    pos[value++][0] = 2+smartNumber;//21
    pos[value][3] = 84+smartNumber;
    pos[value][2] = 48+smartNumber;
    pos[value][1] = 36+smartNumber;
    pos[value++][0] = 2+smartNumber;//20
    pos[value][5] = 86+smartNumber;
    pos[value][4] = 78+smartNumber;
    pos[value][3] = 74+smartNumber;
    pos[value][2] = 50+smartNumber;
    pos[value][1] = 36+smartNumber;
    pos[value++][0] = 2+smartNumber;//19
    pos[value][5] = 88+smartNumber;
    pos[value][4] = 80+smartNumber;
    pos[value][3] = 74+smartNumber;
    pos[value][2] = 54+smartNumber;
    pos[value][1] = 36+smartNumber;
    pos[value++][0] = 4+smartNumber;//18
    pos[value][5] = 88+smartNumber;
    pos[value][4] = 86+smartNumber;
    pos[value][3] = 72+smartNumber;
    pos[value][2] = 60+smartNumber;
    pos[value][1] = 34+smartNumber;
    pos[value++][0] = 4+smartNumber;//17
    pos[value][1] = 34+smartNumber;
    pos[value++][0] = 8+smartNumber;//16
    pos[value][1] = 36+smartNumber;
    pos[value++][0] = 8+smartNumber;//15
    pos[value][1] = 38+smartNumber;
    pos[value++][0] = 10+smartNumber;//14
    pos[value][1] = 38+smartNumber;
    pos[value++][0] = 12+smartNumber;//13
    pos[value][1] = 40+smartNumber;
    pos[value++][0] = 12+smartNumber;//12
    pos[value][1] = 42+smartNumber;
    pos[value++][0] = 14+smartNumber;//11
    pos[value][1] = 42+smartNumber;
    pos[value++][0] = 16+smartNumber;//10
    pos[value][1] = 46+smartNumber;
    pos[value++][0] = 16+smartNumber;//9
    pos[value][1] = 50+smartNumber;
    pos[value++][0] = 14+smartNumber;//8
    pos[value][1] = 42+smartNumber;
    pos[value++][0] = 16+smartNumber;//7
    pos[value][3] = 98+smartNumber;
    pos[value][2] = 86+smartNumber; 
    pos[value][1] = 42+smartNumber;
    pos[value++][0] = 18+smartNumber;//6
    pos[value][3] = 104+smartNumber;
    pos[value][2] = 80+smartNumber;
    pos[value][1] = 34+smartNumber;
    pos[value++][0] = 20+smartNumber;//5
    pos[value][3] = 108+smartNumber;
    pos[value][2] = 80+smartNumber;
    pos[value][1] = 32+smartNumber;
    pos[value++][0] = 24+smartNumber;//4
    pos[value][3] = 110+smartNumber;
    pos[value][2] = 84+smartNumber;
    pos[value][1] = 32+smartNumber;
    pos[value++][0] = 28+smartNumber;//3
    pos[value][1] = 32+smartNumber;
    pos[value++][0] = 30+smartNumber;//2
    pos[value][1] = 32+smartNumber;
    pos[value++][0] = 30+smartNumber;//1
    while (value < maxRow) {
        pos[value][1] = maxColumn - 1;//-1 for the inside of the outline
        pos[value++][0] = maxColumn;//+1 for the inside of the outline //was minColumn + 1 to fill the entire row
    }

    //Menu menu;
    int locationConfirmedCount = 0;
    //starting from top to bottom for the first number and left to right for the second number in pos1_1 - pos#_# 
    int posRow = minRow;
    for (int rowCount = minRow+1; rowCount < maxRow; rowCount++){ //added 1 to the minRow since this will then keep the output inside the outline
        //mapUnfilled = to_string(locationConfirmedCount); //tesing value

        for(int columnPos = initalPosColumn+1; columnPos < pos[rowCount][0]; columnPos++){
            menu.display(columnPos, rowCount, getMapBlank() ,false,false, 16);
        }

        int currentPos = pos[rowCount][0];
        int lastInput1_0 = 1;
        //int currentPos = 5;
        while (currentPos <= pos[rowCount][1]){

            if (lastInput1_0 == 1){ //used to put spaces between the 0's to spread out the look of the map
                locationConfirmedCount++;
                menu.display(currentPos, rowCount, getMapUnfilled() ,false,false, 32);
                possibleTravelLocations[locationConfirmedCount][0].x = currentPos; //the subNum of 0 means the parent location on the map
                possibleTravelLocations[locationConfirmedCount][0].y = rowCount;
                //these two lines record all of the locations on the map so people can travel to them.
                    //worldMap.locationsRecord(locationConfirmedCount, rowCount, currentPos); //map.setPossibleTravelLocations(locationConfirmedCount, rowCount, currentPos);
                    // Testing output:  cout << "Y: " + to_string(rowCount) + "X: " + to_string(currentPos) << endl;

                lastInput1_0 = 0;
            } else {
                menu.display(currentPos, rowCount, getMapBlank(), false, false, 32);
                lastInput1_0++;
            }
            currentPos++;
        }

        // next map step:

        int endpos;
        try{
            endpos = pos[rowCount][2];
        } catch(...){
            endpos = maxColumn;
        }

        if (endpos == 0) endpos = maxColumn;

        for(int columnPos = pos[rowCount][1]+1; columnPos < endpos; columnPos++){
            menu.display(columnPos, rowCount, getMapBlank() ,false,false, 16);
        }

        lastInput1_0 = 1;
        //menu.display(15, 0, "Part 1"); //writes the 2nd portion of the map
        if(pos[rowCount][2] != 0){
            int currentPos2 = pos[rowCount][2];
            while (currentPos2 <= pos[rowCount][3]){
                if (lastInput1_0 == 1){ //used to put spaces between the 0's to spread out the look of the map
                    locationConfirmedCount++;
                    menu.display(currentPos2, rowCount, getMapUnfilled(),false,false, 32);
                    possibleTravelLocations[locationConfirmedCount][0].x = currentPos2;  //the subNum of 0 means the parent location on the map
                    possibleTravelLocations[locationConfirmedCount][0].y = rowCount;
                    //worldMap.locationsRecord(locationConfirmedCount, rowCount, currentPos); //map.setPossibleTravelLocations(locationConfirmedCount, rowCount, currentPos);
                    // Testing output:  cout << "Y: " + to_string(rowCount) + "X: " + to_string(currentPos) << endl;

                    lastInput1_0 = 0;
                } else {
                    menu.display(currentPos2, rowCount, getMapBlank(), false, false, 32);
                    lastInput1_0++;
                }
                currentPos2++;
            }
        }

        //next map step:

        int endpos2;
        int startpos;
        try{
            endpos2 = pos[rowCount][4];
        } catch(...){
            menu.display(0, 1, "Failed endpos2",false,false, 15);
        }
        if (endpos2 == 0) endpos2 = maxColumn;
        try{
            startpos = pos[rowCount][3];
            if(startpos > 0) startpos++;
        } catch(...){
            menu.display(0, 1, "Failed startpos",false,false, 15);
        }
        if (startpos == 0) startpos = pos[rowCount][1]+1;

        for(int columnPos = startpos; columnPos < endpos2; columnPos++){
            menu.display(columnPos, rowCount, getMapBlank() ,false,false, 16);
        }
        
        

        lastInput1_0 = 1;
        //menu.display(30, 0, "Part 2"); //writes the 3rd portion of the map
        if(pos[rowCount][4] != 0){
            int currentPos3 = pos[rowCount][4];
            while (currentPos3 <= pos[rowCount][5]){

                if (lastInput1_0 == 1){ //used to put spaces between the 0's to spread out the look of the map
                    locationConfirmedCount++;
                    menu.display(currentPos3, rowCount, getMapUnfilled(),false,false, 32);
                    possibleTravelLocations[locationConfirmedCount][0].x = currentPos3;
                    possibleTravelLocations[locationConfirmedCount][0].y = rowCount;
                    //worldMap.locationsRecord(locationConfirmedCount, rowCount, currentPos); //map.setPossibleTravelLocations(locationConfirmedCount, rowCount, currentPos);
                    // Testing output:  cout << "Y: " + to_string(rowCount) + "X: " + to_string(currentPos) << endl;

                    lastInput1_0 = 0;
                } else {
                    menu.display(currentPos3, rowCount, getMapBlank(), false, false, 32);
                    lastInput1_0++;
                }
                currentPos3++;
            }
        }
        
        int enter = 0;
        int endpos3;
        int startpos2;
        try{
            endpos3 = pos[rowCount][6];
        } catch(...){
            endpos3 = maxColumn;
        }
        if (endpos3 == 0 || endpos3 < 0 || endpos3 < maxColumn) endpos3 = maxColumn;
        try{
            //menu.waitForEnter(enter);
            startpos2 = pos[rowCount][5];
        } catch(...){
            menu.display(0, 1, "Failed",false,false, 15);
        }
        if(startpos2 > 0){
            startpos2++;
            for(int columnPos = startpos2; columnPos < endpos3; columnPos++){
                menu.display(columnPos, rowCount, getMapBlank(), false, false, 16);
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

void Map::writeLandmark(int locationValue, string iconType){
    if(isCityLocation(locationValue)){
        menu.display(possibleTravelLocations[locationValue][0].x, possibleTravelLocations[locationValue][0].y, iconType, true, false, 47);
        //for(int i = 1; i < map.locationCountLandmark)
    }
}

void Map::writeLandmarkObject(int locationValue){
    if (locationValue){
        menu.display(possibleTravelLocations[getCurrentLocation()][locationValue].x, possibleTravelLocations[getCurrentLocation()][locationValue].y, allLandmarks.iconType[whichCity(getCurrentLocation())][locationValue], true, false, 47);
    }
    /*
    if(isCityLocation(locationValue)){
        //for(int i = 1; i < map.locationCountLandmark)
    }
    */
}

void Map::writeLandmarks(){
    for(int i = inCityLocations.size()-1; i >= 1; i--) writeLandmark(allLandmarks.landmarkLocation[i][0], allLandmarks.iconType[i][0]);
}

void Map::writeLandmarksObjects(/*int objectCount*/){ //this needs to be setup for cities
    int city = whichCity(getCurrentLocation());
    int numberOfLandmarks = getInteractiveLandmarkCount(city);
    for(int i = numberOfLandmarks; i >= 1; i--) writeLandmarkObject(allLandmarks.landmarkLocation[city][i]);
}

bool Map::isCityLocation(int locationValue){
    for(int i = 1; i <= inCityLocations.size()-1; i++){
        if (locationValue == city.location.at(i)){
            return true;
        }
    }
    return false;
}

bool Map::isLandmarkObjectInteractiveLocation(int locationValue){
    /*
    int potentialLandmarkCount = inCityLocations[whichCity(getCurrentLocation())].size()-1;
    for(int i = 1; i <= potentialLandmarkCount; i++){
        if (locationValue == inCityLocations[whichCity(getCurrentLocation())][i]){
            return true;
        }
    }
    */
    int potentialLandmarkCount;
    switch(whichCity(getCurrentLocation())){
        case 1:{
            potentialLandmarkCount = inCityLocations[1].size()-1;
            for(int i = 1; i <= potentialLandmarkCount; i++){
                if (locationValue == inCityLocations[1][i]){
                    return true;
                }
            }
            break;
        }
        case 2:{
            potentialLandmarkCount = inCityLocations[2].size()-1;
            for(int i = 1; i <= potentialLandmarkCount; i++){
                if (locationValue == inCityLocations[2][i]){
                    return true;
                }
            }
            break;
        }
        case 3:{
            potentialLandmarkCount = inCityLocations[3].size()-1;
            for(int i = 1; i <= potentialLandmarkCount; i++){
                if (locationValue == inCityLocations[3][i]){
                    return true;
                }
            }
            break;
        }
        case 4:{
            potentialLandmarkCount = inCityLocations[4].size()-1;
            for(int i = 1; i <= potentialLandmarkCount; i++){
                if (locationValue == inCityLocations[4][i]){
                    return true;
                }
            }
            break;
        }
        case 5:{
            potentialLandmarkCount = inCityLocations[5].size()-1;
            for(int i = 1; i <= potentialLandmarkCount; i++){
                if (locationValue == inCityLocations[5][i]){
                    return true;
                }
            }
            break;
        }
        case 6:{
            potentialLandmarkCount = inCityLocations[6].size()-1;
            for(int i = 1; i <= potentialLandmarkCount; i++){
                if (locationValue == inCityLocations[6][i]){
                    return true;
                }
            }
            break;
        }
        default:{ //this means that it is not a landmark location.
            //menu.displayMessageWithPause(0,0,"Issue with switch(locationValue) in bool Map::isLandmarkObjectInteractiveLocation(int locationValue)");
            break;
        }
    }
    return false;
}

int Map::whichCity(int locationValue){
    for(int i = 1; i <= inCityLocations.size()-1; i++){
        if (locationValue == city.location.at(i)){ // cityLocation[i] --- this was the old method
            return i;
        }
    }
    return 0;
}

bool Map::canMoveFromCurrentLocation(int directionValue) { //1 for north, 2 for east, 3 for south, 4 for west
    switch (directionValue)
    {
        case 1:{
            int endVal = 0;
            for (int i = 0; i <= locationCount; i++){
                if (possibleTravelLocations[i][0].x == possibleTravelLocations[getCurrentLocation()][0].x){
                    if (possibleTravelLocations[i][0].y == possibleTravelLocations[getCurrentLocation()][0].y - 1){
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
                if (possibleTravelLocations[i][0].x == possibleTravelLocations[getCurrentLocation()][0].x + 2){
                    if (possibleTravelLocations[i][0].y == possibleTravelLocations[getCurrentLocation()][0].y){
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
                if (possibleTravelLocations[i][0].x == possibleTravelLocations[getCurrentLocation()][0].x){
                    if (possibleTravelLocations[i][0].y == possibleTravelLocations[getCurrentLocation()][0].y + 1){
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
                if (possibleTravelLocations[i][0].x == possibleTravelLocations[getCurrentLocation()][0].x - 2){
                    if (possibleTravelLocations[i][0].y == possibleTravelLocations[getCurrentLocation()][0].y){
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

bool Map::canMoveFromCurrentLocationCity(int directionValue) { //1 for north, 2 for east, 3 for south, 4 for west
    switch (directionValue)
    {
        case 1:{
            int endVal = 0;
            for (int i = 0; i <= locationCountLandmark; i++){
                if (possibleTravelLocations[getCurrentLocation()][i].x == possibleTravelLocations[getCurrentLocation()][getCurrentLandmarkLocation()].x){
                    if (possibleTravelLocations[getCurrentLocation()][i].y == possibleTravelLocations[getCurrentLocation()][getCurrentLandmarkLocation()].y - 1){
                        setCurrentLandmarkLocation(i);
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
            for (int i = 0; i <= locationCountLandmark; i++){
                if (possibleTravelLocations[getCurrentLocation()][i].x == possibleTravelLocations[getCurrentLocation()][getCurrentLandmarkLocation()].x + 2){
                    if (possibleTravelLocations[getCurrentLocation()][i].y == possibleTravelLocations[getCurrentLocation()][getCurrentLandmarkLocation()].y){
                        setCurrentLandmarkLocation(i);
                        return true;
                    }
                }
                endVal++;
            }
            if (endVal >= locationCountLandmark){
                //cout << "location travel failed" << endl;
                //system("pause");
                return false;
            }
            break;
        }
        case 3:{
            int endVal = 0;
            for (int i = 0; i <= locationCountLandmark; i++){
                if (possibleTravelLocations[getCurrentLocation()][i].x == possibleTravelLocations[getCurrentLocation()][getCurrentLandmarkLocation()].x){
                    if (possibleTravelLocations[getCurrentLocation()][i].y == possibleTravelLocations[getCurrentLocation()][getCurrentLandmarkLocation()].y + 1){
                        setCurrentLandmarkLocation(i);
                        return true;
                    }
                }
                endVal++;
            }
            if (endVal >= locationCountLandmark){
                //cout << "location travel failed" << endl;
                //system("pause");
                return false;
            }
            break;
        }
        case 4:{
            int endVal = 0;
            for (int i = 0; i <= locationCountLandmark; i++){
                if (possibleTravelLocations[getCurrentLocation()][i].x == possibleTravelLocations[getCurrentLocation()][getCurrentLandmarkLocation()].x - 2){
                    if (possibleTravelLocations[getCurrentLocation()][i].y == possibleTravelLocations[getCurrentLocation()][getCurrentLandmarkLocation()].y){
                        setCurrentLandmarkLocation(i);
                        return true;
                    }
                }
                endVal++;
            }
            if (endVal >= locationCountLandmark){
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

void Map::fillInLandmarkMap(){
    int city = whichCity(getCurrentLocation());
    int const tempmaxRow = getMapCityStandardMaxRow() + optionsHeight;
    int pos[tempmaxRow][6];
    int value = getMapCityStandardMinRow()+ optionsHeight;
    switch(city){
        case 1:{
            for (int i = 0; i <= tempmaxRow; i++){ //set all values to null before setting
                pos[i][5] = 0;
                pos[i][4] = 0;
                pos[i][3] = 0;
                pos[i][2] = 0;
                pos[i][1] = 0;
                pos[i][0] = 0;
            }
            //city asci data:
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//20
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//19
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//18
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//17
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//16
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//15
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//14
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//13
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//12
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//11
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//10
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//9
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//8
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//7
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//6
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//5
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//4
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//3
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//2
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//1
            break;
        }
        case 2:{
            for (int i = 0; i <= tempmaxRow; i++){ //set all values to null before setting
                pos[i][5] = 0;
                pos[i][4] = 0;
                pos[i][3] = 0;
                pos[i][2] = 0;
                pos[i][1] = 0;
                pos[i][0] = 0;
            }
            //city asci data:
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//20
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//19
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//18
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//17
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//16
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//15
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//14
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//13
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//12
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//11
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//10
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//9
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//8
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//7
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//6
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//5
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//4
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//3
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//2
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//1
            break;
        }
        case 3:{
            for (int i = 0; i <= tempmaxRow; i++){ //set all values to null before setting
                pos[i][5] = 0;
                pos[i][4] = 0;
                pos[i][3] = 0;
                pos[i][2] = 0;
                pos[i][1] = 0;
                pos[i][0] = 0;
            }
            //city asci data:
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//20
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//19
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//18
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//17
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//16
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//15
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//14
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//13
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//12
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//11
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//10
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//9
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//8
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//7
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//6
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//5
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//4
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//3
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//2
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//1
            break;
        }
        case 4:{
            for (int i = 0; i <= tempmaxRow; i++){ //set all values to null before setting
                pos[i][5] = 0;
                pos[i][4] = 0;
                pos[i][3] = 0;
                pos[i][2] = 0;
                pos[i][1] = 0;
                pos[i][0] = 0;
            }
            //city asci data:
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//20
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//19
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//18
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//17
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//16
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//15
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//14
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//13
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//12
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//11
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//10
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//9
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//8
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//7
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//6
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//5
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//4
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//3
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//2
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//1
            break;
        }
        case 5:{
            for (int i = 0; i <= tempmaxRow; i++){ //set all values to null before setting
                pos[i][5] = 0;
                pos[i][4] = 0;
                pos[i][3] = 0;
                pos[i][2] = 0;
                pos[i][1] = 0;
                pos[i][0] = 0;
            }
            //city asci data:
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//20
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//19
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//18
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//17
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//16
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//15
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//14
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//13
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//12
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//11
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//10
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//9
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//8
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//7
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//6
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//5
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//4
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//3
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//2
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//1
            break;
        }
        case 6:{
            for (int i = 0; i <= tempmaxRow; i++){ //set all values to null before setting
                pos[i][5] = 0;
                pos[i][4] = 0;
                pos[i][3] = 0;
                pos[i][2] = 0;
                pos[i][1] = 0;
                pos[i][0] = 0;
            }
            //city asci data:
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//20
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//19
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//18
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//17
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//16
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//15
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//14
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//13
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//12
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//11
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//10
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//9
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//8
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//7
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//6
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//5
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//4
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//3
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//2
            pos[value][1] = getMapCityStandardMaxColumn()-1;
            pos[value++][0] = getMapCityStandardMinColumn()+1;//1
            break;
        }
        default:
            menu.displayMessageWithPause(0,0, "failed void Map::fillInLandmarkMap(){ " , false, false);
            break;

    }
    /*
    while (value < getMapCityStandardMaxRow()) {
        pos[value][1] = getMapCityStandardMaxColumn() - 1;//-1 for the inside of the outline
        pos[value++][0] = getMapCityStandardMaxColumn();//+1 for the inside of the outline //was minColumn + 1 to fill the entire row
    }*/
    int locationConfirmedCount = 0;
    for (int rowCount = getMapCityStandardMinRow()+optionsHeight+1; rowCount < getMapCityStandardMaxRow()+optionsHeight; rowCount++){ //added 1 to the minRow since this will then keep the output inside the outline
        //mapUnfilled = to_string(locationConfirmedCount); //tesing value

        for(int columnPos = mapCityStandardMinColumn+1; columnPos < pos[rowCount][0]; columnPos++){
            menu.display(columnPos, rowCount, getMapUnfilled() ,false,false, 16);
        }

        int currentPos = pos[rowCount][0];
        int lastInput1_0 = 1;
        //int currentPos = 5;
        while (currentPos <= pos[rowCount][1]){

            if (lastInput1_0 == 1){ //used to put spaces between the 0's to spread out the look of the map
                locationConfirmedCount++;
                menu.display(currentPos, rowCount, getMapUnfilled() ,false,false, 32);
                possibleTravelLocations[map.getCurrentLocation()][locationConfirmedCount].x = currentPos; //the subNum of 0 means the parent location on the map
                possibleTravelLocations[map.getCurrentLocation()][locationConfirmedCount].y = rowCount;
                //these two lines record all of the locations on the map so people can travel to them.
                    //worldMap.locationsRecord(locationConfirmedCount, rowCount, currentPos); //map.setPossibleTravelLocations(locationConfirmedCount, rowCount, currentPos);
                    // Testing output:  cout << "Y: " + to_string(rowCount) + "X: " + to_string(currentPos) << endl;

                lastInput1_0 = 0;
            } else {
                menu.display(currentPos, rowCount, getMapBlank(), false, false, 32);
                lastInput1_0++;
            }
            currentPos++;
        }
    }

}

void Map::fillInMap(int landmark, int subLandmark){
    
}