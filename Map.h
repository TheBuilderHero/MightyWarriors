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
        static const int mapCityStandardMaxColumn = 94, mapCityStandardMaxRow = 26;
        static const int mapCityStandardMinColumn = 74, mapCityStandardMinRow = 16;
        static const int locationCount = 800;
        static const int locationCountLandmark = 200;
        static const int CityCount = 6;
        static const int City1Location = 127, City2Location = 217, City3Location = 285, City4Location = 310, City5Location = 506, City6Location = 637;
        int initalPosRow = minRow = 1 + optionsHeight;
        int initalPosColumn = minColumn = 2;
        struct landmarks{
            int landmarkLocation[CityCount+1]; //the +1 allows us to use the nice 1 - 6 values instead of 0 - 5
            std::string iconType[CityCount+1];
        };
        landmarks allCities;

        struct coords
        {
            // data 
            int x;
            int y;
        };
        coords possibleTravelLocations[locationCount][locationCountLandmark]; //these are all the places coordinates which a player can travel
        int currentLocation;
        int currentLandmarkLocation;
        std::string mapBlank = " ";
        std::string mapFilled = "X";
        std::string mapUnfilled = " ";
        std::string mapCity = "0";

    public:
        Map();
        void listAvalibleLocations(std::string username);
        void displayMapOutline(int maxColumnInput = mapStandardMaxColumn, int maxRowInput = mapStandardMaxRow, int minColumnInput = mapStandardMinColumn, int minRowInput = mapStandardMinRow);
        void fillInMap(); //displays world map
        void fillInMap(int landmark); //displays map of city
        void fillInMap(int landmark, int subLandmark); //displays map of town
        void writeLandmark(int locationValue, std::string iconType);
        void writeLandmarks();


        TempEntity getPlayer(){ return player ;}
        void setPlayer(TempEntity playerE){ player = playerE; }

        bool isCityLocation(int locationValue);

        bool canMoveFromCurrentLocation(int directionValue);
        bool canMoveFromCurrentLocationCity(int directionValue);
        void setCurrentLocation(int num) { currentLocation = num; }
        int getCurrentLocation() {if (currentLocation > 0) { return currentLocation;} else { return currentLocation = 282; } }
        void setCurrentLandmarkLocation(int num) { currentLandmarkLocation = num; }
        int getCurrentLandmarkLocation() {if (currentLandmarkLocation > 0) { return currentLandmarkLocation;} else { return currentLandmarkLocation = 1; } }

        /*
        void setPossibleTravelLocations(int num, int x, int y) { possibleTravelLocations[num].x = x; possibleTravelLocations[num].y = y; std::cout << " xs: " << possibleTravelLocations[num].x << " ys: " << possibleTravelLocations[num].y << std::endl; }
        */
        int getPossibleTravelLocationsX(int num, int subNum = 0) { return possibleTravelLocations[num][subNum].x; }
        int getPossibleTravelLocationsY(int num, int subNum = 0) { return possibleTravelLocations[num][subNum].y; }
        int getMapStandardMaxColumn(){ return mapStandardMaxColumn; }
        int getMapStandardMaxRow(){ return mapStandardMaxRow; }
        int getMapStandardMinColumn(){ return mapStandardMinColumn; }
        int getMapStandardMinRow(){ return mapStandardMinRow; }
        
        int getMapCityStandardMaxColumn() { return mapCityStandardMaxColumn; }
        int getMapCityStandardMaxRow() { return mapCityStandardMaxRow; }
        int getMapCityStandardMinColumn() { return mapCityStandardMinColumn; }
        int getMapCityStandardMinRow() { return mapCityStandardMinRow; }




        landmarks getAllCities(){ return allCities; }
        int getCityCount(){ return CityCount; }


        std::string getMapBlank() { return mapBlank; }
        std::string getMapFilled() { return mapFilled; }
        std::string getMapUnfilled() { return mapUnfilled; }
        std::string getMapCity() { return mapCity; }
};