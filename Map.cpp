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
    for(int i = 1; i <= CityCount; i++) allCities.landmarkLocation[i] = 1; //set all city locations to 1
    for(int i = 1; i <= CityCount; i++) allCities.iconType[i] = getMapCity(); //set all city icons to standard
    allCities.landmarkLocation[1] = City1Location;
    allCities.landmarkLocation[2] = City2Location;
    allCities.landmarkLocation[3] = City3Location;
    allCities.landmarkLocation[4] = City4Location;
    allCities.landmarkLocation[5] = City5Location;
    allCities.landmarkLocation[6] = City6Location;
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

void Map::writeLandmarks(){
    for(int i = CityCount; i >= 1; i--) writeLandmark(allCities.landmarkLocation[i], allCities.iconType[i]);
}

bool Map::isCityLocation(int locationValue){
    switch (locationValue)
    {
        case City1Location:
            return true;
        case City2Location:
            return true;
        case City3Location:
            return true;
        case City4Location:
            return true;
        case City5Location:
            return true;
        case City6Location:
            return true;
        default:
            return false;
    }
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

void Map::fillInMap(int landmarkLocation){
    int const tempmaxRow = getMapCityStandardMaxRow() + optionsHeight;
    int pos[tempmaxRow][6];
    int value = getMapCityStandardMinRow()+ optionsHeight;
    switch(landmarkLocation){
        case City1Location:{
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
        case City2Location:{
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
        case City3Location:{
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
        case City4Location:{
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
        case City5Location:{
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
        case City6Location:{
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
            menu.displayMessageWithPause(0,0, "failed void Map::fillInMap(int landmarkLocation){ " , false, false);
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