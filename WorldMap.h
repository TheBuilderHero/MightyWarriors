#include <iostream>
#include <string>
#include "TempEntity.h"

#pragma once

using namespace std;
class WorldMap{
    private:
        TempEntity player;
        bool encounter;
        string travelMessage1, travelMessage2;
        int mapLocationValue;
    public:
        string getMapDescription(int location);
        bool canTravel(int location, int direction);
        string getTravelMessage(int location, int direction);
        void travel(int direction, bool &failedTravel);
        void travelLandmark(int direction, bool &failedTravel);
        TempEntity getPlayer(){ return player; }
        void setPlayer(TempEntity playerE){ player = playerE; }

        /*
        void locationsRecord(int locationCount, int y, int x);
        int getLocationX(int num);
        int getLocationY(int num);
        */

        void setMapLocationValue(int mapValue) {mapLocationValue = mapValue; }
        int getMapLocationValue() {return mapLocationValue; }
};