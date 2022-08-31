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
    //cout << "DataDeleted..." << endl;
    //system("pause");
}

//Data saving for program close:
//Stats:
void DataGuard::updateSaveValueMaxHealth(int addHealth){
    maxHealth += addHealth;
}
void DataGuard::updateSaveValueHealth(int addHealth){
    health += addHealth;
}
void DataGuard::updateSaveValueArmor(int addArmor){
    armor += addArmor;
}
void DataGuard::updateSaveValueMagicResistance(int addMagicResistance){
    magicResistance += addMagicResistance;
}
void DataGuard::updateSaveValuePhysicalDamageMin(int addPhysicalDamageMin){
    maxPhysicalDamage += addPhysicalDamageMin;
}
void DataGuard::updateSaveValuePhysicalDamageMax(int addPhysicalDamageMax){
    minPhysicalDamage += addPhysicalDamageMax;
}
void DataGuard::updateSaveValueMagicDamageMin(int addMagicDamageMin){
    minMagicDamage += addMagicDamageMin;
}
void DataGuard::updateSaveValueMagicDamageMax(int addMagicDamageMax){
    maxMagicDamage += addMagicDamageMax;
}
void DataGuard::updateSaveValueAgility(int addAgility){
    agility += addAgility;
}
void DataGuard::updateSaveValueStealth(int addStealth){
    stealth += addStealth;
}
void DataGuard::updateSaveValueStamina(int addStamina){
    stamina += addStamina;
}
void DataGuard::updateSaveValueNaturalEnergy(int addNaturalEnergy){
    naturalEnergy += addNaturalEnergy;
}
void DataGuard::updateSaveValueMaxMind(int addMind){
    maxMind += addMind;
}
void DataGuard::updateSaveValueMind(int addMind){
    mind += addMind;
}
void DataGuard::updateSaveValuePsychicDamageMin(int addPsychicDamageMin){
    minPsychicDamage += addPsychicDamageMin;
}
void DataGuard::updateSaveValuePsychicDamageMax(int addPsychicDamageMax){
    maxPsychicDamage += addPsychicDamageMax;
}
//Other:
void DataGuard::updateSaveValueCurrentXP(int addXP){
    xp += addXP;
}
void DataGuard::updateSaveValueLevel(int addLevel){
    level += addLevel;
}

void DataGuard::setPlayerMapLocation(int num){
    locationNum = num;
}

void DataGuard::saveAllData(){
    ReachOutToServer server;
    Cipher code;
    //write the stats to file so that they are stored to be opened again later.
    if(guard.getSaveValueHealth() > 0 || guard.getSaveValueArmor() > 0 || guard.getSaveValueMagicResistance() > 0 || guard.getSaveValuePhysicalDamageMax() > 0 || guard.getSaveValueMagicDamageMax() > 0 || guard.getSaveValueAgility() > 0 || guard.getSaveValueStealth() > 0 || guard.getSaveValueStamina() > 0 || guard.getSaveValueNaturalEnergy() > 0 || guard.getSaveValueMaxMind() > 0 || guard.getSaveValuePsychicDamageMax() > 0) string wasAbleToSave = server.sendToServer(code.cipher("16", guard.getPlayerUsername(), to_string(guard.getSaveValueHealth()), to_string(guard.getSaveValueArmor()), to_string(guard.getSaveValueMagicResistance()), to_string(guard.getSaveValuePhysicalDamageMax()), to_string(guard.getSaveValueMagicDamageMax()), to_string(guard.getSaveValueAgility()), to_string(guard.getSaveValueStealth()), to_string(guard.getSaveValueStamina()), to_string(guard.getSaveValueNaturalEnergy()), to_string(guard.getSaveValueMaxMind()), to_string(guard.getSaveValuePsychicDamageMax()))); //Save data only if one of them has been changed.
    //All other data updates:
    string wasAbleToSave = server.sendToServer(code.cipher("24", guard.getPlayerUsername(), code.subCipher(to_string(guard.getSaveValueHealth()), to_string(guard.getSaveValueArmor()), to_string(guard.getSaveValueMagicResistance()), to_string(guard.getSaveValuePhysicalDamageMax()), to_string(guard.getSaveValueMagicDamageMax()), to_string(guard.getSaveValueAgility()), to_string(guard.getSaveValueStealth()), to_string(guard.getSaveValueStamina()), to_string(guard.getSaveValueNaturalEnergy()), to_string(guard.getSaveValueMaxMind()), to_string(guard.getSaveValuePsychicDamageMax()),/* (end of user stats) Now level and xp->*/ to_string(guard.getSaveValueLevel()), to_string(guard.getSaveValueCurrentXP()), /* Now for the location */ to_string(guard.getPlayerMapLocation()))));
}