#include <iostream>
#include <string>

#pragma once

using namespace std;
class TempEntity{
    private:
        std::string username;
        int health, armor, magicResistance, physicalDamageMin, physicalDamageMax, magicDamageMin, magicDamageMax, agility, stealth, stamina, mana;
        std::string name;
    public:
        TempEntity(string currentUsername);
        ~TempEntity();

        //getter functions:
        string getUsername() { return username; }
        //stats:
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

        //setter functions:
        void setUsername(string newUsername);
        //stats:
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

        //updater functions:
        //Stats:
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


        //Richards functions:
        std::string getName();
        void setName(std::string newName);
        //int getHealth();
        //void setHealth(int newHealth);
        void damage(int damage);
        void heal(int healing);
};
