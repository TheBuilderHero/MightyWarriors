#include <string>

#pragma once

class Battle{//This class will have all the functions needed for the algorythms needed to complete a battle from start to finish.
    public:
    void optionsOutput(std::string username, std::string enemyName, int playerHealth, int enemyHealth); //outputs the players battle options
    void startBattle(std::string username); //function to start a fight
};