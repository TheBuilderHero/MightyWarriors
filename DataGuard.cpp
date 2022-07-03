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
    if(guard.getDataSave()){ //if data daving is on then we will save all data to the server.
        std::cout << "You are closing the application..." << std::endl;
        std::cout << "1" << std::endl;
        std::cout << "2" << std::endl;
        std::cout << "3" << std::endl;
        std::cout << "end" << std::endl;
        std::cout << "this funtion is incomplete but will be used to save all userdata before closing the aplication." << std::endl;
        system("pause");
    }
    //Now that the user is logged into their account and loaded their data we will save their data if they close the aplication:
    // We are going to need to "What you should do instead, as mentioned in the comments, is to use a destructor to do cleanup work. This pattern is known as RAII, and is by far one of the best." - https://stackoverflow.com/questions/43690677/trying-to-pass-a-struct-member-function-to-atexit
    //Now no matter how the program exits, the destructor of __willDoOnExit will execute.
    
    //guard.~DataGuard(); 
}

DataGuard::DataGuard(){ //not sure why but this runs twice when I call the destructor once...
    //cout << "DataGuarded..." << endl;
    //system("pause");
}

DataGuard::~DataGuard(){
    cout << "DataDeleted..." << endl;
    system("pause");
}