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

void Interactions::interact(int location){ //
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    string name = npcs.at(0).getNPCforLocation(location);
    int cuttentNPCID = npcs.at(0).getNPCIDforName(name);
    menu.displayMessageWithPause(25, 10, name);
    int startingRow = 11;
    int mission = 0;
    if(npcs.at(cuttentNPCID).getDialoguePartCount() > 0){
        for (int i = 0; i < npcs.at(cuttentNPCID).getDialogueCount(mission); i++) {
            menu.display(25, startingRow++, npcs.at(cuttentNPCID).getDialogue(mission,i),false,true);
            system("pause");
            menu.clearDisplayRow(startingRow, 25);
        }
        menu.display(25,startingRow++, "End of Dialogue...");
        char exiting;
        bool backForth = true;
        do{
            if(backForth){
                menu.display(25,startingRow+1, "            ");
                menu.display(25,startingRow++, "Exit? (Y/N)");
                backForth = false;
            } else {
                menu.display(25,startingRow-1, "            ");
                menu.display(25,startingRow--, "Exit? (Y/N)");
                backForth = true;
            }
            exiting = menu.yesOrNo();
        } while(exiting != 'y');
        

    }
    //menu.displayMessageWithPause(25, 10, "Dialogue...");
}

void Interactions::setLocationInteractionDialogue(std::string line){
    interactionLines.push(line);
}

void Interactions::pullInteractionsAndNPCs(){
    ReachOutToServer server;
    server.requestFromServer("27");
}