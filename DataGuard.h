#include <string>

#include "TempEntity.h"

#pragma once

//using namespace std; //causing unsigned type error issues

class DataGuard {
private:
    TempEntity playerData;
    bool dataSaveingOn = false;

public:
    DataGuard();
    void updateGuardData(TempEntity player) { playerData = player; }; //updates the data to be guarded
    void on() { dataSaveingOn = true; }; //turn data auto saving to server on (meaning that at this time there is data to loose)
    void off() { dataSaveingOn = false; }; //turn data auto saving to server off (meaing that there is NOT data to loose at this time)
    ~DataGuard();
};

//global data guard variable:
extern DataGuard guard;