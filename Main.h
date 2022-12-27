#include "Menu.h"
#include "Map.h"
#include "Interactions.h"
#include "DataGuard.h"
#include <vector>
#include "NPCData/NPC.h"
#pragma once



//This file holds the global variables for the program.
/************Global Variables to be shared**************/
extern Menu menu;
extern Map map;
extern Interactions interactions;
extern DataGuard guard;
extern std::vector<NPC> npcs;
extern unsigned int setUIDForNPC();
extern unsigned int getLastAssignedUIDForNPC();
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
    void fullsc();
    void maxsc();
    void setupConsole();
    void attemptStartGame();
    void preLoadGameTest();
    void setTextSize(int size);
};