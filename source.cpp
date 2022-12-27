#include <iostream>
#include "Main.h"
#include<Windows.h>

using namespace std;  //so I dont have to type "std::"

int main(){ //Starts the program if the clients version is compatable with the server's versions

    Main main;
    main.setupConsole();
    //main.preLoadGameTest();
    //system("pause");
    main.attemptStartGame();
    return 0;
}