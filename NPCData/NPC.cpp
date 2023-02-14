#include "NPC.h"
#include "../GlobalVariables.h"
#include "../Cipher.h"
#include <iostream>
#include <vector>

using namespace std;
NPC::NPC(std::string inputName, int inputAssignedMapX, int inputAssignedMapY, int inputAssignedLandmarkX, int inputAssignedLandmarkY, std::string& inputDialogueMissionList){ //
    //cout << "started NPC contructor..." << endl;
    Cipher code;
    string token;
    string line;
    size_t posLayer3 = 0; // position variable for removing the delimiters to view the message
    size_t posLayer4 = 0; // position variable for removing the delimiters to view the message
    int runningdialogueNumber = -1; //start at (-1) so after adding 1 the index of 0 will get the first test case
                
    //declar vector for holding each mission:
    vector<string> tempLayer3;
    //(inputDialogueMissionList).

    //remove the first delimiter at the start or the later3 information:
    if ((posLayer3 = inputDialogueMissionList.find(code.getDelimiterLayer3())) != std::string::npos) inputDialogueMissionList.erase(0, posLayer3 + code.getDelimiterLayer3().length());
    //run through all the data adding it to the vector layer3
    while ((posLayer3 = inputDialogueMissionList.find(code.getDelimiterLayer3())) != std::string::npos) {
        token = inputDialogueMissionList.substr(0, posLayer3);
        tempLayer3.emplace_back(token);
        inputDialogueMissionList.erase(0, posLayer3 + code.getDelimiterLayer3().length());
    }
    //cout << "Starting STage 2" << endl;
    for(int i3 = 0; i3 < tempLayer3.size(); i3++){
        //increase vector size to add new data
        dialogue.resize(dialogue.size()+1);
        //vector for holding each line of dialogue in a given mission:
        vector<string> tempLayer4;

        //remove the first delimiter at the start or the later4 information:
        if ((posLayer4 = tempLayer3.at(i3).find(code.getDelimiterLayer4())) != std::string::npos) tempLayer3.at(i3).erase(0, posLayer4 + code.getDelimiterLayer4().length());
        while ((posLayer4 = tempLayer3.at(i3).find(code.getDelimiterLayer4())) != std::string::npos) {
            token = tempLayer3.at(i3).substr(0, posLayer4);
            dialogue.at(i3).emplace_back(token);//this replaces the following line:
            //tempLayer4.emplace_back(token);
            tempLayer3.at(i3).erase(0, posLayer4 + code.getDelimiterLayer4().length());
        }
        //dialogue.at(i3).emplace_back(tempLayer4);
    }
    //cout << "variable assignment .." << endl;
    this->assignedLandmarkX = inputAssignedLandmarkX;
    this->assignedLandmarkY = inputAssignedLandmarkY;
    this->assignedMapX = inputAssignedMapX;
    this->assignedMapY = inputAssignedMapY;
    this->name = inputName;
    npcID = setUIDForNPC();
}
string NPC::getAllDialogue(){
    cout << "Output of NPCs: ";
    for (int i = 0; i < 7; i ++) cout << to_string(npcs.at(i).getNpcID()) << " ";
    cout << endl;
    //Working to add dialogue into memory
    //This outputs all the npc's dialogue:
    for (int i = 0; i < npcs.size(); i++) {
        for(int i2 = 0; i2 < npcs.at(i).getDialoguePartCount(); i2++){
            for(int i3 = 0; i3 < npcs.at(i).getDialogueCount(i2); i3++){
                cout << npcs.at(i).getDialogue(i2, i3) << endl;
            }
        }
    }
    system("pause");
    return "stuff";
}

string NPC::getNPCforMapXY(int mapX, int mapY, int landmarkX, int landmarkY){
    for (int i = 0; i < npcs.size(); i++){
        //menu.displayMessageWithPause(0,0,"NPC: x:" + to_string(npcs.at(i).assignedMapX)+ "y:" + to_string(npcs.at(i).assignedMapY));
        //menu.displayMessageWithPause(0,1,"Player: x:" + to_string(mapX)+ "y:" + to_string(mapY));
        if (mapX == npcs.at(i).assignedMapX && mapY == npcs.at(i).assignedMapY){
            if(landmarkX == npcs.at(i).assignedLandmarkX && landmarkY == npcs.at(i).assignedLandmarkY) return npcs.at(i).getName();
            //menu.displayMessageWithPause(0,0,"NPC Landmark: x:" + to_string(npcs.at(i).assignedLandmarkX)+ "y:" + to_string(npcs.at(i).assignedLandmarkY));
            //menu.displayMessageWithPause(0,1,"Player Landmark: x:" + to_string(landmarkX)+ "y:" + to_string(landmarkY));
        }
    }

    return "Random Nobody";
}

int NPC::getNPCIDforName(string characterName){
    for(int i = 0; i < npcs.size(); i++){
        if(npcs.at(i).getName() == characterName) return npcs.at(i).getNpcID();
    }
    return -1;
}