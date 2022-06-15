#include <string>
#include "TempEntity.h"

#pragma once

class Map{
    private:
        TempEntity player;
    public:
        void listAvalibleLocations(std::string username);
        void displayMapOutline();
        TempEntity getPlayer(){ return player ;}
        void setPlayer(TempEntity playerE){ player = playerE; }
};