#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

#include "Account.h"
#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Menu.h"
#include "Battle.h"

Menu classMenu;

using namespace std;

void Battle::optionsOutput(string username, string enemyName, int playerHealth, int enemyHealth){
    system("cls");
    cout << endl << setfill(' ') << setw(20 + username.length()) << username  << setfill(' ') << setw(47 + enemyName.length()) << enemyName << endl; //print the current stats of both the enemy and the Player
    cout << endl << setfill(' ') << setw(30) << "Player Health: " << playerHealth << setfill(' ') << setw(50) << "Enemy Health: " << enemyHealth << endl; //print the current stats of both the enemy and the Player
    cout << endl << endl << endl << setfill(' ') << setw(63) << "Please choose an attack option" <<//give the user a list of options to choose from in order to fight the enemy
    endl << setfill(' ') << setw(41) << "Attack 1" << setfill(' ') << setw(25) <<"(type number \"Q\")" << endl;
    cout << setfill(' ') << setw(38) << "Block" << setfill(' ') << setw(28) <<"(type number \"W\")" << endl;
    cout << setfill(' ') << setw(40) << "Utility" << setfill(' ') << setw(26) <<"(type number \"E\")" << endl;
    cout << setfill(' ') << setw(48) << "Ultimate Attack" << setfill(' ') << setw(18) <<"(type number \"R\")" << endl;
}

//loops till the player presses one of Q W E R
void Battle::waitForButtonPress(string &username, string &enemyName, bool &qKeyPressedLastLoop, bool &wKeyPressedLastLoop, bool &eKeyPressedLastLoop, bool &rKeyPressedLastLoop, bool &playerBlocking, int &playerHealth, int &enemyHealth, int &ultimateUses, int &combatVal, int &playerAttack, int &enemyBlocking){
    ReachOutToServer server;
    Cipher code;
    string qOption = "1", wOption = "2", eOption = "3", rOption = "4";
    while (1) //continues to run until broken out.
        {
            if (GetKeyState('R') < 0 && !rKeyPressedLastLoop && ultimateUses > 0) {//checks to make sure that the key is pressed and makes sure it was not pressed last check
                playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, rOption))); //gets damage info from the server to determine the amount inflicted on the enemy;
                code.decipherS(server.sendToServer(code.cipher("11"))); //ask if enemy is blocking next attack and get BLOCK_REDUCTION_VALUE from server
                enemyBlocking = stoi(code.getItemS(1)); //set enemyBlocking from server
                if (!enemyBlocking) enemyHealth -= playerAttack; //if the enemy is not blocking do full damage otherwise reduce it by the BLOCK_REDUCTION_VALUE sent over by the server.
                if (enemyBlocking) enemyHealth -= (playerAttack *= stod(code.getItemS(2))); //reduce attack by BLOCK_REDUCTION_VALUE
                ultimateUses--; //take away one of the ult uses.
                rKeyPressedLastLoop = true;
                break;
            } else if (GetKeyState('R') < 0 && !rKeyPressedLastLoop && ultimateUses <= 0) {
                cout << "You do nothave anymore ultimate uses..." << endl;
                system("pause");
                system("cls");
                optionsOutput(username, enemyName, playerHealth, enemyHealth); //re output the options for battle after clearing the terminal
            } else if (GetKeyState('R') >= 0){// else R not pressed
                rKeyPressedLastLoop = false;
            }
            if (GetKeyState('E') < 0 && eKeyPressedLastLoop == false) {//checks to make sure that the key is pressed and makes sure it was not pressed last check
                playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, eOption))); //gets damage info from the server to determine the amount inflicted on the enemy;
                code.decipherS(server.sendToServer(code.cipher("11"))); //ask if enemy is blocking next attack and get BLOCK_REDUCTION_VALUE from server
                enemyBlocking = stoi(code.getItemS(1)); //set enemyBlocking from server
                if (!enemyBlocking) enemyHealth -= playerAttack; //if the enemy is not blocking do full damage otherwise reduce it by the BLOCK_REDUCTION_VALUE sent over by the server.
                if (enemyBlocking) enemyHealth -= (playerAttack *= stod(code.getItemS(2))); //reduce attack by BLOCK_REDUCTION_VALUE
                eKeyPressedLastLoop = true;
                break;
            } else if (GetKeyState('E') >= 0){// else E not pressed
                eKeyPressedLastLoop = false;
            }
            if (GetKeyState('W') < 0 && wKeyPressedLastLoop == false) {//checks to make sure that the key is pressed and makes sure it was not pressed last check
                //This ability now blocks instead of inflicts damage
                playerBlocking = true;
                //The following commenet out was for the damage aspect of this ability:
                    /*playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, wOption))); //gets damage info from the server to determine the amount inflicted on the enemy;
                    code.decipherS(server.sendToServer(code.cipher("11"))); //ask if enemy is blocking next attack and get BLOCK_REDUCTION_VALUE from server
                    enemyBlocking = stoi(code.getItemS(1)); //set enemyBlocking from server
                    if (!enemyBlocking) enemyHealth -= playerAttack; //if the enemy is not blocking do full damage otherwise reduce it by the BLOCK_REDUCTION_VALUE sent over by the server.
                    if (enemyBlocking) enemyHealth -= (playerAttack *= stod(code.getItemS(2))); //reduce attack by BLOCK_REDUCTION_VALUE
                    enemyHealth -= playerAttack;*/
                wKeyPressedLastLoop = true;
                break;
            } else if (GetKeyState('W') >= 0){// else W not pressed
                playerBlocking = false;
                wKeyPressedLastLoop = false;
            }
            if (GetKeyState('Q') < 0 && !qKeyPressedLastLoop) { //checks to make sure that the key is pressed and makes sure it was not pressed last check - also check ultimate uses
                playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, qOption))); //gets damage info from the server to determine the amount inflicted on the enemy;
                code.decipherS(server.sendToServer(code.cipher("11"))); //ask if enemy is blocking next attack and get BLOCK_REDUCTION_VALUE from server
                enemyBlocking = stoi(code.getItemS(1)); //set enemyBlocking from server
                if (!enemyBlocking) enemyHealth -= playerAttack; //if the enemy is not blocking do full damage otherwise reduce it by the BLOCK_REDUCTION_VALUE sent over by the server.
                if (enemyBlocking) enemyHealth -= (playerAttack *= stod(code.getItemS(2))); //reduce attack by BLOCK_REDUCTION_VALUE
                qKeyPressedLastLoop = true;
                break;
            } else if (GetKeyState('Q') >= 0){ // else Q not pressed
                qKeyPressedLastLoop = false;
            }
        }
}

void Battle::startBattle(string username){
    bool qKeyPressedLastLoop = false, wKeyPressedLastLoop = false, eKeyPressedLastLoop = false, rKeyPressedLastLoop = false;
    bool playerBlocking = false;
    int playerHealth, enemyHealth;
    int ultimateUses = 1;
    string answer;
    bool fightWon, fightLost;
    ReachOutToServer server;
    Cipher code;
    Account account;
    //**************************
    //Initalize all variables
    int playerLevelAtStartOfFight = account.getLevel(username);
    code.decipherS(server.sendToServer(code.cipher("6", username))); //request the current stats of this user from the server //pull info from the server to get the Player's Character info
    playerHealth = stoi(code.getItemS(1)); //set player health
    fightWon = fightLost = false; //set both lost and won to false
    code.decipherS(server.sendToServer(code.cipher("7", username))); //request the current stats of a enemy from the server //pull data from the server regarding the enemy to fight
    enemyHealth = stoi(code.getItemS(2)); //set enemy health
    string enemyName = code.getItemS(1);
    //**************************
    //Start Battle clearing the screen
    while (!fightWon && !fightLost){//loop through displaying the stats and having the player pick options until the fight is won or lost
        int combatVal = 0;
        int playerAttack = 0;
        int enemyBlocking = 0;
        optionsOutput(username, enemyName, playerHealth, enemyHealth); //outputs the options for battle
        
        //loops till the player presses one of Q W E R
        waitForButtonPress(username,enemyName,qKeyPressedLastLoop,wKeyPressedLastLoop,eKeyPressedLastLoop,rKeyPressedLastLoop,playerBlocking,playerHealth,enemyHealth,ultimateUses,combatVal,playerAttack,enemyBlocking);
        
        cout << "Your attack hits the enemy for " << playerAttack << " damage" << endl;
        system("pause");

        //check if enemy is dead:
        if (enemyHealth <= 0){
            fightWon = true;
            break;
        }

        //reprint the stats and info:
        system("cls");
        optionsOutput(username, enemyName, playerHealth, enemyHealth);

        //Enemy's turn to attack:
        int enemyAttack = stoi(server.sendToServer(code.cipher("10", username, enemyName, to_string(playerBlocking))));
        enemyAttack = (enemyBlocking) ? 0 : enemyAttack; //set attack to 0 damage if enemy is blocking
        cout << "The enemies attack hits you for " << enemyAttack << " damage" << endl;
        system("pause");
        playerHealth -= enemyAttack;
        enemyAttack = 0;

        if (playerHealth <= 0) {
            fightLost = true;
            break;
        }
    }
    //print out the result of the fight
    if (fightWon) { //the player has won the fight
        system("cls");
        //increase user xp, since fight was won.
        string playerLevel = server.sendToServer(code.cipher("14", username, enemyName, "WillNeedToFeedBackEnemyLevel")); //this will need to send the enemy level later on.
        cout <<  setfill(' ') << setw(57) << "You won the Battle!" << endl;
        cout <<  setfill(' ') << setw((77 - 16) - playerLevel.length()) << "Your level is: " << playerLevel << endl;
        system("pause");
        system("cls"); 
        int currentPlayerLevel = account.getLevel(username);
        if(playerLevelAtStartOfFight < currentPlayerLevel){ //runs the level update for stats
            account.levelUp(username, currentPlayerLevel);
        }
        system("cls");
    } else if (fightLost){ //the enemy has won the fight
        system("cls");
        cout <<  setfill(' ') << setw(58) << "You Lost the Battle!" << endl;
        system("pause");
        system("cls");
    }


    
    cout << "Would you like to Battle again? (Y/N)\n>";
    answer = classMenu.yesOrNo();
    while (!(answer == "n" || answer == "N" || answer == "y" || answer == "Y")) { //ask player if they want to battle more or go back to main menu.
        cout << endl << answer << endl;
        //answer = 'A';// set the answer variable to some other value on the start of each loop.
        cout << "Your input was not recognized." << endl << "Would you like to Battle again? (Y/N)";
        answer = classMenu.yesOrNo();
    }
    if (answer == "y" || answer == "Y"){
        startBattle(username);//run battle again
    } else {
        classMenu.menu(username);//go to main menu
    }
}

void Battle::questBattle(string username, int quest, int step, TempEntity player){
    bool qKeyPressedLastLoop = false, wKeyPressedLastLoop = false, eKeyPressedLastLoop = false, rKeyPressedLastLoop = false;
    bool playerBlocking = false;
    int playerHealth, enemyHealth;
    int playerLevelAtStartOfFight = 0;
    int ultimateUses = 1;
    string enemyName = "";
    string answer;
    bool fightWon = false, fightLost = false;
    ReachOutToServer server;
    Cipher code;
    Account account;
    //**************************
    //Initalize all variables
    try {
        playerLevelAtStartOfFight = account.getLevel(username);
        code.decipherS(server.sendToServer(code.cipher("6", username))); //request the current stats of this user from the server //pull info from the server to get the Player's Character info
        player.setHealth(stoi(code.getItemS(1))); //set player health
        playerHealth = player.getHealth();
        fightWon = fightLost = false; //set both lost and won to false
        code.decipherS(server.sendToServer(code.cipher("7", username, to_string(quest), to_string(step)))); //request the current stats of a enemy from the server //pull data from the server regarding the enemy to fight
        enemyHealth = stoi(code.getItemS(2)); //set enemy health
        if(quest == 1 && step == 0){
            if(enemyHealth > 10)
                enemyHealth = 10;
        }
        enemyName = code.getItemS(1);
    } catch(std::invalid_argument) {
        cout << "Battle initialization failed";
        system("pause");
        return;
    }
    //**************************
    //Start Battle clearing the screen
    while (!fightWon && !fightLost){//loop through displaying the stats and having the player pick options until the fight is won or lost
        int combatVal = 0;
        int playerAttack = 0;
        int enemyBlocking = 0;
        optionsOutput(username, enemyName, playerHealth, enemyHealth); //outputs the options for battle
        
        //loops till the player presses one of Q W E R
        waitForButtonPress(username,enemyName,qKeyPressedLastLoop,wKeyPressedLastLoop,eKeyPressedLastLoop,rKeyPressedLastLoop,playerBlocking,playerHealth,enemyHealth,ultimateUses,combatVal,playerAttack,enemyBlocking);
        
        cout << "Your attack hits the enemy for " << playerAttack << " damage" << endl;
        system("pause");

        //check if enemy is dead:
        if (enemyHealth <= 0){
            fightWon = true;
            break;
        }

        //reprint the stats and info:
        system("cls");
        optionsOutput(username, enemyName, playerHealth, enemyHealth);

        //Enemy's turn to attack:
        int enemyAttack = stoi(server.sendToServer(code.cipher("10", username, enemyName, to_string(playerBlocking))));
        enemyAttack = (enemyBlocking) ? 0 : enemyAttack; //set attack to 0 damage if enemy is blocking
        cout << "The enemies attack hits you for " << enemyAttack << " damage" << endl;
        system("pause");
        playerHealth -= enemyAttack;
        enemyAttack = 0;

        player.setHealth(playerHealth);

        if (playerHealth <= 0) {
            fightLost = true;
            break;
        }
    }
    //print out the result of the fight
    if (fightWon) { //the player has won the fight
        system("cls");
        //increase user xp, since fight was won.
        string playerLevel = server.sendToServer(code.cipher("14", username, enemyName, "WillNeedToFeedBackEnemyLevel")); //this will need to send the enemy level later on.
        cout <<  setfill(' ') << setw(57) << "You won the Battle!" << endl;
        cout <<  setfill(' ') << setw((77 - 16) - playerLevel.length()) << "Your level is: " << playerLevel << endl;
        system("pause");
        system("cls"); 
        int currentPlayerLevel = account.getLevel(username);
        if(playerLevelAtStartOfFight < currentPlayerLevel){ //runs the level update for stats
            account.levelUp(username, currentPlayerLevel);
        }
        system("cls");
    } else if (fightLost){ //the enemy has won the fight
        system("cls");
        cout <<  setfill(' ') << setw(58) << "You Lost the Battle!" << endl;
        system("pause");
        system("cls");
    }
}