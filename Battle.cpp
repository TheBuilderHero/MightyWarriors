#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

#include "Main.h"
#include "Account.h"
#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Menu.h"
#include "Battle.h"
#include "Passives.h"
#include "TempEntity.h"

//extern Menu menu;

using namespace std;

/*
void Battle::optionsOutput(string username, string enemyName, int playerHealth, int enemyHealth){
    system("cls");
    cout << endl << setfill(' ') << setw(20 + username.length()) << username  << setfill(' ') << setw(47 + enemyName.length()) << enemyName << endl; //print the current stats of both the enemy and the Player
    cout << endl << setfill(' ') << setw(30) << "Player Health: " << playerHealth << setfill(' ') << setw(50) << "Enemy Health: " << enemyHealth << endl; //print the current stats of both the enemy and the Player
    cout << endl << endl << endl << setfill(' ') << setw(63) << "Please choose an attack option" <<//give the user a list of options to choose from in order to fight the enemy
    endl << setfill(' ') << setw(41) << "Attack 1" << setfill(' ') << setw(25) <<"(type number \"Q\")" << endl;
    cout << setfill(' ') << setw(38) << "Block" << setfill(' ') << setw(28) <<"(type number \"W\")" << endl;
    cout << setfill(' ') << setw(40) << "Utility" << setfill(' ') << setw(26) <<"(type number \"E\")" << endl;
    cout << setfill(' ') << setw(48) << "Ultimate Attack" << setfill(' ') << setw(18) <<"(type number \"R\")" << endl;
}*/
void Battle::optionsOutput(string username, string enemyName, int playerHealth, int enemyHealth, int playerMind, int enemyMind){
    system("cls");
    cout << endl << setfill(' ') << setw(20 + username.length()) << username  << setfill(' ') << setw(47 + enemyName.length()) << enemyName << endl; //print the current stats of both the enemy and the Player
    cout << endl << setfill(' ') << setw(30) << "Player Health: " << playerHealth << setfill(' ') << setw(50) << "Enemy Health: " << enemyHealth << endl; //print the current stats of both the enemy and the Player
    cout << endl << setfill(' ') << setw(30) << "Player Mind: " << playerMind << setfill(' ') << setw(50) << "Enemy Mind: " << enemyMind << endl;
    cout << endl << endl << endl << setfill(' ') << setw(63) << "Please choose an attack option" <<//give the user a list of options to choose from in order to fight the enemy
    endl << setfill(' ') << setw(41) << "Attack 1" << setfill(' ') << setw(25) <<"(type number \"Q\")" << endl;
    cout << setfill(' ') << setw(38) << "Block" << setfill(' ') << setw(28) <<"(type number \"W\")" << endl;
    cout << setfill(' ') << setw(40) << "Utility" << setfill(' ') << setw(26) <<"(type number \"E\")" << endl;
    cout << setfill(' ') << setw(48) << "Ultimate Attack" << setfill(' ') << setw(18) <<"(type number \"R\")" << endl;
}

//loops till the player presses one of Q W E R
void Battle::waitForButtonPress(string username, string &enemyName, bool &qKeyPressedLastLoop, bool &wKeyPressedLastLoop, bool &eKeyPressedLastLoop, bool &rKeyPressedLastLoop, bool &playerBlocking, int playerHealth, int &enemyHealth, int &ultimateUses, int &combatVal, int &playerAttack, int &enemyBlocking, string &playerAttackType){
    ReachOutToServer server;
    Cipher code;
    string qOption = "1", wOption = "2", eOption = "3", rOption = "4";
    while (1) //continues to run until broken out.
        {
            if (GetKeyState('R') < 0 && !rKeyPressedLastLoop && ultimateUses > 0) {//checks to make sure that the key is pressed and makes sure it was not pressed last check
                playerAttackType = player.getRDamageType();
                playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, rOption))); //gets damage info from the server to determine the amount inflicted on the enemy;
                code.decipherS(server.sendToServer(code.cipher("11"))); //ask if enemy is blocking next attack and get BLOCK_REDUCTION_VALUE from server
                enemyBlocking = stoi(code.getItemS(1)); //set enemyBlocking from server
                if(playerAttackType != "Psychic"){
                    if (!enemyBlocking) enemyHealth -= playerAttack; //if the enemy is not blocking do full damage otherwise reduce it by the BLOCK_REDUCTION_VALUE sent over by the server.
                    if (enemyBlocking) enemyHealth -= (playerAttack *= stod(code.getItemS(2))); //reduce attack by BLOCK_REDUCTION_VALUE
                }
                ultimateUses--; //take away one of the ult uses.
                rKeyPressedLastLoop = true;
                break;
            } else if (GetKeyState('R') < 0 && !rKeyPressedLastLoop && ultimateUses <= 0) {
                cout << "You do not have any more ultimate uses..." << endl;
                system("pause");
                system("cls");
                optionsOutput(username, enemyName, playerHealth, enemyHealth); //re output the options for battle after clearing the terminal
            } else if (GetKeyState('R') >= 0){// else R not pressed
                rKeyPressedLastLoop = false;
            }
            if (GetKeyState('E') < 0 && eKeyPressedLastLoop == false) {//checks to make sure that the key is pressed and makes sure it was not pressed last check
                playerAttackType = player.getEDamageType();
                playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, eOption))); //gets damage info from the server to determine the amount inflicted on the enemy;
                code.decipherS(server.sendToServer(code.cipher("11"))); //ask if enemy is blocking next attack and get BLOCK_REDUCTION_VALUE from server
                enemyBlocking = stoi(code.getItemS(1)); //set enemyBlocking from server
                if(playerAttackType != "Psychic"){
                    if (!enemyBlocking) enemyHealth -= playerAttack; //if the enemy is not blocking do full damage otherwise reduce it by the BLOCK_REDUCTION_VALUE sent over by the server.
                    if (enemyBlocking) enemyHealth -= (playerAttack *= stod(code.getItemS(2))); //reduce attack by BLOCK_REDUCTION_VALUE
                }
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
                playerAttackType = "Block";
                break;
            } else if (GetKeyState('W') >= 0){// else W not pressed
                playerBlocking = false;
                wKeyPressedLastLoop = false;
            }
            if (GetKeyState('Q') < 0 && !qKeyPressedLastLoop) { //checks to make sure that the key is pressed and makes sure it was not pressed last check - also check ultimate uses
                playerAttackType = player.getQDamageType();
                playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, qOption))); //gets damage info from the server to determine the amount inflicted on the enemy;
                code.decipherS(server.sendToServer(code.cipher("11"))); //ask if enemy is blocking next attack and get BLOCK_REDUCTION_VALUE from server
                enemyBlocking = stoi(code.getItemS(1)); //set enemyBlocking from server
                if(playerAttackType != "Psychic"){
                    if (!enemyBlocking) enemyHealth -= playerAttack; //if the enemy is not blocking do full damage otherwise reduce it by the BLOCK_REDUCTION_VALUE sent over by the server.
                    if (enemyBlocking) enemyHealth -= (playerAttack *= stod(code.getItemS(2))); //reduce attack by BLOCK_REDUCTION_VALUE
                }
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
        string playerAttackType = " ";
        int enemyBlocking = 0;
        optionsOutput(username, enemyName, playerHealth, enemyHealth); //outputs the options for battle
        
        //loops till the player presses one of Q W E R
        waitForButtonPress(username,enemyName,qKeyPressedLastLoop,wKeyPressedLastLoop,eKeyPressedLastLoop,rKeyPressedLastLoop,playerBlocking,playerHealth,enemyHealth,ultimateUses,combatVal,playerAttack,enemyBlocking, playerAttackType);
        
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
    answer = menu.yesOrNo();
    while (!(answer == "n" || answer == "N" || answer == "y" || answer == "Y")) { //ask player if they want to battle more or go back to main menu.
        cout << endl << answer << endl;
        //answer = 'A';// set the answer variable to some other value on the start of each loop.
        cout << "Your input was not recognized." << endl << "Would you like to Battle again? (Y/N)";
        answer = menu.yesOrNo();
    }
    if (answer == "y" || answer == "Y"){
        startBattle(username);//run battle again
    } else {
        menu.menu(username);//go to main menu
    }
}

void Battle::questBattle(string username, int quest, int step){
    system("cls");
    bool qKeyPressedLastLoop = false, wKeyPressedLastLoop = false, eKeyPressedLastLoop = false, rKeyPressedLastLoop = false;
    bool playerBlocking = false;
    int playerHealth, enemyHealth, playerMind, enemyMind;
    int playerLevelAtStartOfFight = 0;
    int ultimateUses = 1;
    string enemyName = "";
    int enemyNum = 0;
    string answer;
    bool fightWon = false, fightLost = false;
    int location = player.getLocation();
    ReachOutToServer server;
    Cipher code;
    Account account;
    //**************************
    //Initalize all variables
    try {
        playerLevelAtStartOfFight = account.getLevel(username);
        code.decipherS(server.sendToServer(code.cipher("6", username))); //request the current stats of this user from the server //pull info from the server to get the Player's Character info
        playerHealth = stoi(code.getItemS(1)); //set player health
        playerMind = stoi(code.getItemS(10));
        //player.setHealth(playerHealth);
        fightWon = fightLost = false; //set both lost and won to false
        code.decipherS(server.sendToServer(code.cipher("7", username, to_string(quest), to_string(step)))); //request the current stats of a enemy from the server //pull data from the server regarding the enemy to fight
        enemyHealth = stoi(code.getItemS(2)); //set enemy health
        if(quest == 1 && step == 0){
            if(enemyHealth > 10)
                enemyHealth = 10;
        }
        enemyMind = stoi(code.getItemS(8));
        enemyName = code.getItemS(1);
        enemyNum = stoi(code.getItemS(7));
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
        string playerAttackType;//set in the genius optionsOutput function
        int enemyBlocking = 0;
        optionsOutput(username, enemyName, playerHealth, enemyHealth, playerMind, enemyMind); //outputs the options for battle
        
        //loops till the player presses one of Q W E R
        waitForButtonPress(username,enemyName,qKeyPressedLastLoop,wKeyPressedLastLoop,eKeyPressedLastLoop,rKeyPressedLastLoop,playerBlocking,playerHealth,enemyHealth,ultimateUses,combatVal,playerAttack,enemyBlocking,playerAttackType);
        if(playerAttackType == "Psychic"){
            enemyMind -= playerAttack;
            cout << "Your mental attack hits the enemy's mind for " << playerAttack << " damage" << endl;
            system("pause");
        }else{
            cout << "Your attack hits the enemy for " << playerAttack << " damage" << endl;
            system("pause");
        }

        //check if enemy is dead:
        if (enemyHealth <= 0 || enemyMind <= 0){
            fightWon = true;
            break;
        }

        //reprint the stats and info:
        system("cls");
        optionsOutput(username, enemyName, playerHealth, enemyHealth, playerMind, enemyMind);

        //Enemy's turn to attack:
        code.decipherS(server.sendToServer(code.cipher("10", username, enemyName, to_string(playerBlocking))));
        int enemyAttack = stoi(code.getItemS(1));
        enemyAttack = (enemyBlocking) ? 0 : enemyAttack; //set attack to 0 damage if enemy is blocking
        string enemyAttackType = code.getItemS(2);

        //check during battle passives:
        Passives passive;
        passive.duringBattleEnemyAttackPassives();

        if(enemyAttackType == "Psychic"){
            cout << "The enemy's mental attack hits your mind for " << enemyAttack << " damage" << endl;
            system("pause");
            playerMind -= enemyAttack;
            player.setMind(playerMind);
            enemyAttack = 0;
        }else{
            cout << "The enemies attack hits you for " << enemyAttack << " damage" << endl;
            system("pause");
            playerHealth -= enemyAttack;
            player.setHealth(playerHealth);
            enemyAttack = 0;
        }

        if (playerHealth <= 0 || playerMind <= 0) {
            fightLost = true;
            break;
        }
    }
    //print out the result of the fight
    if (fightWon) { //the player has won the fight
        system("cls");
        //increase user xp, since fight was won.
        string playerLevel = server.sendToServer(code.cipher("14", username, to_string(enemyNum), "WillNeedToFeedBackEnemyLevel")); //this will need to send the enemy level later on.
        if(enemyMind <= 0){
            cout <<  setfill(' ') << setw(60) << "You broke the Enemy's mind!" << endl;
        }else{
            cout <<  setfill(' ') << setw(60) << "You kicked the Enemy's brass!" << endl;
        }
        cout <<  setfill(' ') << setw(57) << "You won the Battle!" << endl;
        cout <<  setfill(' ') << setw((77 - 16) - playerLevel.length()) << "Your level is: " << playerLevel << endl;
        system("pause");
        system("cls"); 
        int currentPlayerLevel = account.getLevel(username);
        if(playerLevelAtStartOfFight < currentPlayerLevel){ //runs the level update for stats
            account.levelUp(username, currentPlayerLevel);
            TempEntity playerE{username};
            setPlayer(playerE);
        }else{
            player.setCurrentXP(account.getCurrentXPForNextLevel(username));//This was added because XP was not updating in player stats after battles
        }
        player.setBattleResult(true);
        player.setLocation(location);
        system("cls");
    } else if (fightLost){ //the enemy has won the fight
        system("cls");
        if(playerMind <= 0){
            cout <<  setfill(' ') << setw(60) << "The Enemy broke your mind!" << endl;
        }else{
            cout <<  setfill(' ') << setw(60) << "The Enemy kicked your brass!" << endl;
        }
        cout <<  setfill(' ') << setw(58) << "You Lost the Battle!" << endl;
        system("pause");
        system("cls");
    }
    //cout << "Player ended Battle with " << player.getHealth() << " health!\n";
    //system("pause");
}


void Battle::tempEntBattle(TempEntity player){
    setPlayer(player); //load in the players stats from tempentity data
    standardBattle(player);
}

//probably not needed since the quest battle function does everything we need. I would like to use this and make one for travel combat.
void Battle::standardBattle(TempEntity player){
    system("cls");
    TempEntity battlingStatsOfPlayer;
    battlingStatsOfPlayer = player; //setup a duplicate account we can use for changing player stats in battle

    //setup other variables:
    bool qKeyPressedLastLoop = false, wKeyPressedLastLoop = false, eKeyPressedLastLoop = false, rKeyPressedLastLoop = false;
    bool playerBlocking = false;
    int enemyHealth;
    int playerLevelAtStartOfFight = 0;
    int ultimateUses = 1;
    string enemyName = "";
    string answer;
    bool fightWon = false, fightLost = false;
    ReachOutToServer server;
    Cipher code;
    Account account;

    //before battle Passives:
    Passives passive;
    passive.preBattlePassives(); //checking if there is any pre battle passives which need to be run

    //**************************
    //Start Battle clearing the screen
    while (!fightWon && !fightLost){//loop through displaying the stats and having the player pick options until the fight is won or lost
        int combatVal = 0;
        int playerAttack = 0;
        string playerAttackType = " ";
        int enemyBlocking = 0;
        optionsOutput(player.getUsername(), enemyName, battlingStatsOfPlayer.getHealth(), enemyHealth); //outputs the options for battle
        
        //loops till the player presses one of Q W E R
        waitForButtonPress(player.getUsername(),enemyName,qKeyPressedLastLoop,wKeyPressedLastLoop,eKeyPressedLastLoop,rKeyPressedLastLoop,playerBlocking, battlingStatsOfPlayer.getHealth(),enemyHealth,ultimateUses,combatVal,playerAttack,enemyBlocking, playerAttackType);

        //check during battle passives of player's attack:
        passive.duringBattlePlayerAttackPassives();
        
        cout << "Your attack hits the enemy for " << playerAttack << " damage" << endl;
        system("pause");

        //check if enemy is dead:
        if (enemyHealth <= 0){
            fightWon = true;
            break;
        }

        //reprint the stats and info:
        system("cls");
        optionsOutput(player.getUsername(), enemyName, battlingStatsOfPlayer.getHealth(), enemyHealth);

        //Enemy's turn to attack:
        int enemyAttack = stoi(server.sendToServer(code.cipher("10", player.getUsername(), enemyName, to_string(playerBlocking))));
        enemyAttack = (enemyBlocking) ? 0 : enemyAttack; //set attack to 0 damage if enemy is blocking

        //check during battle passives of enemies attack:
        passive.duringBattleEnemyAttackPassives();

        cout << "The enemies attack hits you for " << enemyAttack << " damage" << endl;
        system("pause");
        battlingStatsOfPlayer.setHealth(battlingStatsOfPlayer.getHealth() - enemyAttack);
        //player.setHealth(playerHealth);
        enemyAttack = 0;

        if (battlingStatsOfPlayer.getHealth() <= 0) {
            fightLost = true;
            break;
        }
        //post battle passives:
        passive.postBattlePassives();
    }
    //print out the result of the fight
    if (fightWon) { //the player has won the fight
        system("cls");
        //increase user xp, since fight was won.
        string playerLevel = server.sendToServer(code.cipher("14", player.getUsername(), enemyName, "WillNeedToFeedBackEnemyLevel")); //this will need to send the enemy level later on.
        cout <<  setfill(' ') << setw(57) << "You won the Battle!" << endl;
        cout <<  setfill(' ') << setw((77 - 16) - playerLevel.length()) << "Your level is: " << playerLevel << endl;
        system("pause");
        system("cls"); 
        int currentPlayerLevel = account.getLevel(player.getUsername());
        if(playerLevelAtStartOfFight < currentPlayerLevel){ //runs the level update for stats
            account.levelUp(player.getUsername(), currentPlayerLevel);
        }
        system("cls");
    } else if (fightLost){ //the enemy has won the fight
        system("cls");
        cout <<  setfill(' ') << setw(58) << "You Lost the Battle!" << endl;
        system("pause");
        system("cls");
    }
    //cout << "Player ended Battle with " << player.getHealth() << " health!\n";
    //system("pause");
}


int Battle::getPlayerHealth(){
    //return player.getHealth();
    return 0;
}