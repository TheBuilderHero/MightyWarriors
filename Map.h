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
        
    public:
        void listAvalibleLocations(std::string username);
        void displayMapOutline();
        TempEntity getPlayer(){ return player ;}
        void setPlayer(TempEntity playerE){ player = playerE; }
        void displayLocations(); //displays world map
        void displayLocations(int city); //displays map of city
        void displayLocations(int city, int town); //displays map of town
};