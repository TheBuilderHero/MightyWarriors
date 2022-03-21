#include <string>

#pragma once

class Account {
    public:
        bool HasGoneThroughInitalSetup; //this will be used to make sure they have added the inital 3 stat points - This needs to be defualted to false in the user account creation on the server.
        std::string username;
        int remainingStatPoints;
        int health = 0, attack = 0, armor = 0, magicResistance = 0;
        void setHealth(std::string username);
        void setAttack(std::string username);
        void setArmor(std::string username);
        void setMagicResistance(std::string username);
        void createCharacter(std::string username);

};