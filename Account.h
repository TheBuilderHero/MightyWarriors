#include <string>

#pragma once

class Account {
    private:
    bool HasGoneThroughInitalSetup; //this will be used to make sure they have added the inital 3 stat points - This needs to be defualted to false in the user account creation on the server.
    bool restartLevelUp = false; //used in levelUp function
    std::string username;
    int initHealth = 0, initArmor = 0, initMagicResistance = 0, initPhysicalDamage = 0, initMagicDamage = 0, initAgility = 0, initStealth = 0, initStamina = 0, initMana = 0, initMind = 0, initPsychicDamage = 0;
    std::string newaccountMenu1 = "no", newaccountMenu2 = "No", newaccountMenu3 = "nO", newaccountMenu4 = "NO";
    public:
        void setHealth(std::string username, int &remainingStatPoints, int numOfStatPoints);
        void setArmor(std::string username, int &remainingStatPoints, int numOfStatPoints);
        void setMagicResistance(std::string username, int &remainingStatPoints, int numOfStatPoints);
        void setPhysicalDamage(std::string username, int &remainingStatPoints, int numOfStatPoints);
        void setMagicDamage(std::string username, int &remainingStatPoints, int numOfStatPoints);
        void setAgility(std::string username, int &remainingStatPoints, int numOfStatPoints);
        void setStealth(std::string username, int &remainingStatPoints, int numOfStatPoints);
        void setStamina(std::string username, int &remainingStatPoints, int numOfStatPoints);
        void setMana(std::string username, int &remainingStatPoints, int numOfStatPoints);
        void setMind(std::string username, int &remainingStatPoints, int numOfStatPoints);
        void setPsychicDamage(std::string username, int &remainingStatPoints, int numOfStatPoints);

        void createPlayer(std::string username);
        void levelUp(std::string username, int numOfStatPoints);

        int getHealth(std::string username);
        int getArmor(std::string username);
        int getMagicResistance(std::string username);
        int getPhysicalDamage(std::string username);
        std::string getPhysicalDamageString(std::string username);
        int getMagicDamage(std::string username);
        std::string getMagicDamageString(std::string username);
        int getAgility(std::string username);
        int getStealth(std::string username);
        int getStamina(std::string username);
        int getMana(std::string username);
        int getMind(std::string username);
        int getPsychicDamage(std::string username);
        std::string getPsychicDamageString(std::string username);
        std::string getMagicDamgeAbilities(std::string username);
        std::string getPhysicalDamgeAbilities(std::string username);
        std::string getPsychicDamgeAbilities(std::string username);
        std::string getKit(std::string username);
        std::string getRace(std::string username);
        std::string getWeapon(std::string username);
        int getLevel(std::string username);
        double getCurrentXPForNextLevel(std::string username);
        double getTotalXPForNextLevel(std::string username);
        void displayStats(std::string username, int bypass = 0, std::string usernameA = ""); //by default bypass is 0 for standard user
        int getQuest1Progress(std::string username);
        void setQuest1Progress(std::string username, int step);

        void newOrExistingAccout();
        void createNewAccount();
        void logonScreen(int type = 1); //this allows us to use the logon screen function at the end of this function and pass in the defualt value of 1
        void introStory(int raceChoice, std::string username);
        std::string storyTree(int raceChoice, int i1);

};