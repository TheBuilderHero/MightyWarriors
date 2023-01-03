#include <cmath>
#include "GlobalMap.h"
#include "Menu.h"

#include <string>

using namespace std;

GlobalMap::GlobalMap(){
    player.setMapLocation(9,9);
}

void GlobalMap::displayMap(){
    bool previousIndexWasLand = false;
    bool previousIndexWasWater = false;
    for(int i = 0; i < mapping.size(); i++){
        previousIndexWasLand = false;
        previousIndexWasWater = false;
        for(int i2 = 0; i2 < mapping.at(i).size(); i2++){
            //all values greater than 0 will be land and those less than 0 will be water
            //Note: other values greater than 89 have other useful purposes like 99 for city locations 
            if(mapping.at(i).at(i2) < 90 && mapping.at(i).at(i2) > 0) { //PLAIN LAND
                menu.display(getConsoleXFromMapX(i2), getConsoleYFromMapY(i), UNFILLED_MAP_ICON, true, false, 43);
                if(previousIndexWasLand){ //for setting green in between locations but not on the far side of the islands
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 43);
                }
                if(previousIndexWasWater){//for filling in the water
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 16);
                }
                previousIndexWasLand = true;
                previousIndexWasWater = false;
            } else if(mapping.at(i).at(i2) == LANDMARK_LOCATION_VALUE) { //CITY LOCATIONS
                menu.display(getConsoleXFromMapX(i2), getConsoleYFromMapY(i), LANDMARK_MAP_ICON, true, false, 43);
                if(previousIndexWasLand){ //for setting green in between locations but not on the far side of the islands
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 43);
                }
                if(previousIndexWasWater){//for filling in the water
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 16);
                }
                previousIndexWasLand = true;
                previousIndexWasWater = false;
            } else {                                              //WATER LOCATIONS
                menu.display(getConsoleXFromMapX(i2), getConsoleYFromMapY(i)," ", true, false, 16);
                if(previousIndexWasWater){ //for filling in the water
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 16);
                }
                if(previousIndexWasLand){ //for setting green in between locations but not on the far side of the islands
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 16);
                }
                previousIndexWasLand = false;
                previousIndexWasWater = true;
            }
        }
    }
}
void GlobalMap::displayLandmarkMap(){
    bool previousIndexWasLand = false;
    bool previousIndexWasWater = false;
    for(int i = 0; i < landmarkMapping.size(); i++){
        previousIndexWasLand = false;
        previousIndexWasWater = false;
        for(int i2 = 0; i2 < landmarkMapping.at(i).size(); i2++){
            //all values greater than 0 will be land and those less than 0 will be water
            //Note: other values greater than 89 have other useful purposes like 99 for city locations 
            if(landmarkMapping.at(i).at(i2) < 90 && landmarkMapping.at(i).at(i2) > 0) { //PLAIN LAND
                menu.display(getConsoleXFromMapX(i2), getConsoleYFromMapY(i), UNFILLED_MAP_ICON, true, false, 43);
                if(previousIndexWasLand){ //for setting green in between locations but not on the far side of the islands
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 43);
                }
                if(previousIndexWasWater){//for filling in the water
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 16);
                }
                previousIndexWasLand = true;
                previousIndexWasWater = false;
            } else if(landmarkMapping.at(i).at(i2) == LANDMARK_LOCATION_VALUE) { //CITY LOCATIONS
                menu.display(getConsoleXFromMapX(i2), getConsoleYFromMapY(i), LANDMARK_MAP_ICON, true, false, 43);
                if(previousIndexWasLand){ //for setting green in between locations but not on the far side of the islands
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 43);
                }
                if(previousIndexWasWater){//for filling in the water
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 16);
                }
                previousIndexWasLand = true;
                previousIndexWasWater = false;
            } else {                                              //WATER LOCATIONS
                menu.display(getConsoleXFromMapX(i2), getConsoleYFromMapY(i)," ", true, false, 16);
                if(previousIndexWasWater){ //for filling in the water
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 16);
                }
                if(previousIndexWasLand){ //for setting green in between locations but not on the far side of the islands
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 16);
                }
                previousIndexWasLand = false;
                previousIndexWasWater = true;
            }
        }
    }
}
void GlobalMap::displayMapOutline(){
    //then we have OUTLINE_OFFSET being used to take the map from overwriting the map to writing just around the outside of the map.
    int setX, setY;

    setX = getConsoleXFromMapX(0)-OUTLINE_OFFSET;
    setY = getConsoleYFromMapY(0)-OUTLINE_OFFSET;
    menu.display(setX,setY,"+");
    setY = getMapMaxPositionY()+OUTLINE_OFFSET;
    for (int posRow = getConsoleYFromMapY(0); posRow < setY; posRow++){
        menu.display(setX,posRow,"|");
    }

    setY = getMapMaxPositionY()+OUTLINE_OFFSET;
    menu.display(setX,setY,"+");
    setX = getMapMaxPositionX()+OUTLINE_OFFSET;
    for (int posColumn = getConsoleXFromMapX(0); posColumn < setX; posColumn++){
        menu.display(posColumn,setY,"-");
    }
    
    menu.display(setX, setY,"+");
    setY = getConsoleYFromMapY(0)-OUTLINE_OFFSET;
    for (int posRow = getMapMaxPositionY(); setY < posRow; posRow--){
        menu.display(setX,posRow,"|");
    }

    menu.display(setX, setY,"+");
    setX = getConsoleXFromMapX(0)-OUTLINE_OFFSET;
    for (int posColumn = getMapMaxPositionX(); setX < posColumn; posColumn--){
        menu.display(posColumn,setY,"-");
    }
}
void GlobalMap::displayLandmarkMapOutline(){
    //then we have OUTLINE_OFFSET being used to take the map from overwriting the map to writing just around the outside of the map.
    int setX, setY;

    setX = getConsoleXFromMapX(0)-OUTLINE_OFFSET;
    setY = getConsoleYFromMapY(0)-OUTLINE_OFFSET;
    menu.display(setX,setY,"+");
    setY = getLandmarkMapMaxPositionY()+OUTLINE_OFFSET;
    for (int posRow = getConsoleYFromMapY(0); posRow < setY; posRow++){
        menu.display(setX,posRow,"|");
    }

    setY = getLandmarkMapMaxPositionY()+OUTLINE_OFFSET;
    menu.display(setX,setY,"+");
    setX = getLandmarkMapMaxPositionX()+OUTLINE_OFFSET;
    for (int posColumn = getConsoleXFromMapX(0); posColumn < setX; posColumn++){
        menu.display(posColumn,setY,"-");
    }
    
    menu.display(setX, setY,"+");
    setY = getConsoleYFromMapY(0)-OUTLINE_OFFSET;
    for (int posRow = getLandmarkMapMaxPositionY(); setY < posRow; posRow--){
        menu.display(setX,posRow,"|");
    }

    menu.display(setX, setY,"+");
    setX = getConsoleXFromMapX(0)-OUTLINE_OFFSET;
    for (int posColumn = getLandmarkMapMaxPositionX(); setX < posColumn; posColumn--){
        menu.display(posColumn,setY,"-");
    }
}
void GlobalMap::displayPlayerPostion(){
    int x = player.getMapLocationX();
    int y = player.getMapLocationY();
    //int location = player.getLocation();
    //x = getConsoleXFromMapX(getMapX(location));
    //y = getConsoleYFromMapY(getMapY(location));
    //menu.displayMessageWithPause(0,0,"x:"+to_string(x),false, true);
    //menu.displayMessageWithPause(0,1,"y:"+to_string(y),false, true);
    
    menu.display(getConsoleXFromMapX(x),getConsoleYFromMapY(y), playerIcon(x,y),true,false,41);
}
void GlobalMap::displayPlayerLandmarkPostion(int x, int y){
    menu.display(getConsoleXFromMapX(x),getConsoleYFromMapY(y), playerIcon(x,y),true,false,41);
}

int GlobalMap::getMapMaxPositionX(){
    //Note we subtact one because we are including zero
    return columnOffset+COLUMN_SCALER*(mapping.at(1).size()-1); //just picked a random value because all the rows and columns have the same size
}
int GlobalMap::getMapMaxPositionY(){
    //Note we subtact one because we are including zero:
    return rowOffset+mapping.size()-1;
}
int GlobalMap::getLandmarkMapMaxPositionX(){
    //Note we subtact one because we are including zero
    return columnOffset+COLUMN_SCALER*(landmarkMapping.at(1).size()-1); //just picked a random value because all the rows and columns have the same size
}
int GlobalMap::getLandmarkMapMaxPositionY(){
    //Note we subtact one because we are including zero:
    return rowOffset+landmarkMapping.size()-1;
}

int GlobalMap::getConsoleXFromMapX(int mapX){
    return columnOffset+(mapX*COLUMN_SCALER);
}
int GlobalMap::getConsoleYFromMapY(int mapY){
    return rowOffset+mapY;
}
int GlobalMap::getConsoleXFromLocation(int location){ //need to review this code
    int i = (double)location - (55.0*(double)((getConsoleYFromLocation(location)-rowOffset)-1)) + columnOffset;
    return i;
}
int GlobalMap::getConsoleYFromLocation(int location){
    int i = ceil((double)location / 55.0) + rowOffset;
    return i;
}
int GlobalMap::getMapX(int location){ //need to review this code
    int i = (double)location - (55.0*(double)((getMapY(location)-rowOffset)-1));
    return i;
}
int GlobalMap::getMapY(int location){
    int i = ceil((double)location / 55.0);
    return i;
}
string GlobalMap::icon(int mapX, int mapY){
    int locationValue = mapping.at(mapY).at(mapX);
    if(locationValue < 90 && locationValue > 0){
        return UNFILLED_MAP_ICON;
    } else if (locationValue == LANDMARK_LOCATION_VALUE){
        return LANDMARK_MAP_ICON;
    } else {
        return UNFILLED_MAP_ICON;
    }
}
string GlobalMap::iconLandmark(int mapX, int mapY){
    int locationValue = landmarkMapping.at(mapY).at(mapX);
    if(locationValue < 90 && locationValue > 0){
        return UNFILLED_MAP_ICON;
    } else if (locationValue == LANDMARK_LOCATION_VALUE){
        return LANDMARK_MAP_ICON;
    } else {
        return UNFILLED_MAP_ICON;
    }
}
string GlobalMap::playerIcon(int mapX, int mapY){
    int locationValue = mapping.at(mapY).at(mapX);
    if(locationValue < 90 && locationValue > 0){
        return PLAYER_MAP_ICON;
    } else if (locationValue == LANDMARK_LOCATION_VALUE){
        return LANDMARK_MAP_ICON;
    } else {
        return PLAYER_MAP_ICON;
    }
}
string GlobalMap::playerIconLandmark(int mapX, int mapY){
    int locationValue = landmarkMapping.at(mapY).at(mapX);
    if(locationValue < 90 && locationValue > 0){
        return PLAYER_MAP_ICON;
    } else if (locationValue == LANDMARK_LOCATION_VALUE){
        return LANDMARK_MAP_ICON;
    } else {
        return PLAYER_MAP_ICON;
    }
}

bool GlobalMap::isLocationLandmark(){
    int x = player.getMapLocationX();
    int y = player.getMapLocationY();
    if (mapping.at(y).at(x) == LANDMARK_LOCATION_VALUE){
        return true;
    } else {
        return false;
    }
}
bool GlobalMap::isLocationInteractive(int x, int y){
    if (landmarkMapping.at(y).at(x) == LANDMARK_LOCATION_VALUE){
        return true;
    } else {
        return false;
    }
}

void GlobalMap::promptInteraction(){

}

void GlobalMap::travelLandmark(){
    bool leaveMapTravling = false;
    bool canTravel = false;
    bool printMap = true;
    string failedTravelMSG = "Failed Travel!";
    //starting x,y
    int x = 0;
    int y = 4;
    int TRAVEL_MESSAGE_ERROR_X = 42;
    int TRAVEL_MESSAGE_ERROR_Y = 4;
    //Now that a new option has been selected clear the Failed Travel message
    while(!leaveMapTravling){
        int oldX = x;
        int oldY = y;
        if(printMap) {
            menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");

            menu.display(47, 1, "Traveling");
            menu.display(32, 2, "Use Arrow Keys to navegate the Landmark");
            menu.display(32, 3, "Press 0 to Return to Menu");
            displayLandmarkMap();
            displayLandmarkMapOutline();
            displayPlayerLandmarkPostion(x,y);
        }
        int pressedKey = menu.arrowPressWait(true);
        if(!canTravel) menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y, string(failedTravelMSG.length(), ' '));
        switch(pressedKey){
            case 0:{
                leaveMapTravling = true;
                break;
            }
            case 1:{
                canTravel = false;
                if(y>0) {
                    if(landmarkMapping.at(y-1).at(x)) {
                    canTravel = true;
                    player.setMapLocation(x,--y);
                    } else {
                        menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                    }
                } else {
                    menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                }
                break;
            }
            case 2:{
                canTravel = false;
                if(x<landmarkMapping.at(y).size()) {
                    if(landmarkMapping.at(y).at(x+1)) {
                    canTravel = true;
                    player.setMapLocation(++x,y);
                    } else {
                        menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                    }
                } else {
                    menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                }
                break;
            }
            case 3:{
                canTravel = false;
                if(y<landmarkMapping.size()) {
                    if(landmarkMapping.at(y+1).at(x)) {
                    canTravel = true;
                    player.setMapLocation(x,++y);
                    } else {
                        menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                    }
                } else {
                    menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                }
                break;
            }
            case 4:{
                canTravel = false;
                if(x>0) {
                    if(landmarkMapping.at(y).at(x-1)) {
                    canTravel = true;
                    player.setMapLocation(--x,y);
                    } else {
                        menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                    }
                } else {
                    menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                }
                break;
            }
        }
        
        //display new player position:
        displayPlayerLandmarkPostion(x,y);
        //write map icon to old player position if they traveled to a new location successfully:
        if(canTravel) menu.display(getConsoleXFromMapX(oldX), getConsoleYFromMapY(oldY), icon(oldX,oldY), true, false, 43);
        if(isLocationInteractive(x,y)) {
            printMap = true;
            promptInteraction();
        }
    }
}

void GlobalMap::travelMap(){
        string failedTravelMSG = "Failed Travel!";
        int TRAVEL_MESSAGE_ERROR_X = 42;
        int TRAVEL_MESSAGE_ERROR_Y = 4;
        int x = player.getMapLocationX();
        int y = player.getMapLocationY();
        bool leaveMapTravling = false;
        bool printMap = true;
        bool canTravel = false;
    while(!leaveMapTravling){
        int oldX = x;
        int oldY = y;
        if(printMap) {
            menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
            
            displayMap();
            displayMapOutline();
            displayPlayerPostion();

            menu.display(47, 1, "Traveling");
            menu.display(32, 2, "Use Arrow Keys to navegate the Map");
            menu.display(32, 3, "Press 0 to Return to Menu");
            printMap = false;
        }
        int pressedKey = menu.arrowPressWait(true);
        //Now that a new option has been selected clear the Failed Travel message
        if(!canTravel) menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y, string(failedTravelMSG.length(), ' '));

        //int currentLocation = player.getLocation();
        //x = getMapX(currentLocation);
        //y = getMapY(currentLocation);
        switch(pressedKey){
            case 0:{
                leaveMapTravling = true;
                break;
            }
            case 1:{
                canTravel = false;
                if(y>0) {
                    if(mapping.at(y-1).at(x)) {
                    canTravel = true;
                    player.setMapLocation(x,--y);
                    } else {
                        menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                    }
                } else {
                    menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                }
                break;
            }
            case 2:{
                canTravel = false;
                if(x<mapping.at(y).size()) {
                    if(mapping.at(y).at(x+1)) {
                    canTravel = true;
                    player.setMapLocation(++x,y);
                    } else {
                        menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                    }
                } else {
                    menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                }
                break;
            }
            case 3:{
                canTravel = false;
                if(y<mapping.size()) {
                    if(mapping.at(y+1).at(x)) {
                    canTravel = true;
                    player.setMapLocation(x,++y);
                    } else {
                        menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                    }
                } else {
                    menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                }
                break;
            }
            case 4:{
                canTravel = false;
                if(x>0) {
                    if(mapping.at(y).at(x-1)) {
                    canTravel = true;
                    player.setMapLocation(--x,y);
                    } else {
                        menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                    }
                } else {
                    menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                }
                break;
            }
        }
        //display new player position:
        displayPlayerPostion(); 
        //write map icon to old player position if they traveled to a new location successfully:
        if(canTravel) menu.display(getConsoleXFromMapX(oldX), getConsoleYFromMapY(oldY), icon(oldX,oldY), true, false, 43);
        if(isLocationLandmark()) {
            printMap = true;
            travelLandmark();
        }
    }
}
