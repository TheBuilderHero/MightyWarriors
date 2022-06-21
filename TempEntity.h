#include <iostream>
#include <string>

#pragma once
class TempEntity{
    private:
        std::string username;
        int maxHealth, health, armor, magicResistance, physicalDamageMin, physicalDamageMax, magicDamageMin, magicDamageMax, agility, stealth, stamina, mana, maxMind, mind, psychicDamageMin, psychicDamageMax;
        int level, currentXP, XPForNextLevel;
        std::string race, kit, weapon, qDamageType, wDamageType, eDamageType, rDamageType;
        int location, quest1Progress;
        std::string name;
        bool battleWon = false;
    public:
        TempEntity(std::string currentUsername);
        TempEntity(std::string currentUsername, bool NewTempEntityProccess);
        TempEntity();
        ~TempEntity();

        //getter functions:
        std::string getUsername() { return username; }
        int getLocation() { return location; }
        int getQuest1Progress(){ return quest1Progress; }
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
        

        //setter functions:
        void setUsername(std::string newUsername);
        void setLocation(int currentLocationValue);
        void setQuest1Progress(int newProgress);
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


        //Richards functions:
        std::string getName();
        void setName(std::string newName);
        void damage(int damage);
        void heal(int healing);
        void setBattleResult(bool result){ battleWon = result; }
        bool getBattleResult(){ return battleWon; }
};
