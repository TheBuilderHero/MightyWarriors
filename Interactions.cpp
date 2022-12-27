#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Interactions.h"
#include "Main.h"
#include "globalVariables.h"
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
    menu.displayMessageWithPause(25, 10, npcs.at(0).getNPCforLocation(location));
    //menu.displayMessageWithPause(25, 10, "Dialogue...");
}

void Interactions::setLocationInteractionDialogue(std::string line){
    interactionLines.push(line);
}

void Interactions::pullInteractionsAndNPCs(){
    ReachOutToServer server;
    server.requestFromServer("27");
}