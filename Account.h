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

        int getHealth(std::string username);
        int getAttack(std::string username);
        int getArmor(std::string username);
        int getMagicResistance(std::string username);
        void displayStats(std::string username, int bypass = 0, std::string usernameA = ""); //by default bypass is 0 for standard user

        void newOrExistingAccout();
        void createNewAccount();
        void logonScreen(int type = 1); //this allows us to use the logon screen function at the end of this function and pass in the defualt value of 1

};