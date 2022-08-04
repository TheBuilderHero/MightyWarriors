#include <iostream>
#include <string>

#pragma once
class TempEntity{
    private:
        std::string username;
        //Stats***********************************************************************************
        int maxHealth, health, armor, magicResistance, physicalDamageMin, physicalDamageMax, magicDamageMin, magicDamageMax, agility, stealth, stamina, mana, maxMind, mind, psychicDamageMin, psychicDamageMax;
        //the following data is used to update the user's saved data on the server (need to create getters and setters)
        //Stats added*********************************************************************************************************************
        int addedHealth, addedarmor, addedMagicResistance, addedPhysicalDamageMin, addedPhysicalDamageMax, addedMagicDamageMin, addedMagicDamageMax, addedAgility, addedStealth, addedStamina, addedMana, addedMaxMind, addedMind, addedPsychicDamageMin, addedPsychicDamageMax;
        //weapon Additions****************************************************************************************************************
        int addedWeaponIron, addedWeaponWood, addedWeaponGems, addedWeaponFeet, addedWeaponFruit, addedWeaponBrains;
        
        //Other player info************************************************************************************************************
        int NUMBER_OF_QUESTS = 7;
        int level, currentXP, XPForNextLevel;
        std::string race, kit, weapon, qDamageType, wDamageType, eDamageType, rDamageType;
        int location, quest1Progress[7];
        //int quest1Progress[2];
        std::string name;
        bool battleWon = false;

        int INVENTORY_SPACES = 24; //this should be the max inventory (I guess)
        int inventory[24]; //if inventory changes, this number should be updated
        int inventorySize = 12; //Spaces in your starting pack; as you upgrade your pack you can carry more
        int primaryHand, offHand; //these values will be set to the weapon number
    public:
        TempEntity(std::string currentUsername);
        TempEntity(std::string currentUsername, bool NewTempEntityProccess);
        TempEntity();
        ~TempEntity();

        //getter functions:
        std::string getUsername() { return username; }
        int getLocation() { return location; }
        int getQuest1Progress(int questNumber){ return quest1Progress[questNumber - 1]; }
        //stats:
        int getMaxHealth(){ return maxHealth; }
        int getHealth(){ return health; }
        int getArmor(){ return armor; }
        int getMagicResistance(){ return magicResistance; }
        int getPhysicalDamageMin(){ return physicalDamageMin; }
        int getPhysicalDamageMax(){ return physicalDamageMax; }
        int getMagicDamageMin(){ return magicDamageMin; }
        int getMagicDamageMax(){ return magicDamageMax; }
        int getAgility(){ return agility; }
        int getStealth(){ return stealth; }
        int getStamina(){ return stamina; }
        int getMana(){ return mana; }
        int getMaxMind(){ return maxMind; }
        int getMind(){ return mind; }
        int getPsychicDamageMin(){ return psychicDamageMin; }
        int getPsychicDamageMax(){ return psychicDamageMax; }

        std::string getRace(){ return race; }
        std::string getKit(){ return kit; }
        std::string getWeapon(){ return weapon; }
        std::string getQDamageType(){ return qDamageType; }
        std::string getWDamageType(){ return wDamageType; }
        std::string getEDamageType(){ return eDamageType; }
        std::string getRDamageType(){ return rDamageType; }
        int getLevel(){ return level; }
        int getCurrentXP(){ return currentXP; }
        int getXPForNextLevel(){ return XPForNextLevel; }

        int getInventory(int number){ return inventory[number]; }
        int getPrimaryHand(){ return primaryHand; }
        int getOffHand(){ return offHand; }
        int getInventorySize(){ return inventorySize; }

        //setter functions:
        void setUsername(std::string newUsername);
        void setLocation(int currentLocationValue);
        void setQuest1Progress(int questNumber, int newProgress);
        //stats:
        void setMaxHealth(int newHealth);
        void setHealth(int newHealth);
        void setArmor(int newArmor);
        void setMagicResistance(int newMagicResistance);
        void setPhysicalDamageMin(int newPhysicalDamageMin);
        void setPhysicalDamageMax(int newPhysicalDamageMax);
        void setMagicDamageMin(int newMagicDamageMin);
        void setMagicDamageMax(int newMagicDamageMax);
        void setAgility(int newAgility);
        void setStealth(int newStealth);
        void setStamina(int newStamina);
        void setMana(int newMana);
        void setMaxMind(int newMaxMind);
        void setMind(int newMind);
        void setPsychicDamageMin(int newPsychicDamageMin);
        void setPsychicDamageMax(int newPsychicDamageMax);

        void setRace(std::string newRace);
        void setKit(std::string newKit);
        void setWeapon(std::string newWeapon);
        void setQDamageType(std::string newDamageType);
        void setWDamageType(std::string newDamageType);
        void setEDamageType(std::string newDamageType);
        void setRDamageType(std::string newDamageType);
        void setLevel(int newLevel);
        void setCurrentXP(int newXP);
        void setXPForNextLevel(int newXPForNextLevel);

        void setInventory(int number, int itemNum);
        void setPrimaryHand(int itemNum);
        void setOffHand(int itemNum);
        void setInventorySize(int newInventorySize);

        //updater functions:
        //Stats:
        void updateMaxHealth(int addHealth);
        void updateHealth(int addHealth);
        void updateArmor(int addArmor);
        void updateMagicResistance(int addMagicResistance);
        void updatePhysicalDamageMin(int addPhysicalDamageMin);
        void updatePhysicalDamageMax(int addPhysicalDamageMax);
        void updateMagicDamageMin(int addMagicDamageMin);
        void updateMagicDamageMax(int addMagicDamageMax);
        void updateAgility(int addAgility);
        void updateStealth(int addStealth);
        void updateStamina(int addStamina);
        void updateMana(int addMana);
        void updateMaxMind(int addMana);
        void updateMind(int addMana);
        void updatePsychicDamageMin(int addPsychicDamageMin);
        void updatePsychicDamageMax(int addPsychicDamageMax);

        void updateCurrentXP(int addXP);
        void updateLevel(int addLevel);

        void updateInventorySize(int addInventory);

        //Richards old and outdated and completely unusued (totally lame) functions:
        std::string getName();
        void setName(std::string newName);
        void damage(int damage);
        void heal(int healing);
        void setBattleResult(bool result){ battleWon = result; }
        bool getBattleResult(){ return battleWon; }
};
