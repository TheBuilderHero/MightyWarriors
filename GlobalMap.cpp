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
            if(mapping.at(i).at(i2)) {
                menu.display(getConsoleXFromMapX(i2), getConsoleYFromMapY(i), unfilledMapIcon, true, false, 43);
                if(previousIndexWasLand){ //for setting green in between locations but not on the far side of the islands
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 43);
                }
                if(previousIndexWasWater){//for filling in the water
                    menu.display(getConsoleXFromMapX(i2)-1, getConsoleYFromMapY(i)," ", true, false, 16);
                }
                previousIndexWasLand = true;
                previousIndexWasWater = false;
            } else {
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
void GlobalMap::displayPlayerPostion(){
    int x = player.getMapLocationX();
    int y = player.getMapLocationY();
    //int location = player.getLocation();
    //x = getConsoleXFromMapX(getMapX(location));
    //y = getConsoleYFromMapY(getMapY(location));
    //menu.displayMessageWithPause(0,0,"x:"+to_string(x),false, true);
    //menu.displayMessageWithPause(0,1,"y:"+to_string(y),false, true);
    
    menu.display(getConsoleXFromMapX(x),getConsoleYFromMapY(y), "x",true,false,41);
}

int GlobalMap::getMapMaxPositionX(){
    //Note we subtact one because we are including zero
    return columnOffset+COLUMN_SCALER*(mapping.at(1).size()-1); //just picked a random value because all the rows and columns have the same size
}
int GlobalMap::getMapMaxPositionY(){
    //Note we subtact one because we are including zero:
    return rowOffset+mapping.size()-1;
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


void GlobalMap::travelMap(){
        string failedTravelMSG = "Failed Travel!";
        int TRAVEL_MESSAGE_ERROR_X = 30;
        int TRAVEL_MESSAGE_ERROR_Y = 5;
        int x = player.getMapLocationX();
        int y = player.getMapLocationY();
        bool canTravel = false;
    while(true){
        int oldX = x;
        int oldY = y;
        int pressedKey = menu.arrowPressWait();
        //Now that a new option has been selected clear the Failed Travel message
        menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y, string(failedTravelMSG.length(), ' '));

        //int currentLocation = player.getLocation();
        //x = getMapX(currentLocation);
        //y = getMapY(currentLocation);
        switch(pressedKey){
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
        if(canTravel) menu.display(getConsoleXFromMapX(oldX), getConsoleYFromMapY(oldY), unfilledMapIcon, true, false, 43);
    }
}
