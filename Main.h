#include "Menu.h"
#include "Map.h"
#include "DataGuard.h"

#pragma once

//This file holds the global variables for the program.
/************Global Variables**************/
extern Menu menu;
extern Map map;
extern DataGuard guard;
/******************************************/

class Main {
    private:
        //Change the version number in the menu.h header file.
        //********************************************
        const int gameVersion     = menu.gameVersion;
        const int gameMajorBuild  = menu.gameMajorBuild;
        const int gameMinorBuild  = menu.gameMinorBuild;
        const int gamePatch       = menu.gamePatch;
        //********************************************

    public:
    void attemptStartGame();
};