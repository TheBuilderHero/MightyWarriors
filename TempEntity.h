#include <iostream>
#include <string>

#include "Passives.h"

#pragma once
class TempEntity{
    private:
        std::string username;
        //Stats***********************************************************************************
        int maxHealth, health, armor, magicResistance, physicalDamageMin, physicalDamageMax, magicDamageMin, magicDamageMax, agility, stealth, stamina, naturalEnergy, maxMind, mind, psychicDamageMin, psychicDamageMax;
        //battle temporary stats******************************************************************
        int bHealth = 0;
        
        //the following data is used to update the user's saved data on the server (need to create getters and setters)
        //Stats added*********************************************************************************************************************
        int addedHealth, addedarmor, addedMagicResistance, addedPhysicalDamageMin, addedPhysicalDamageMax, addedMagicDamageMin, addedMagicDamageMax, addedAgility, addedStealth, addedStamina, addedNaturalEnergy, addedMaxMind, addedMind, addedPsychicDamageMin, addedPsychicDamageMax;
        //weapon Additions****************************************************************************************************************
        int addedWeaponIron, addedWeaponWood, addedWeaponGems, addedWeaponFeet, addedWeaponFruit, addedWeaponBrains;
        
        //Other player info************************************************************************************************************
        int NUMBER_OF_QUESTS = 7;
        int level, currentXP, XPForNextLevel;
        std::string race, kit, weapon, qDamageType, wDamageType, eDamageType, rDamageType;
        int location, landmarkLocation, quest1Progress[7];
        struct{
            int x;
            int y;
        } mapLocation;
        //int quest1Progress[2];
        std::string name;
        bool battleWon = false;
        int enemyNumber = 0;//This is for tempEntities in group battles

        int INVENTORY_SPACES = 24; //this should be the max inventory (I guess)
        int inventory[24]; //if inventory changes, this number should be updated
        int inventorySize = 12; //Spaces in your starting pack; as you upgrade your pack you can carry more
        int primaryHand, offHand; //these values will be set to the weapon number

        Passives passives;
    public:
        void runConstructorValueSetup(std::string currentUsername, bool NewTempEntityProccess = false);
        TempEntity(std::string currentUsername);
        TempEntity(std::string currentUsername, bool NewTempEntityProccess);
        TempEntity();
        ~TempEntity();

        /* breaks other code:
        TempEntity operator= (TempEntity &tempItem){
            TempEntity output;
            output.health = tempItem.getHealth();
            output.armor = tempItem.getArmor();
            output.magicResistance = tempItem.getMagicResistance();
            output.physicalDamageMin = tempItem.getPhysicalDamageMin();
            output.physicalDamageMax = tempItem.getPhysicalDamageMax();
            output.magicDamageMin = tempItem.getMagicDamageMin();
            output.magicDamageMax = tempItem.getMagicDamageMax();
            output.agility = tempItem.getAgility();
            output.stealth = tempItem.getStealth();
            output.stamina = tempItem.getStamina();
            output.naturalEnergy = tempItem.getNaturalEnergy();
            output.location = tempItem.getLocation();
            output.landmarkLocation = tempItem.getLandmarkLocation();
            for(int i = 0; i < tempItem.NUMBER_OF_QUESTS; i++){
                output.quest1Progress[i] = tempItem.getQuest1Progress(i);
            }
            for(int i = 0; i < tempItem.INVENTORY_SPACES; i++){
                output.inventory[i] = tempItem.getInventory(i);
            }
            output.primaryHand = tempItem.getPrimaryHand();
            output.offHand = tempItem.getOffHand();
            output.level = tempItem.getLevel();
            output.currentXP = tempItem.getCurrentXP();
            output.XPForNextLevel = tempItem.getXPForNextLevel();
            output.name = tempItem.getName();
            output.username = tempItem.getUsername();
            output.race = tempItem.getRace();
            output.kit = tempItem.getKit();
            output.weapon = tempItem.getWeapon();
            return output;
        }
        */


        //getter functions:
        std::string getUsername() { return username; }
        int getLocation() { return location; }
        int getMapLocationX() { return mapLocation.x; }
        int getMapLocationY() { return mapLocation.y; }
        int getLandmarkLocation() { return landmarkLocation; }
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
        int getNaturalEnergy(){ return naturalEnergy; }
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

        int getEnemyNumber(){ return enemyNumber; }

        //setter functions:
        void setUsername(std::string newUsername);
        void setLocation(int currentLocationValue);
        void setMapLocation(int mapX, int mapY);
        void setLandmarkLocation(int currentLandmarkLocationValue);
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
        void setNaturalEnergy(int newNaturalEnergy);
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

        void setEnemyNumber(int number){ enemyNumber = number; }

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
        void updateNaturalEnergy(int addNaturalEnergy);
        void updateMaxMind(int addNaturalEnergy);
        void updateMind(int addNaturalEnergy);
        void updatePsychicDamageMin(int addPsychicDamageMin);
        void updatePsychicDamageMax(int addPsychicDamageMax);

        void updateCurrentXP(int addXP);
        void updateLevel(int addLevel);
        void levelUp();

        void updateInventorySize(int addInventory);
        void addInventoryItem(int itemNum);
        void sortInventory();
        int dropItem();


        //battle functions
        void battleInitialize();
        int calculatePhysicalDamage();
        int calculateMagicalDamage();
        void receiveDamage(int damage);

        void statPassives();//maybe redundant
        void offensePassives();//These will inflict status effects on an enemy
        void defensePassives();//These will mitigate damage from an enemy
        void postBattlePassives();
        void setStunned(bool stun);

        Passives getPassives();

        //Richards old and outdated and completely unusued (totally lame) functions:
        std::string getName();//This one is not useless anymore
        void setName(std::string newName);
        void damage(int damage);
        void heal(int healing);
        void setBattleResult(bool result){ battleWon = result; }
        bool getBattleResult(){ return battleWon; }
};
