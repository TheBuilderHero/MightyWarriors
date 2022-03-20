#include <string>

#pragma once

using namespace std;

class Account {
    public:
        string username;
        int health, attack, armor, magicResistance;
        void setHealth();
        void setAttack();
        void setArmor();
        void setMagicResistance();
        void createCharacter();

};