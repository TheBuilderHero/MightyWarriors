#include <string>

#pragma once

using namespace std;

class Account {
    public:
        bool HasGoneThroughInitalSetup; //this will be used to make sure they have added the inital 3 stat points - This needs to be defualted to false in the user account creation on the server.
        string username;
        int remainingStatPoints;
        int health, attack, armor, magicResistance;
        void setHealth();
        void setAttack();
        void setArmor();
        void setMagicResistance();
        void createCharacter();

};