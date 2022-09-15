#include <string>
#include "TempEntity.h"

#pragma once

class Map{
    private:
        TempEntity player;
        int optionsHeight = 6;
        int maxRow, minRow;
        int maxColumn, minColumn;
        static const int mapStandardMaxColumn = 170, mapStandardMaxRow = 42;
        static const int mapStandardMinColumn = 2, mapStandardMinRow = 1;
        static const int locationCount = 800;
        static const int CityCount = 6;
        static const int City1Location = 637, City2Location = 602, City3Location = 603, City4Location = 604, City5Location = 605, City6Location = 606;
        int initalPosRow = minRow = 1 + optionsHeight;
        int initalPosColumn = minColumn = 2;
        struct cities{
            int cityLocation[CityCount+1]; //the +1 allows us to use the nice 1 - 6 values instead of 0 - 5
            std::string iconType[CityCount+1];
        };
        cities allCities;

        struct coords
        {
            // data 
            int x;
            int y;
        };
        coords possibleTravelLocations[locationCount]; //these are all the places coordinates which a player can travel
        int currentLocation;
        std::string mapBlank = " ";
        std::string mapFilled = "X";
        std::string mapUnfilled = " ";
        std::string mapCity = "0";

    public:
        Map();
        void listAvalibleLocations(std::string username);
        void displayMapOutline(int maxColumnInput = mapStandardMaxColumn, int maxRowInput = mapStandardMaxRow, int minColumnInput = mapStandardMinColumn, int minRowInput = mapStandardMinRow);
        void fillInMap(); //displays world map
        void fillInMap(int city); //displays map of city
        void fillInMap(int city, int town); //displays map of town
        void writeLandmark(int locationValue, std::string iconType);
        void writeLandmarks();


        TempEntity getPlayer(){ return player ;}
        void setPlayer(TempEntity playerE){ player = playerE; }

        bool isCityLocation(int locationValue);

        void setCurrentLocation(int num) { currentLocation = num; }
        bool canMoveFromCurrentLocation(int directionValue);
        int getCurrentLocation() {if (currentLocation > 0) { return currentLocation;} else { return currentLocation = 1; } }

        /*
        void setPossibleTravelLocations(int num, int x, int y) { possibleTravelLocations[num].x = x; possibleTravelLocations[num].y = y; std::cout << " xs: " << possibleTravelLocations[num].x << " ys: " << possibleTravelLocations[num].y << std::endl; }
        */
        int getPossibleTravelLocationsX(int num) { return possibleTravelLocations[num].x; }
        int getPossibleTravelLocationsY(int num) { return possibleTravelLocations[num].y; }
        int getMapStandardMaxColumn(){ return mapStandardMaxColumn; }
        int getMapStandardMaxRow(){ return mapStandardMaxRow; }
        int getMapStandardMinColumn(){ return mapStandardMinColumn; }
        int getMapStandardMinRow(){ return mapStandardMinRow; }
        cities getAllCities(){ return allCities; }
        int getCityCount(){ return CityCount; }


        std::string getMapBlank() { return mapBlank; }
        std::string getMapFilled() { return mapFilled; }
        std::string getMapUnfilled() { return mapUnfilled; }
        std::string getMapCity() { return mapCity; }
};