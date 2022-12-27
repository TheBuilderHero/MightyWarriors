#include <string>
#include "TempEntity.h"

#pragma once

class Battle{//This class will have all the functions needed for the algorythms needed to complete a battle from start to finish.
    private:
        //This is causing a issue if the server is offline:
        //TempEntity player{"kota"};
        //need to have this be an argument instead and then change the other functions that take this value and use it to use that instead.
        TempEntity player;
        bool lazyZeroPressCheck = false;
        bool lazyLPressCheck = false;
    
    public:
        //void optionsOutput(std::string username, std::string enemyName, int playerHealth, int enemyHealth); //outputs the players battle options
        void optionsOutput(std::string username, std::string enemyName, int playerHealth, int enemyHealth, int playerMind = 0, int enemyMind = 0);
        void startBattle(std::string username); //function to start a fight
        void questBattle(std::string username, int quest, int step); // function for Quest Battles yo
        void waitForButtonPress(std::string username, std::string &enemyName, bool &zeroKeyPressedLastLoop, bool &lPressKeyPressedLastLoop,bool &qKeyPressedLastLoop, bool &wKeyPressedLastLoop, bool &eKeyPressedLastLoop, bool &rKeyPressedLastLoop, bool &playerBlocking, int playerHealth, int &enemyHealth, int &ultimateUses, int &combatVal, int &playerAttack, int &enemyBlocking, std::string &playerAttackType);
        int getPlayerHealth();

        void tempEntBattle(TempEntity player); //for battle testing purposes
        void standardBattle(TempEntity player);

        TempEntity getPlayer(){ return player ;}
        void setPlayer(TempEntity playerE){ player = playerE; }

        std::string getVictoryMessage();
        std::string getDefeatMessage();
};