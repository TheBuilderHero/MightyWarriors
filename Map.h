#include <string>
#include "TempEntity.h"

#pragma once

class Map{
    private:
        TempEntity player;
        int maxColumn, minColumn;
        int maxRow, minRow;

        struct coords
        {
            // data 
            int x;
            int y;
        };
        coords possibleTravelLocations[500]; //these are all the places coordinates which a player can travel
        int currentLocation;
        std::string mapBlank = " ";
        std::string mapFilled = "X";
        std::string mapUnfilled = "0";//to_string(locationConfirmedCount);

    public:
        void listAvalibleLocations(std::string username);
        void displayMapOutline();
        TempEntity getPlayer(){ return player ;}
        void setPlayer(TempEntity playerE){ player = playerE; }
        void displayLocations(); //displays world map
        void displayLocations(int city); //displays map of city
        void displayLocations(int city, int town); //displays map of town

        void setCurrentLocation(int num) { currentLocation = num; }
        bool canMoveFromCurrentLocation(int directionValue);
        int getCurrentLocation() {if (currentLocation > 0) { return currentLocation;} else { return currentLocation = 1; } }

        /*
        void setPossibleTravelLocations(int num, int x, int y) { possibleTravelLocations[num].x = x; possibleTravelLocations[num].y = y; std::cout << " xs: " << possibleTravelLocations[num].x << " ys: " << possibleTravelLocations[num].y << std::endl; }
        */
        int getPossibleTravelLocationsX(int num) { return possibleTravelLocations[num].x; }
        int getPossibleTravelLocationsY(int num) { return possibleTravelLocations[num].y; }

        std::string getMapBlank() { return mapBlank; }
        std::string getMapFilled() { return mapFilled; }
        std::string getMapUnfilled() { return mapUnfilled; }
};