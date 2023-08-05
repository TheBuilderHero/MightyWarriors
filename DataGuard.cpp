#include <string>
#include <iostream>
#include <fstream>

#include "GlobalVariables.h"
#include "TempEntity.h"
#include "DataGuard.h"
#include "Cipher.h"
#include "ReachOutToServer.h"

using namespace std;

void fnExit(){
    if(guard.getDataSave()){ //if data daving is on then we will save all data to the server.
        guard.saveAllData();
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
    minPhysicalDamage += addPhysicalDamageMin;
}
void DataGuard::updateSaveValuePhysicalDamageMax(int addPhysicalDamageMax){
    maxPhysicalDamage += addPhysicalDamageMax;
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

//trying to move away from map location and to X Y coords
/*
void DataGuard::setPlayerMapLocation(int num){
    locationNum = num;
}
*/
void DataGuard::setPlayerMapLocationX(int numX){
    locationX = numX;
}
void DataGuard::setPlayerMapLocationY(int numY){
    locationY = numY;
}
string DataGuard::getInventoryString(){
    string inventoryString = to_string(playerData.getPrimaryHand()) + "=" + to_string(playerData.getOffHand()) + "=";
    for(int i = 0; i < playerData.getInventorySize(); i++){
        inventoryString += to_string(playerData.getInventory(i)) + "=";
    }
    return inventoryString;
}

void DataGuard::saveAllData(){
    ReachOutToServer server;
    Cipher code;
    //write the stats to file so that they are stored to be opened again later.
    if(guard.getSaveValueMaxHealth() > 0 || guard.getSaveValueArmor() > 0 || guard.getSaveValueMagicResistance() > 0 || guard.getSaveValuePhysicalDamageMax() > 0 || guard.getSaveValueMagicDamageMax() > 0 || guard.getSaveValueAgility() > 0 || guard.getSaveValueStealth() > 0 || guard.getSaveValueStamina() > 0 || guard.getSaveValueNaturalEnergy() > 0 || guard.getSaveValueMaxMind() > 0 || guard.getSaveValuePsychicDamageMax() > 0) string wasAbleToSave = server.sendToServer(code.cipher("16", guard.getPlayerUsername(), to_string(guard.getSaveValueMaxHealth()), to_string(guard.getSaveValueArmor()), to_string(guard.getSaveValueMagicResistance()), to_string(guard.getSaveValuePhysicalDamageMax()), to_string(guard.getSaveValueMagicDamageMax()), to_string(guard.getSaveValueAgility()), to_string(guard.getSaveValueStealth()), to_string(guard.getSaveValueStamina()), to_string(guard.getSaveValueNaturalEnergy()), to_string(guard.getSaveValueMaxMind()), to_string(guard.getSaveValuePsychicDamageMax()))); //Save data only if one of them has been changed.
    //All other data updates:
    string wasAbleToSave = server.sendToServer(code.cipher("24", guard.getPlayerUsername(), code.subCipher(to_string(guard.getSaveValueMaxHealth()), to_string(guard.getSaveValueArmor()), to_string(guard.getSaveValueMagicResistance()), to_string(guard.getSaveValuePhysicalDamageMax()), to_string(guard.getSaveValueMagicDamageMax()), to_string(guard.getSaveValueAgility()), to_string(guard.getSaveValueStealth()), to_string(guard.getSaveValueStamina()), to_string(guard.getSaveValueNaturalEnergy()), to_string(guard.getSaveValueMaxMind()), to_string(guard.getSaveValuePsychicDamageMax()),/* (end of user stats) Now level and xp->*/ to_string(guard.getSaveValueLevel()), to_string(guard.getSaveValueCurrentXP()), /* Now for the location */ to_string(guard.getPlayerMapLocationX()), to_string(guard.getPlayerMapLocationY())), getInventoryString()));
}

void DataGuard::saveAllDataVector(){
    ReachOutToServer server;
    Cipher codeVector;
    std::string tempUsername = player.getUsername();
    codeVector.vectorDeliminateLayer1Head(codeVector.VECTOR_SEND);

    //Load Player Stats:*******************************************************************************************************

    //save the stats date back to the server
    //only was used on server: //codeVector.userDataDeliminationRead(1, tempUsername); //sets the items3 - 6 to the current stat values
    //only used on server: //characters.pullRaceStats(player.getPlayerRace(tempUsername), tempUsername);//set the stats of the Player for the race in their file
    
    //add the stats data to message:
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.STAT_INFO); //next input item
    //IF YOU ADD MORE ITEMS TO STATS BE SURE TO UPDATE: TRANSMITTED_STAT_COUNT (ON THE SERVER SIDE IN CIPHER class)
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(); //use this if moving down to new lower layer
    //moved to data layer 2
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getMaxHealth()));
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getArmor()));
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getMagicResistance()));
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getPhysicalDamageMin())+codeVector.getDelimiterMinMax()+to_string(player.getPhysicalDamageMax())); //need to make sure it accepts both max and min damage
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getMagicDamageMin())+codeVector.getDelimiterMinMax()+to_string(player.getMagicDamageMax())); //need to make sure it accepts both max and min damage
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getAgility()));
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getStealth()));
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getNaturalEnergy()));
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getMaxMind()));
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getPsychicDamageMin())+codeVector.getDelimiterMinMax()+to_string(player.getPsychicDamageMax())); //need to make sure it accepts both max and min damage
    codeVector.vectorDeliminateLayer2EndInput();
    //move back up to layer 1
    //get player location data************************************************************************************************
    //save location data to server
    //add the location data to message:
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.LOCATION_INFO); //send type
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer();
    string mapX = to_string(player.getMapLocationX());
    string mapY = to_string(player.getMapLocationY());
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(mapX); //X
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(mapY); //Y
    codeVector.vectorDeliminateLayer2EndInput();
    //move back up to layer 1
    //sends the player's race, kit and, weapon**********************************************************************************************
    //send the weapons data back to the server
    //only used on server: //Weapons weapons(tempUsername);

    //add the race, kit and, weapon data to message:
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.RACE_KIT_WEAPON_INFO); //send type
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer();
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(player.getRace());
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(player.getKit());
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(player.getWeapon());
    codeVector.vectorDeliminateLayer2EndInput();
    //move back up to layer 1
    //sends the player's Level and XP info***********************************************************
        //read the level and xp data from file
        // level is needed before XP but after weapons due to some sort of ordering thing 
    //add the Level and XP info data to message:
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.LEVEL_XP_INFO); //send type
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer();
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getLevel()));
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getCurrentXP())); //current xp
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getXPForNextLevel())); //xp till next level
    codeVector.vectorDeliminateLayer2EndInput();
    //move back up to layer 1
    //sends the player's ability type info***********************************************************
    //add the Level and XP info data to message:
    /* //Likely do not need to send the following to the server since it already has this and it should not be getting updated:
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.ABILITY_TYPES_INFO); //send type
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer();
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(kit.getRaceDamageTypeForAbility(tempUsername, 'q'));
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(kit.getRaceDamageTypeForAbility(tempUsername, 'w'));
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(kit.getRaceDamageTypeForAbility(tempUsername, 'e'));
    codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(kit.getRaceDamageTypeForAbility(tempUsername, 'r'));
    codeVector.vectorDeliminateLayer2EndInput();
    */
    //move back up to layer 1
    //current Quest Progress****************************************************************************************************
    //read the quest progress data from file
    //only used on server: //codeVector.userDataDeliminationRead(5, tempUsername);//first number is the quest number, then second one is the progess number
    //need to add a function which determines the current quest that the user is working to complete and has not complete.
    
    //please add here... then set that value to the variables below
    
    //add the Quest Progress info data to message:
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.QUEST_PROGRESS); //send type
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer();
    //loop through all quests and send them to the server:
    for(int i = 0; i < player.getQuestCount(); i++){ //so this will send the data over in the format of quest number then quest progress value
        codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(i)); //quest number
        codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getQuestProgress(i))); //quest progress
    }
    codeVector.vectorDeliminateLayer2EndInput();
    //move back up to layer 1
    //Inventory Information****************************************************************************************************
    //add the Inventory data to message:
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.INVENTORY_INFO); //send type
    codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(); //to lower layer
    //add each inventory item to the message:
    for(int i = 0; i < player.getInventorySize(); i++) codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(player.getInventory(i))); //inventory data
    codeVector.vectorDeliminateLayer2EndInput();
    //moved back up to layer 1
    //end vector:
    codeVector.vectorDeliminateLayer1EndInput();

    //reset returnMessage message = ""
    string returnMessage = "";
    //add all items in MESSAGE vector to return message to client
    for(int i = 0; i < codeVector.getMESSAGESize(); i++){
        returnMessage += codeVector.getMESSAGE(i);
    }
    
    server.sendToServer(returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
}