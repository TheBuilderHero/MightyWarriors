#pragma once
#include <string>
#include <vector>

class NPC{
    private:
        int assignedMapX, assignedMapY;
        int assignedLandmarkX, assignedLandmarkY;
        std::string name;
        int npcID;
        std::vector<std::vector<std::string>> dialogue;
    public:
        NPC(std::string inputName, int inputAssignedMapX, int inputAssignedMapY, int inputAssignedLandmarkX, int inputAssignedLandmarkY, std::string& inputDialogueMissionList); //
        int getNpcID(){ return npcID; }
        std::string getDialogue(int number, int part){ return dialogue[number][part];}
        int getDialoguePartCount() { int i = dialogue.size(); return i; }
        int getDialogueCount(int number) { int i = dialogue[number].size(); return i; }
        std::string getAllDialogue();
        std::string getName() { return name; }
        std::string getNPCforMapXY(int mapX, int mapY, int landmarkX, int landmarkY);
        int getNPCIDforName(std::string characterName);
};