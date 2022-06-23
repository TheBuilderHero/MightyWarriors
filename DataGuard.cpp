#include <string>
#include <iostream>
#include <fstream>

#include "TempEntity.h"
#include "DataGuard.h"
#include "Cipher.h"
#include "ReachOutToServer.h"

using namespace std;

//global data guard variable:
DataGuard guard;

void fnExit(){
    //Now that the user is logged into their account and loaded their data we will save their data if they close the aplication:
    // We are going to need to "What you should do instead, as mentioned in the comments, is to use a destructor to do cleanup work. This pattern is known as RAII, and is by far one of the best." - https://stackoverflow.com/questions/43690677/trying-to-pass-a-struct-member-function-to-atexit
    //Now no matter how the program exits, the destructor of __willDoOnExit will execute.
    std::cout << "You are closing the application..." << std::endl;
    std::cout << "1" << std::endl;
    std::cout << "2" << std::endl;
    std::cout << "3" << std::endl;
    std::cout << "4" << std::endl;
    std::cout << "5" << std::endl;
    std::cout << "6" << std::endl;
    std::cout << "7" << std::endl;
    std::cout << "8" << std::endl;
    std::cout << "9" << std::endl;
    std::cout << "10" << std::endl;
    std::cout << "end" << std::endl;
    std::cout << "this funtion is incomplete but will be used to save all userdata before closing the aplication." << std::endl;
    guard.~DataGuard(); 
    system("pause");
}

DataGuard::DataGuard(){ //not sure why but this runs twice when I call the destructor once...
    cout << "DataGuarded..." << endl;
    system("pause");
}

DataGuard::~DataGuard(){
    if(dataSaveingOn){ //if data daving is on then we will save all data to the server.
        //Cipher code;
        //ReachOutToServer server;
        //server.sendToServer(code.cipher("24", playerData.getUsername(), code.subCipher()));
        //need to send all data back to server so that we can save it.
        //However, we will need to save bonus stats to file and weapon/kit stats do not need to be saved. (that is the current issue)
        //How are we going to be able to tell the difference.
        cout << "DataDeleted..." << endl;
        system("pause");
    }
}