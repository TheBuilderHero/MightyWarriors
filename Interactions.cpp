#include "ReachOutToServer.h"
#include "Cipher.h"
#include "GlobalVariables.h"
#include <string>

using namespace std;

//**********************************************************************
//             Define all Character/location interactions              *
//**********************************************************************
Interactions::Interactions(int name/*std::vector<std::string> &test*/) : Interactions(){ //build all character interactions by getting them from the server files
    //std::cout << "Constructor 2 runnning!" << std::endl;
}
Interactions::Interactions(){ //build all character interactions by getting them from the server files
    //this runs first before the other constructor
    //std::cout << "Constructor 1 running!" << std::endl;
}

void Interactions::interact(){ //
    int mapX = player.getMapLocationX();
    int mapY = player.getMapLocationY();
    int landmarkX = player.getLandmarkLocationX();
    int landmarkY = player.getLandmarkLocationY();
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    string name = npcs.at(0).getNPCforMapXY(mapX, mapY,landmarkX,landmarkY);
    int currentNPCID = npcs.at(0).getNPCIDforName(name);
    menu.display(25, 10, name);
    int startingRow = 11;
    int mission = 0;
    int missionStage = player.getQuestProgress(mission);
    //probably need to swap mission out for mission stage when it is all working correctly
    if(currentNPCID >= 0){
        if(npcs.at(currentNPCID).getDialoguePartCount() > 0){
            //currently this only gets mission = 0 and nothing else:
            //we need to have this reach out to "mission control" to determine the current mission
            for (int i = 0; i < npcs.at(currentNPCID).getDialogueCount(mission); i++) {
                menu.display(25, startingRow++, npcs.at(currentNPCID).getDialogue(mission,i),false,true);
                system("pause");
                menu.clearDisplayRow(startingRow, 25);
            }
            menu.display(25,startingRow++, "End of Dialogue...");
            char exiting;
            string exitMessage = "Exit? (Y/N)";
            string addToExitMessage = "";
            do{
                menu.clearDisplayRow(startingRow, 25);
                if(addToExitMessage.length() < 4){
                    menu.display(25,startingRow, exitMessage + addToExitMessage);
                    addToExitMessage += ".";
                } else {
                    menu.display(25,startingRow, exitMessage + addToExitMessage);
                    addToExitMessage = "";
                }
                exiting = menu.yesOrNo();
            } while(exiting != 'y');
        }
    } else {
        menu.displayMessageWithPause(25, startingRow, "No Dialogue...");
    }
}

void Interactions::setLocationInteractionDialogue(std::string line){
    interactionLines.push(line);
}

void Interactions::pullInteractionsAndNPCs(){
    ReachOutToServer server;
    server.requestFromServer(server.GET_ALL_DIALOGUE_DATA);
}