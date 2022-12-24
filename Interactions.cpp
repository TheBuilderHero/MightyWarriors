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

void Interactions::interact(){
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    menu.displayMessageWithPause(25, 10, "Dialogue...");
}

void Interactions::setLocationInteractionDialogue(std::string line){
    interactionLines.push(line);
}

void Interactions::pullInteractionsAndNPCs(){
    ReachOutToServer server;
    Cipher code;
    std::string dialogue = server.sendToServer("~27~");
    string token;
    size_t posLayer1 = 0; // position variable for removing the delimiters to view the message
    size_t posLayer2 = 0; // position variable for removing the delimiters to view the message
    vector<string> layer1;
    vector<string> layer2;
    cout << "STarting Phase 1 interations:" << endl;
    //remove the server send value first before processing the rest of the data:
    posLayer1 = dialogue.find(code.getDelimiterLayer1());
    dialogue.erase(0, posLayer1 + code.getDelimiterLayer1().length());
    posLayer1 = dialogue.find(code.getDelimiterLayer1());
    dialogue.erase(0, posLayer1 + code.getDelimiterLayer1().length());
    //Put all the rest of the data in layer1 vector:
    while ((posLayer1 = dialogue.find(code.getDelimiterLayer1())) != std::string::npos) {
        token = dialogue.substr(0, posLayer1);
        layer1.emplace_back(token);
        dialogue.erase(0, posLayer1 + code.getDelimiterLayer1().length());
    }
    bool lastLoopWasDIALOGUE_INFO = false;
    bool lastLoopWasENEMY_INFO= false;
    bool lastLoopWasSTAT_INFO = false;
    //cout << "STarting Phase 2 interations:" << endl;
    //run through the lower layers and convert them into the needed formats and places
    //cout << "layer 1 size: " << layer1.size() << endl;
    for(int i = 0; i < layer1.size(); i++){
        //cout << "STarting Phase 3 interations:" << endl;
        //cout << "current layer 1: " << layer1.at(i) << endl;
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.DIALOGUE_INFO && !lastLoopWasDIALOGUE_INFO){
            //cout << "STarting Phase if interations:" << endl;

            lastLoopWasDIALOGUE_INFO = true;
            continue;
        } else if (lastLoopWasDIALOGUE_INFO){
            //cout << "STarting Phase else interations:" << endl;

            //then we create all the NPCs with the data from the current deliminations
            bool secondLoopLayer2 = false;
            lastLoopWasDIALOGUE_INFO = false;
            //remove the first delimiter at the start or the later2 information:
            if ((posLayer2 = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2 + code.getDelimiterLayer2().length());
            //then run through all the other data and add it to the vector: 
            while ((posLayer2 = layer1.at(i).find(code.getDelimiterLayer2())) != std::string::npos) {
                token = layer1.at(i).substr(0, posLayer2);
                layer2.emplace_back(token);
                layer1.at(i).erase(0, posLayer2 + code.getDelimiterLayer2().length());
            }
            string npcName = "";
            string npcLocation = "";
            //cout << "STarting Phase 4 interations:" << endl;
            //cout << "size of layer 2: " << layer2.size() << endl;
            //for every chracter recived we run through determining their conversations:
            for(int i2 = 0; i2 < layer2.size(); i2++){
                //set name of character since the first iteration will be the name of the character:
                //then increment the current vector position to access the character's location
                npcName = layer2.at(i2++);
                
                //set location of character since the second iteration will be the assigned location of the character:
                //then increment the current vector position to access the character's multple missions of dialogue
                npcLocation = layer2.at(i2++);
                
                try{//create the NPCs:
                    string lines = layer2.at(i2);
                    npcs.emplace_back(npcName,stoi(npcLocation),lines);
                }
                catch(invalid_argument){
                    //cout << "Critical Failure in \"Interactions::Interactions()\" -> npcs.emplace_back(npcName,stoi(npcLocation),layer2.at(i2));" << endl;
                    system("pause");
                }
            }
        }
        //cout << "End interations:" << endl;


        //maybe we could use this for other things and have it make decisions based on that info:
        /*
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.ENEMY_INFO);
        if (code.convertToDATA_TYPE(layer1.at(i)) == code.STAT_INFO);
        */
    }
    //output all NPC data for testing:
    //cout << "NPCS size: " << npcs.size() << endl;
    npcs.at(0).getAllDialogue();
}

