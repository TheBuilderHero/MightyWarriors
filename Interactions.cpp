#include "Interactions.h"
#include "Main.h"

void Interactions::interact(){
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    menu.displayMessageWithPause(25, 10, "Dialogue...");
}