#include <string>
#include "TempEntity.h"

#pragma once

class Map{
    private:
        TempEntity player;
        int maxColumn, minColumn;
        int maxRow, minRow;
    public:
        void listAvalibleLocations(std::string username);
        void displayMapOutline();
        TempEntity getPlayer(){ return player ;}
        void setPlayer(TempEntity playerE){ player = playerE; }
        void displayLocations(); //displays world map
        void displayLocations(int city); //displays map of city
        void displayLocations(int city, int town); //displays map of town
};