#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Interactions.h"
#include "Main.h"
#include <string>

using namespace std;

//**********************************************************************
//             Define all Character/location interactions              *
//**********************************************************************
Interactions::Interactions(int name/*std::vector<std::string> &test*/) : Interactions(){ //build all character interactions by getting them from the server files
    //std::cout << "Constructor 2 ran!" << std::endl;
    ReachOutToServer server;
    Cipher code;
    std::string dialogue = server.sendToServer("~27~");
    string str_file_content;
    string token, output;
    int loopPass = 0;
    size_t pos = 0; // position variable for removing the delimiters to view the message
    while ((pos = dialogue.find(code.getDelimiterLayer1())) != std::string::npos) {
        token = dialogue.substr(0, pos);
        output = token;
        str_file_content += std::string(token); // we do not need to add spaces between the information for now so I removed: + std::string(" ")
        dialogue.erase(0, pos + code.getDelimiterLayer1().length());
        loopPass++;
    }
}
Interactions::Interactions(){ //build all character interactions by getting them from the server files
    //this runs first before the other constructor
    //std::cout << "Constructor 1 ran!" << std::endl;
}

void Interactions::interact(){
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    menu.displayMessageWithPause(25, 10, "Dialogue...");
}

void Interactions::setLocationInteractionDialogue(std::string line){
    interactionLines.push(line);
}

