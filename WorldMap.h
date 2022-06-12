#include <iostream>
#include <string>
#include "TempEntity.h"

#pragma once

using namespace std;
class WorldMap{
    private:
        TempEntity player;
    public:
        string getMapDescription(int location);
        bool canTravel(int location, int direction);
        string getTravelMessage(int location, int direction);
        int travel(int location, int direction);
        TempEntity getPlayer(){ return player ;}
        void setPlayer(TempEntity playerE){ player = playerE; }
};