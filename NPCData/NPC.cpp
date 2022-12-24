#include "NPC.h"
#include "../globalVariables.h"
#include "../Cipher.h"
#include <iostream>
#include <vector>

using namespace std;

NPC::NPC(string name, int assignedLandmark, string& dialogueMissionList){
    cout << "started NPC contructor..." << endl;
    Cipher code;
    string token;
    string line;
    size_t posLayer3 = 0; // position variable for removing the delimiters to view the message
    size_t posLayer4 = 0; // position variable for removing the delimiters to view the message
    int runningdialogueNumber = -1; //start at (-1) so after adding 1 the index of 0 will get the first test case
                
    //declar vector for holding each mission:
    vector<string> tempLayer3;
    //(dialogueMissionList).

    //remove the first delimiter at the start or the later3 information:
    if ((posLayer3 = dialogueMissionList.find(code.getDelimiterLayer3())) != std::string::npos) dialogueMissionList.erase(0, posLayer3 + code.getDelimiterLayer3().length());
    //run through all the data adding it to the vector layer3
    while ((posLayer3 = dialogueMissionList.find(code.getDelimiterLayer3())) != std::string::npos) {
        token = dialogueMissionList.substr(0, posLayer3);
        tempLayer3.emplace_back(token);
        dialogueMissionList.erase(0, posLayer3 + code.getDelimiterLayer3().length());
    }
    cout << "Starting STage 2" << endl;
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
    cout << "variable assignment .." << endl;
    /*
    while(getline(dialogueMissionList, line)){
        bool singleExceptionRun = false;
        static bool recordingDialogue = false; 
        static bool getDialogueNumber = false; 
        static int dialogueNumber = -1;
        static int lineNum = 0;
        if(getDialogueNumber) {
            runningdialogueNumber++;
            try {
                dialogueNumber = stoi(line);
                if (dialogueNumber != runningdialogueNumber) { //prevent incrimentations to dialogue greater than 1
                    throw dialogueNumber;
                }
            } 
            catch(invalid_argument){ //runs if there is no mission number
                dialogueNumber = runningdialogueNumber;
                singleExceptionRun = true;

                //Let user know that something went wrong with dialogue incrementation:
                cout << "Warning! Initialization NPC while(getline(cin, line)) -> if(getDialogueNumber) -> Stoi(line) -> Missing Dialogue Number" << endl;
            }
            catch(int failed){ //runs since there is a mission number but it is out of order
                dialogueNumber = runningdialogueNumber;
                
                //Let user know that something went wrong with dialogue incrementation:
                cout << "Warning! Initialization NPC while(getline(cin, line)) -> if(getDialogueNumber) -> Stoi(line) -> incrimentation to dialogue greater or less than 1" << endl;
            }
            catch(...){
                //Let user know that something went wrong:
                cout << "Warning! Initialization NPC while(getline(cin, line)) -> if(getDialogueNumber) -> Stoi(line) -> Defalult Case" << endl;
            }
        }
        if (line == "~"+name+"~"){
            recordingDialogue = true;
            getDialogueNumber = true;
            dialogue.resize(dialogue.size()+1);
        }
        if (line == "~/"+name+"~"){
            recordingDialogue = false;
            dialogueNumber = -1;
            lineNum = 0;
        }
        if((!getDialogueNumber && recordingDialogue) || singleExceptionRun){
            //Working to add dialogue into memory
            dialogue[dialogueNumber].resize(dialogue[dialogueNumber].size()+1);
            dialogue[dialogueNumber][lineNum]= line;
            lineNum++;
            //cout << lineNum << " : Recorded : Size: " << dialogue[dialogueNumber].size() << endl;
            singleExceptionRun = false;
        } 
        if (dialogueNumber >= 0 && recordingDialogue) {
            getDialogueNumber = false;
        }
    }
    */
    this->assignedLandmark = assignedLandmark;
    this->name = name;
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