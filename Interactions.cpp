#include "Interactions.h"
#include "Main.h"


//**********************************************************************
//             Define all Character/location interactions              *
//**********************************************************************
Interactions::Interactions(std::vector<std::string> &test) : Interactions(){ //build all character interactions by getting them from the server files
    std::cout << "Constructor 1 ran!" << std::endl;
    for (int i = 0; i < test.size(); i++){
        setLocationInteractionDialogue(test[i]);
    }
}
Interactions::Interactions(){ //build all character interactions by getting them from the server files
    std::cout << "Constructor 2 ran!" << std::endl;
}

void Interactions::interact(){
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    menu.displayMessageWithPause(25, 10, "Dialogue...");
}

void Interactions::setLocationInteractionDialogue(std::string line){
    interactionLines.push(line);
}

