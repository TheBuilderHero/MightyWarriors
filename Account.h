#include <string>

#pragma once

class Account {
    public:
        bool HasGoneThroughInitalSetup; //this will be used to make sure they have added the inital 3 stat points - This needs to be defualted to false in the user account creation on the server.
        std::string username;
        int remainingStatPoints;
        int initHealth = 0, initArmor = 0, initMagicResistance = 0, initPhysicalDamage = 0, initMagicDamage = 0, initAgility = 0, initStealth = 0, initStamina = 0, initMana = 0;
        void setHealth(std::string username);
        void setArmor(std::string username);
        void setMagicResistance(std::string username);
        void setPhysicalDamage(std::string username);
        void setMagicDamage(std::string username);
        void setAgility(std::string username);
        void setStealth(std::string username);
        void setStamina(std::string username);
        void setMana(std::string username);
        void createPlayer(std::string username);

        int getHealth(std::string username);
        int getArmor(std::string username);
        int getMagicResistance(std::string username);
        int getPhysicalDamage(std::string username);
        int getMagicDamage(std::string username);
        int getAgility(std::string username);
        int getStealth(std::string username);
        int getStamina(std::string username);
        int getMana(std::string username);
        void displayStats(std::string username, int bypass = 0, std::string usernameA = ""); //by default bypass is 0 for standard user

        void newOrExistingAccout();
        void createNewAccount();
        void logonScreen(int type = 1); //this allows us to use the logon screen function at the end of this function and pass in the defualt value of 1
        void introStory(std::string username);
        std::string storyTree(int i1);

};