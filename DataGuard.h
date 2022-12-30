#include <string>

#include "TempEntity.h"
#include "Menu.h"
#include "Main.h"

#pragma once
extern TempEntity player;

//Reason for this is to setup

class DataGuard {
private:
    TempEntity playerData;
    std::string playerUsername;
    bool dataSaveingOn = false;
    int maxHealth = 0, health = 0, armor = 0, magicResistance = 0, maxPhysicalDamage = 0, minPhysicalDamage = 0, maxMagicDamage = 0, minMagicDamage = 0, agility = 0, stealth = 0, stamina = 0, naturalEnergy = 0, maxMind = 0, mind = 0, maxPsychicDamage = 0, minPsychicDamage = 0;
    int level, xp, locationNum;

public:
    DataGuard();
    void updateGuardData() { playerData = player; }; //updates the data to be guarded
    void on(std::string username) { 
        dataSaveingOn = true;
        playerUsername = username;
    }; //turn data auto saving to server on (meaning that at this time there is data to loose)
    void off() { dataSaveingOn = false; }; //turn data auto saving to server off (meaing that there is NOT data to loose at this time)
    bool getDataSave() { return dataSaveingOn; };
    std::string getPlayerUsername(){ return playerUsername; }
    ~DataGuard();

    //Data saving for program close:
    //Stats:
    void updateSaveValueMaxHealth(int addHealth);
    void updateSaveValueHealth(int addHealth);
    void updateSaveValueArmor(int addArmor);
    void updateSaveValueMagicResistance(int addMagicResistance);
    void updateSaveValuePhysicalDamageMin(int addPhysicalDamageMin);
    void updateSaveValuePhysicalDamageMax(int addPhysicalDamageMax);
    void updateSaveValueMagicDamageMin(int addMagicDamageMin);
    void updateSaveValueMagicDamageMax(int addMagicDamageMax);
    void updateSaveValueAgility(int addAgility);
    void updateSaveValueStealth(int addStealth);
    void updateSaveValueStamina(int addStamina);
    void updateSaveValueNaturalEnergy(int addNaturalEnergy);
    void updateSaveValueMaxMind(int addNaturalEnergy);
    void updateSaveValueMind(int addNaturalEnergy);
    void updateSaveValuePsychicDamageMin(int addPsychicDamageMin);
    void updateSaveValuePsychicDamageMax(int addPsychicDamageMax);
    //Other:
    void updateSaveValueCurrentXP(int addXP);
    void updateSaveValueLevel(int addLevel);

    //Setters:
    //Map Data:
    void setPlayerMapLocation(int num);
    
    //Data saving getter functions:
    //Stats:
    int getSaveValueMaxHealth(){ return maxHealth; }
    int getSaveValueHealth(){ return health; }
    int getSaveValueArmor(){ return armor; }
    int getSaveValueMagicResistance(){ return magicResistance; }
    int getSaveValuePhysicalDamageMin(){ return minPsychicDamage; }
    int getSaveValuePhysicalDamageMax(){ return maxPhysicalDamage; }
    int getSaveValueMagicDamageMin(){ return minMagicDamage; }
    int getSaveValueMagicDamageMax(){ return maxMagicDamage; }
    int getSaveValueAgility(){ return agility; }
    int getSaveValueStealth(){ return stealth; }
    int getSaveValueStamina(){ return stamina; }
    int getSaveValueNaturalEnergy(){ return naturalEnergy; }
    int getSaveValueMaxMind(){ return maxMind; }
    int getSaveValueMind(){ return mind; }
    int getSaveValuePsychicDamageMin(){ return minPsychicDamage; }
    int getSaveValuePsychicDamageMax(){ return maxPsychicDamage; }
    
    //Other:
    int getSaveValueCurrentXP(){ return playerData.getCurrentXP(); }
    int getSaveValueLevel(){ return playerData.getLevel(); }
    int getPlayerMapLocation() { return locationNum; }
    std::string getInventoryString(); //this is for data saving purposes, not for client use

    void saveAllData();
};