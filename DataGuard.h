#include <string>

#include "TempEntity.h"

#pragma once

//Reason for this is to setup

class DataGuard {
private:
    TempEntity playerData;
    std::string playerUsername;
    bool dataSaveingOn = false;
    int maxHealth, health, armor, magicResistance, maxPhysicalDamage, minPhysicalDamage, maxMagicDamage, minMagicDamage, agility, stealth, stamina, naturalEnergy, maxMind, mind, maxPsychicDamage, minPsychicDamage;
    int level, xp;

public:
    DataGuard();
    void updateGuardData(TempEntity player) { playerData = player; }; //updates the data to be guarded
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
    int getSaveValueCurrentXP(){ return xp; }
    int getSaveValueLevel(){ return level; }
};

//global data guard variable:
extern DataGuard guard;