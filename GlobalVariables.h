#pragma once
#include "Menu.h"
//#include "Map.h"
#include "Interactions.h"
#include "DataGuard.h"
#include <vector>
#include "TempEntity.h"
#include "NPCData/NPC.h"
#include "GlobalMap.h"

//This file holds the global variables for the program.
/************Global Variables to be shared**************/
extern Menu menu;
//extern Map map;
extern Interactions interactions;
extern DataGuard guard;
extern TempEntity player;
extern GlobalMap globalmap;
extern std::vector<NPC> npcs;
extern unsigned int setUIDForNPC();
extern unsigned int getLastAssignedUIDForNPC();
extern bool exitingGame;
/******************************************/