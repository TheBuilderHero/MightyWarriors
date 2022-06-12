#include <string>
#include "TempEntity.h"

#pragma once

class Map{
    private:
        TempEntity player;
    public:
        void listAvalibleLocations(std::string username);
        TempEntity getPlayer(){ return player ;}
        void setPlayer(TempEntity playerE){ player = playerE; }
};