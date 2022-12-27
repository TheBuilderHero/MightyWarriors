#include <string>
#include <vector>
#include "TempEntity.h"

#pragma once

class Map{
    private:
        TempEntity player;
        int optionsHeight = 6;
        int maxRow, minRow;
        int maxColumn, minColumn;
        static const int mapStandardMaxColumn = 112, mapStandardMaxRow = 42;
        static const int mapStandardMinColumn = 2, mapStandardMinRow = 1;
        static const int mapCityStandardMaxColumn = 64, mapCityStandardMaxRow = 26;
        static const int mapCityStandardMinColumn = 24, mapCityStandardMinRow = 6;
        static const int locationCount = 800;
        static const int locationCountLandmark = 400;
        static const int maxCityObjectCount = 8+1; //+1 so that all cities locations work properly (For some reason the last city was having issues with location and icon)
        //in each all of the below we do not use the first value of index 0
        struct{
            const std::vector<std::string> names {"hi","hi","hi","hi","hi","hi","hi"};
            const std::vector<int> location {0, 127, 217, 285, 310, 506, 637};
        } city;
        //This vector holds all the locations within the given cities with which a player can interact.
        const std::vector<std::vector<int>> inCityLocations =   { 
                                                                { }, //empty vector for holding index 0
                                                                { 0,2,3,4 },
                                                                { 0,2,3,4,5 },
                                                                { 0,2,3,4,5,6 },
                                                                { 0,2,3,4,5,6,7 },
                                                                { 0,2,3,4,5,6,7,8 },
                                                                { 0,2,3,4,5,6,7,8,9 }
                                                                };
        int CityCount = ((int)inCityLocations.size()-1);
        //const std::vector<int> interactiveLandmarkCount {0, (int)inCityLocations[1].size()-1, (int)inCityLocations[2].size()-1, (int)inCityLocations[3].size()-1, (int)inCityLocations[4].size()-1, (int)inCityLocations[5].size()-1, (int)inCityLocations[6].size()-1}; //the number of landmarks per city

        int initalPosRow = minRow = 1 + optionsHeight;
        int initalPosColumn = minColumn = 2;
        struct landmarks{
            //int landmarkLocation[CityCount+1][maxCityObjectCount+1]; //the +1 allows us to use the nice 1 - 6 values instead of 0 - 5
            //std::string iconType[CityCount+1][maxCityObjectCount+1];
            std::vector<std::vector<int>> landmarkLocation; //the +1 allows us to use the nice 1 - 6 values instead of 0 - 5
            std::vector<std::vector<std::string>> iconType;
        };
        landmarks allLandmarks;

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
        void fillInLandmarkMap(); //displays map of city
        void fillInMap(int landmark, int subLandmark); //displays map of town
        void writeLandmark(int locationValue, std::string iconType);
        void writeLandmarkObject(int locationValue);
        void writeLandmarks();
        void writeLandmarksObjects(/*int objectCount*/);



        TempEntity getPlayer(){ return player ;}
        void setPlayer(TempEntity playerE){ player = playerE; }

        bool isCityLocation(int locationValue);
        bool isLandmarkObjectInteractiveLocation(int locationValue);
        int whichCity(int locationValue);

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




        landmarks getAllCities(){ return allLandmarks; }
        int getCityCount(){ return inCityLocations.size()-1; }


        std::string getMapBlank() { return mapBlank; }
        std::string getMapFilled() { return mapFilled; }
        std::string getMapUnfilled() { return mapUnfilled; }
        std::string getMapCity() { return mapCity; }

        int getLocationCountLandmark() { return locationCountLandmark; }
        int getInteractiveLandmarkCount(int landmarkID) { return (int)inCityLocations[landmarkID].size()-1;} //basically landmarkID is just the city value 1 - 6
};