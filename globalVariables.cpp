#include "globalVariables.h"
#include "NPCData/NPC.h"
#include <vector>

std::vector<NPC> npcs;
static int currentID = 0;

unsigned int setUIDForNPC(){
    return currentID++;
}

unsigned int getLastAssignedUIDForNPC(){
    return currentID-1;
}