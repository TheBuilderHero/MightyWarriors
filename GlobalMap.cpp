#include <cmath>
//#include "GlobalMap.h"
#include "GlobalVariables.h"
#include "Battle.h"
#include "Menu.h"

#include <string>

using namespace std;

GlobalMap::GlobalMap(){ //sets the players starting position on the map
    //this order can only be changed by changing the order in enum LandmarkMapChoice:
    landmarkMaps.emplace_back(landmark_City); //city is index 0
    landmarkMaps.emplace_back(landmark_Cave); //cave is index 1
    if(true){
        player.setMapLocation(9,9);
    }
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
            if(mapping.at(i).at(i2) < RESERVED_MAP_VALUE_MIN && mapping.at(i).at(i2) > 0) { //PLAIN LAND
                menu.display(getConsoleXFromMapXForMap(i2), getConsoleYFromMapYForMap(i), UNFILLED_MAP_ICON, true, false, 43);
                if(previousIndexWasLand){ //for setting green in between locations but not on the far side of the islands
                    menu.display(getConsoleXFromMapXForMap(i2)-1, getConsoleYFromMapYForMap(i)," ", true, false, 43);
                }
                if(previousIndexWasWater){//for filling in the water
                    menu.display(getConsoleXFromMapXForMap(i2)-1, getConsoleYFromMapYForMap(i)," ", true, false, 16);
                }
                previousIndexWasLand = true;
                previousIndexWasWater = false;
            } else if(mapping.at(i).at(i2) >= RESERVED_MAP_VALUE_MIN && mapping.at(i).at(i2) <= RESERVED_MAP_VALUE_MAX) { //LANDMARK LOCATIONs
                menu.display(getConsoleXFromMapXForMap(i2), getConsoleYFromMapYForMap(i), icon(i2,i), true, false, 43);
                if(previousIndexWasLand){ //for setting green in between locations but not on the far side of the islands
                    menu.display(getConsoleXFromMapXForMap(i2)-1, getConsoleYFromMapYForMap(i)," ", true, false, 43);
                }
                if(previousIndexWasWater){//for filling in the water
                    menu.display(getConsoleXFromMapXForMap(i2)-1, getConsoleYFromMapYForMap(i)," ", true, false, 16);
                }
                previousIndexWasLand = true;
                previousIndexWasWater = false;
            } else {                                              //WATER LOCATIONS
                menu.display(getConsoleXFromMapXForMap(i2), getConsoleYFromMapYForMap(i)," ", true, false, 16);
                if(previousIndexWasWater){ //for filling in the water
                    menu.display(getConsoleXFromMapXForMap(i2)-1, getConsoleYFromMapYForMap(i)," ", true, false, 16);
                }
                if(previousIndexWasLand){ //for setting green in between locations but not on the far side of the islands
                    menu.display(getConsoleXFromMapXForMap(i2)-1, getConsoleYFromMapYForMap(i)," ", true, false, 16);
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

    setX = getConsoleXFromMapXForMap(0)-OUTLINE_OFFSET;
    setY = getConsoleYFromMapYForMap(0)-OUTLINE_OFFSET;
    menu.display(setX,setY,"+");
    setY = getMapMaxPositionY()+OUTLINE_OFFSET;
    for (int posRow = getConsoleYFromMapYForMap(0); posRow < setY; posRow++){
        menu.display(setX,posRow,"|");
    }

    setY = getMapMaxPositionY()+OUTLINE_OFFSET;
    menu.display(setX,setY,"+");
    setX = getMapMaxPositionX()+OUTLINE_OFFSET;
    for (int posColumn = getConsoleXFromMapXForMap(0); posColumn < setX; posColumn++){
        menu.display(posColumn,setY,"-");
    }
    
    menu.display(setX, setY,"+");
    setY = getConsoleYFromMapYForMap(0)-OUTLINE_OFFSET;
    for (int posRow = getMapMaxPositionY(); setY < posRow; posRow--){
        menu.display(setX,posRow,"|");
    }

    menu.display(setX, setY,"+");
    setX = getConsoleXFromMapXForMap(0)-OUTLINE_OFFSET;
    for (int posColumn = getMapMaxPositionX(); setX < posColumn; posColumn--){
        menu.display(posColumn,setY,"-");
    }
}
void GlobalMap::displayPlayerPostion(){
    int x = player.getMapLocationX();
    int y = player.getMapLocationY();

    //menu.displayMessageWithPause(0,0,"x:"+to_string(x));
    //menu.displayMessageWithPause(0,0,"y:"+to_string(y));
    
    menu.display(getConsoleXFromMapXForMap(x),getConsoleYFromMapYForMap(y), playerIcon(x,y),true,false,41);
}

void GlobalMap::displayLandmarkMap(){
    bool previousIndexWasLand = false;
    bool previousIndexWasWater = false;
    for(int i = 0; i < landmarkMaps.at(landmarkMapChoice).size(); i++){
        previousIndexWasLand = false;
        previousIndexWasWater = false;
        for(int i2 = 0; i2 < landmarkMaps.at(landmarkMapChoice).at(i).size(); i2++){
            //all values greater than 0 will be land and those less than 0 will be water
            //Note: other values greater than 89 have other useful purposes like 99 for city locations 
            if(landmarkMaps.at(landmarkMapChoice).at(i).at(i2) < RESERVED_LANDMARK_VALUE_MIN && landmarkMaps.at(landmarkMapChoice).at(i).at(i2) > 0) { //PLAIN LAND
                menu.display(getConsoleXFromMapXForLandmark(i2), getConsoleYFromMapYForLandmark(i), UNFILLED_LANDMARK_MAP_ICON, true, false, 43);
                if(previousIndexWasLand){ //for setting green in between locations but not on the far side of the islands
                    menu.display(getConsoleXFromMapXForLandmark(i2)-1, getConsoleYFromMapYForLandmark(i)," ", true, false, 43);
                }
                if(previousIndexWasWater){//for filling in the water
                    menu.display(getConsoleXFromMapXForLandmark(i2)-1, getConsoleYFromMapYForLandmark(i)," ", true, false, 15);
                }
                previousIndexWasLand = true;
                previousIndexWasWater = false;
            } else if(landmarkMaps.at(landmarkMapChoice).at(i).at(i2) >= RESERVED_LANDMARK_VALUE_MIN && landmarkMaps.at(landmarkMapChoice).at(i).at(i2) <= RESERVED_LANDMARK_VALUE_MAX) { //CITY LOCATIONS
                menu.display(getConsoleXFromMapXForLandmark(i2), getConsoleYFromMapYForLandmark(i), iconsInLandmark(i2,i), true, false, 43);
                if(previousIndexWasLand){ //for setting green in between locations but not on the far side of the islands
                    menu.display(getConsoleXFromMapXForLandmark(i2)-1, getConsoleYFromMapYForLandmark(i)," ", true, false, 43);
                }
                if(previousIndexWasWater){//for filling in the water
                    menu.display(getConsoleXFromMapXForLandmark(i2)-1, getConsoleYFromMapYForLandmark(i)," ", true, false, 15);
                }
                previousIndexWasLand = true;
                previousIndexWasWater = false;
            } else {                                              //Black zone LOCATIONS for cities, caves, etc
                menu.display(getConsoleXFromMapXForLandmark(i2), getConsoleYFromMapYForLandmark(i)," ", true, false, 15);
                if(previousIndexWasWater){ //for filling in the water
                    menu.display(getConsoleXFromMapXForLandmark(i2)-1, getConsoleYFromMapYForLandmark(i)," ", true, false, 15);
                }
                if(previousIndexWasLand){ //for setting green in between locations but not on the far side of the islands
                    menu.display(getConsoleXFromMapXForLandmark(i2)-1, getConsoleYFromMapYForLandmark(i)," ", true, false, 15);
                }
                previousIndexWasLand = false;
                previousIndexWasWater = true;
            }
        }
    }
}
void GlobalMap::displayLandmarkMapOutline(){
    //then we have OUTLINE_OFFSET being used to take the map from overwriting the map to writing just around the outside of the map.
    int setX, setY;

    setX = getConsoleXFromMapXForLandmark(0)-OUTLINE_OFFSET;
    setY = getConsoleYFromMapYForLandmark(0)-OUTLINE_OFFSET;
    menu.display(setX,setY,"+");
    setY = getLandmarkMapMaxPositionY()+OUTLINE_OFFSET;
    for (int posRow = getConsoleYFromMapYForLandmark(0); posRow < setY; posRow++){
        menu.display(setX,posRow,"|");
    }

    setY = getLandmarkMapMaxPositionY()+OUTLINE_OFFSET;
    menu.display(setX,setY,"+");
    setX = getLandmarkMapMaxPositionX()+OUTLINE_OFFSET;
    for (int posColumn = getConsoleXFromMapXForLandmark(0); posColumn < setX; posColumn++){
        menu.display(posColumn,setY,"-");
    }
    
    menu.display(setX, setY,"+");
    setY = getConsoleYFromMapYForLandmark(0)-OUTLINE_OFFSET;
    for (int posRow = getLandmarkMapMaxPositionY(); setY < posRow; posRow--){
        menu.display(setX,posRow,"|");
    }

    menu.display(setX, setY,"+");
    setX = getConsoleXFromMapXForLandmark(0)-OUTLINE_OFFSET;
    for (int posColumn = getLandmarkMapMaxPositionX(); setX < posColumn; posColumn--){
        menu.display(posColumn,setY,"-");
    }
}
void GlobalMap::displayPlayerLandmarkPostion(int x, int y){
    menu.display(getConsoleXFromMapXForLandmark(x),getConsoleYFromMapYForLandmark(y), playerIconLandmark(x,y),true,false,41);
}

int GlobalMap::getMapMaxPositionX(){
    //Note we subtact one because we are including zero
    return COLUMN_OFFSET+COLUMN_SCALER*(mapping.at(1).size()-1); //just picked a random value because all the rows and columns have the same size
}
int GlobalMap::getMapMaxPositionY(){
    //Note we subtact one because we are including zero:
    return ROW_OFFSET+mapping.size()-1;
}
int GlobalMap::getLandmarkMapMaxPositionX(){
    //Note we subtact one because we are including zero
    return COLUMN_OFFSET_LANDMARK_MAP+COLUMN_SCALER*(landmarkMaps.at(landmarkMapChoice).at(1).size()-1); //just picked a random value because all the rows and columns have the same size
}
int GlobalMap::getLandmarkMapMaxPositionY(){
    //Note we subtact one because we are including zero:
    return ROW_OFFSET_LANDMARK_MAP+landmarkMaps.at(landmarkMapChoice).size()-1;
}

int GlobalMap::getConsoleXFromMapXForMap(int mapX){
    return COLUMN_OFFSET+(mapX*COLUMN_SCALER);
}
int GlobalMap::getConsoleYFromMapYForMap(int mapY){
    return ROW_OFFSET+mapY;
}
int GlobalMap::getConsoleXFromMapXForLandmark(int mapX){
    return COLUMN_OFFSET_LANDMARK_MAP+(mapX*COLUMN_SCALER_LANDMARK_MAP);
}
int GlobalMap::getConsoleYFromMapYForLandmark(int mapY){
    return ROW_OFFSET_LANDMARK_MAP+mapY;
}
int GlobalMap::getConsoleXFromLocation(int location){ //need to review this code
    int i = (double)location - (55.0*(double)((getConsoleYFromLocation(location)-ROW_OFFSET)-1)) + COLUMN_OFFSET;
    return i;
}
int GlobalMap::getConsoleYFromLocation(int location){
    int i = ceil((double)location / 55.0) + ROW_OFFSET;
    return i;
}
int GlobalMap::getMapX(int location){ //need to review this code
    int i = (double)location - (55.0*(double)((getMapY(location)-ROW_OFFSET)-1));
    return i;
}
int GlobalMap::getMapY(int location){
    int i = ceil((double)location / 55.0);
    return i;
}
string GlobalMap::icon(int mapX, int mapY){
    int locationValue = mapping.at(mapY).at(mapX);
    if(locationValue < RESERVED_MAP_VALUE_MIN && locationValue > 0){
        return UNFILLED_MAP_ICON;
    } else if (locationValue == LANDMARK_LOCATION_VALUE_CITY){
        return LANDMARK_MAP_ICON;
    } else if (locationValue == LANDMARK_LOCATION_VALUE_CAVE){
        return UNFILLED_MAP_ICON;
    } else {
        return UNFILLED_MAP_ICON;
    }
}
string GlobalMap::iconsInLandmark(int mapX, int mapY){
    int locationValue = landmarkMaps.at(landmarkMapChoice).at(mapY).at(mapX);
    if(locationValue < RESERVED_LANDMARK_VALUE_MIN && locationValue > 0){
        return UNFILLED_LANDMARK_MAP_ICON;
    } else if (locationValue == INTERACTION_LOCATION_VALUE){
        return NPC_LANDMARK_MAP_ICON;
    } else {
        return UNFILLED_LANDMARK_MAP_ICON;
    }
}
string GlobalMap::playerIcon(int mapX, int mapY){
    int locationValue = mapping.at(mapY).at(mapX);
    if(locationValue < RESERVED_MAP_VALUE_MIN && locationValue > 0){
        return PLAYER_MAP_ICON;
    } else if (locationValue == LANDMARK_LOCATION_VALUE_CITY){
        return LANDMARK_MAP_ICON;
    } else {
        return PLAYER_MAP_ICON;
    }
}
string GlobalMap::playerIconLandmark(int mapX, int mapY){
    int locationValue = landmarkMaps.at(landmarkMapChoice).at(mapY).at(mapX);
    if(locationValue < RESERVED_LANDMARK_VALUE_MIN && locationValue > 0){
        return PLAYER_LANDMARK_MAP_ICON;
    } else if (locationValue == INTERACTION_LOCATION_VALUE){
        return NPC_LANDMARK_MAP_ICON;
    } else {
        return PLAYER_LANDMARK_MAP_ICON;
    }
}

bool GlobalMap::isLocationLandmark(){ //this checks if a location is a landmark then if it is, it will set the landmarkMapChoice value to that corseponding map (the index values are defined in the constructor)
    int x = player.getMapLocationX();
    int y = player.getMapLocationY();
    if (mapping.at(y).at(x) == LANDMARK_LOCATION_VALUE_CITY){
        setLandmarkMapChoice(CITY);
        return true;
    } else if (mapping.at(y).at(x) == LANDMARK_LOCATION_VALUE_CAVE){
        setLandmarkMapChoice(CAVE);
        return true;
    }else {
        return false;
    }
}
bool GlobalMap::isLocationinLandmarkInteractive(int x, int y){
    if (landmarkMaps.at(landmarkMapChoice).at(y).at(x) == INTERACTION_LOCATION_VALUE){
        return true;
    } else {
        return false;
    }
}

void GlobalMap::promptInteraction(){
    //prompt for player to talk with person in city/cave/other:
    menu.display(getLandmarkMapMaxPositionX()+4, (getLandmarkMapMaxPositionY()/2)+5, "Would you like to talk with "+npcs.at(0).getNPCforMapXY(player.getMapLocationX(), player.getMapLocationY(), player.getLandmarkLocationX(), player.getLandmarkLocationY())+"? (Y/N)", true);
    char interact = menu.yesOrNo(); //returns y or n
    if (interact == 'y'){
        interactions.interact(); //add location in city to this
    } else {//do not enter city
        menu.clearDisplayRow(getLandmarkMapMaxPositionX()+5, (getLandmarkMapMaxPositionY()-(2*ROW_OFFSET_LANDMARK_MAP)));
    }
}

bool GlobalMap::checkForEncounter(){
    //the following is code for the other travel system that probably needs some slight adjustments to the current system:
    bool encounter = false;
    srand(time(NULL)); 
    if(rand() % 2 == 0){ //1 in 15
        encounter = true;
    }
    //does not seem we need the folowing:
    //int locationX = player.getMapLocationX();
    //int locationY = player.getMapLocationY();
    //getTravelMessage(player.getLocation(), direction);
    if(encounter){
        menu.setStillSimpleTraveling(false);//no longer simple traveling (The cmd will have to re-output the travel menu.)
        menu.clearDisplayRow(2);
        menu.display(30, 2, "ENCOUNTER!");
        menu.waitForEnter(menu.getEnterKeyState());
        Battle battle;
        //battle.setPlayer(player);
        battle.questBattle(player.getUsername(), 100, 10);
        //setPlayer(battle.getPlayer());
        if(!player.getBattleResult()){
            menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
            menu.display(30, 2, "Having been defeated, you return crying to whence you came.");
            menu.waitForEnter(menu.getEnterKeyState());
            //cout << "still Traveling? " << menu.getStillSimpleTraveling();
            //menu.waitForEnter(menu.getEnterKeyState());
            return true;
        }else{
            //cout << "still Traveling? " << menu.getStillSimpleTraveling();
            menu.display(30, 2, "You may resume travelling now.");
            menu.waitForEnter(menu.getEnterKeyState());
            player.setBattleResult(false);
        }        
    } else {
        //menu.clearDisplayRow(2);
        menu.display(30, 4, "You moved hooray!");
    }
    return encounter;
}

void GlobalMap::travelLandmark(){
    bool leaveMapTravling = false;
    bool canTravel = false;
    bool printMap = true;
    string failedTravelMSG = "Failed Travel!";
    //starting x,y
    int x = player.getLandmarkLocationX();
    int y = player.getLandmarkLocationY();
    int TRAVEL_MESSAGE_ERROR_X = 42;
    int TRAVEL_MESSAGE_ERROR_Y = 4;
    //Now that a new option has been selected clear the Failed Travel message
    int oldX = x;
    int oldY = y;
    while(!leaveMapTravling){
        oldX = x;
        oldY = y;
        if(printMap) {
            menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");

            menu.display(47, 1, "Traveling");
            menu.display(32, 2, "Use Arrow Keys to navegate the Landmark");
            menu.display(32, 3, "Press 0 to Return to Menu");
            displayLandmarkMap();
            displayLandmarkMapOutline();
            displayPlayerLandmarkPostion(x,y);
            printMap = false;
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
                    if(landmarkMaps.at(landmarkMapChoice).at(y-1).at(x)) {
                        canTravel = true;
                        --y;
                        player.setLandmarkLocation(x,y); //this is only updated so that we can check the player's location through other functions 
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
                if(x<landmarkMaps.at(landmarkMapChoice).at(y).size()-1) {
                    if(landmarkMaps.at(landmarkMapChoice).at(y).at(x+1)) {
                        canTravel = true;
                        ++x;
                        player.setLandmarkLocation(x,y); //this is only updated so that we can check the player's location through other functions 
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
                if(y<landmarkMaps.at(landmarkMapChoice).size()-1) {
                    if(landmarkMaps.at(landmarkMapChoice).at(y+1).at(x)) {
                        canTravel = true;
                        ++y;
                        player.setLandmarkLocation(x,y); //this is only updated so that we can check the player's location through other functions 
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
                    if(landmarkMaps.at(landmarkMapChoice).at(y).at(x-1)) {
                        canTravel = true;
                        --x;
                        player.setLandmarkLocation(x,y); //this is only updated so that we can check the player's location through other functions 
                    } else {
                        menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                    }
                } else {
                    menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                }
                break;
            }
        }
        if(!leaveMapTravling){
            //display new player position:
            displayPlayerLandmarkPostion(x,y);
            //write map icon to old player position if they traveled to a new location successfully:
            if(canTravel) menu.display(getConsoleXFromMapXForLandmark(oldX), getConsoleYFromMapYForLandmark(oldY), iconsInLandmark(oldX,oldY), true, false, 43);
            if(isLocationinLandmarkInteractive(x,y)) {
                printMap = true;
                promptInteraction();
            }
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
        int oldX = x;
        int oldY = y;
    while(!leaveMapTravling){
        oldX = x;
        oldY = y;
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
                        guard.setPlayerMapLocationX(x);
                        guard.setPlayerMapLocationY(y);
                        if(checkForEncounter()) printMap = true;
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
                if(x<mapping.at(y).size()-1) {
                    if(mapping.at(y).at(x+1)) {
                        canTravel = true;
                        player.setMapLocation(++x,y);
                        guard.setPlayerMapLocationX(x);
                        guard.setPlayerMapLocationY(y);
                        if(checkForEncounter()) printMap = true;
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
                if(y<mapping.size()-1) {
                    if(mapping.at(y+1).at(x)) {
                        canTravel = true;
                        player.setMapLocation(x,++y);
                        guard.setPlayerMapLocationX(x);
                        guard.setPlayerMapLocationY(y);
                        if(checkForEncounter()) printMap = true;
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
                        guard.setPlayerMapLocationX(x);
                        guard.setPlayerMapLocationY(y);
                        if(checkForEncounter()) printMap = true;
                    } else {
                        menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                    }
                } else {
                    menu.display(TRAVEL_MESSAGE_ERROR_X,TRAVEL_MESSAGE_ERROR_Y,failedTravelMSG);
                }
                break;
            }
        }
        if(!leaveMapTravling){
            //display new player position:
            displayPlayerPostion(); 
            //write map icon to old player position if they traveled to a new location successfully:
            if(canTravel) menu.display(getConsoleXFromMapXForMap(oldX), getConsoleYFromMapYForMap(oldY), icon(oldX,oldY), true, false, 43);
            if(isLocationLandmark()) {
                printMap = true;
                player.setLandmarkLocation(LANDMARK_START_X,LANDMARK_START_Y);
                travelLandmark();
            }
        }
    }
}