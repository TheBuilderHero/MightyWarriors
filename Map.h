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
        std::vector<std::vector<int>> inCityLocations;
        int CityCount;

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
        int cityStartLocation = 200;
        int worldStartLocation = 282;

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



        TempEntity getPlayer(){ return player;}
        void setPlayer(TempEntity playerE){ 
            player = playerE; 
            std::cout << "updated pos MP" << std::endl;
            system("pause");
        }

        bool isCityLocation(int locationValue);
        bool isLandmarkObjectInteractiveLocation(int locationValue);
        int whichCity(int locationValue);

        bool canMoveFromCurrentLocation(int directionValue);
        bool canMoveFromCurrentLocationCity(int directionValue);
        void setCurrentLocation(int num) { currentLocation = num; }
        int getCurrentLocation() {if (currentLocation > 0) { return currentLocation;} else { return currentLocation = getWorldStartLocation(); } }
        void setCurrentLandmarkLocation(int num) { currentLandmarkLocation = num; }
        int getCurrentLandmarkLocation() {if (currentLandmarkLocation > 0) { return currentLandmarkLocation;} else { return currentLandmarkLocation = getCityStartLocation(); } }

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
        int getCityStartLocation() { return cityStartLocation; }
        int getWorldStartLocation() { return worldStartLocation; }

        bool isCityUID(unsigned short id);
};