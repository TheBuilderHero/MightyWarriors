#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>

#include "GlobalVariables.h"
#include "Account.h"
#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Menu.h"
#include "Battle.h"
#include "Passives.h"
#include "TempEntity.h"
#include "Items.h"

//extern Menu menu;

using namespace std;

/*
void Battle::optionsOutput(string username, string enemyName, int playerHealth, int enemyHealth){
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
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
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    cout << endl << setfill(' ') << setw(20 + username.length()) << username  << setfill(' ') << setw(47 + enemyName.length()) << enemyName << endl; //print the current stats of both the enemy and the Player
    cout << endl << setfill(' ') << setw(30) << "Player Health: " << playerHealth << setfill(' ') << setw(50) << "Enemy Health: " << enemyHealth << endl; //print the current stats of both the enemy and the Player
    cout << endl << setfill(' ') << setw(30) << "Player Mind: " << playerMind << setfill(' ') << setw(50) << "Enemy Mind: " << enemyMind << endl;
    cout << endl << endl << endl << setfill(' ') << setw(63) << "Please choose an attack option" <<//give the user a list of options to choose from in order to fight the enemy
    endl << setfill(' ') << setw(41) << "Attack 1" << setfill(' ') << setw(25) <<"(type number \"Q\")" << endl;
    cout << setfill(' ') << setw(38) << "Block" << setfill(' ') << setw(28) <<"(type number \"W\")" << endl;
    cout << setfill(' ') << setw(40) << "Utility" << setfill(' ') << setw(26) <<"(type number \"E\")" << endl;
    cout << setfill(' ') << setw(48) << "Ultimate Attack" << setfill(' ') << setw(18) <<"(type number \"R\")" << endl;
    cout << setfill(' ') << setw(48) << "Deselect" << setfill(' ') << setw(18) <<"(type number \"0\")" << endl;
}

//loops till the player presses one of Q W E R
void Battle::waitForButtonPress(string username, string &enemyName, bool &zeroPressKeyPressedLastLoop, bool &lPressKeyPressedLastLoop, bool &qKeyPressedLastLoop, bool &wKeyPressedLastLoop, bool &eKeyPressedLastLoop, bool &rKeyPressedLastLoop, bool &playerBlocking, int playerHealth, int &enemyHealth, int &ultimateUses, int &combatVal, int &playerAttack, int &enemyBlocking, string &playerAttackType){
    ReachOutToServer server;
    Cipher code;
    string qOption = "1", wOption = "2", eOption = "3", rOption = "4";
    while (1) //continues to run until broken out.
        {
            if (GetKeyState('R') < 0 && !rKeyPressedLastLoop && ultimateUses > 0) {//checks to make sure that the key is pressed and makes sure it was not pressed last check
                playerAttackType = player.getRDamageType();
                //playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, rOption, to_string(player.getPrimaryHand())))); //gets damage info from the server to determine the amount inflicted on the enemy;
                code.decipherS(server.sendToServer(code.cipher("9", username, enemyName, rOption, to_string(player.getPrimaryHand())))); //ask if enemy is blocking next attack and get BLOCK_REDUCTION_VALUE from server
                playerAttack = stoi(code.getItemS(1));
                enemyBlocking = stoi(code.getItemS(2)); //set enemyBlocking from server
                if(playerAttackType != "Psychic"){
                    if (!enemyBlocking) enemyHealth -= playerAttack; //if the enemy is not blocking do full damage otherwise reduce it by the BLOCK_REDUCTION_VALUE sent over by the server.
                    if (enemyBlocking) enemyHealth -= (playerAttack *= stod(code.getItemS(3))); //reduce attack by BLOCK_REDUCTION_VALUE
                }
                ultimateUses--; //take away one of the ult uses.
                rKeyPressedLastLoop = true;
                break;
            } else if (GetKeyState('R') < 0 && !rKeyPressedLastLoop && ultimateUses <= 0) {
                menu.display(8, 13, "You do not have any more ultimate uses, okay?", false);
                system("pause");
                menu.display(8, 13, "                                             ");
                menu.display(8, 14, "                                             ");
            } else if (GetKeyState('R') >= 0){// else R not pressed
                rKeyPressedLastLoop = false;
            }
            if (GetKeyState('E') < 0 && eKeyPressedLastLoop == false) {//checks to make sure that the key is pressed and makes sure it was not pressed last check
                playerAttackType = player.getEDamageType();
                //playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, eOption, to_string(player.getPrimaryHand())))); //gets damage info from the server to determine the amount inflicted on the enemy;
                code.decipherS(server.sendToServer(code.cipher("9", username, enemyName, eOption, to_string(player.getPrimaryHand())))); //ask if enemy is blocking next attack and get BLOCK_REDUCTION_VALUE from server
                playerAttack = stoi(code.getItemS(1));
                enemyBlocking = stoi(code.getItemS(2)); //set enemyBlocking from server
                if(playerAttackType != "Psychic"){
                    if (!enemyBlocking) enemyHealth -= playerAttack; //if the enemy is not blocking do full damage otherwise reduce it by the BLOCK_REDUCTION_VALUE sent over by the server.
                    if (enemyBlocking) enemyHealth -= (playerAttack *= stod(code.getItemS(3))); //reduce attack by BLOCK_REDUCTION_VALUE
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
                    /*playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, wOption, to_string(player.getPrimaryHand())))); //gets damage info from the server to determine the amount inflicted on the enemy;
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
                //playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, qOption, to_string(player.getPrimaryHand())))); //gets damage info from the server to determine the amount inflicted on the enemy;
                code.decipherS(server.sendToServer(code.cipher("9", username, enemyName, qOption, to_string(player.getPrimaryHand())))); //ask if enemy is blocking next attack and get BLOCK_REDUCTION_VALUE from server
                playerAttack = stoi(code.getItemS(1));
                enemyBlocking = stoi(code.getItemS(2)); //set enemyBlocking from server
                if(playerAttackType != "Psychic"){
                    if (!enemyBlocking) enemyHealth -= playerAttack; //if the enemy is not blocking do full damage otherwise reduce it by the BLOCK_REDUCTION_VALUE sent over by the server.
                    if (enemyBlocking) enemyHealth -= (playerAttack *= stod(code.getItemS(3))); //reduce attack by BLOCK_REDUCTION_VALUE
                }
                qKeyPressedLastLoop = true;
                break;
            } else if (GetKeyState('Q') >= 0){ // else Q not pressed
                qKeyPressedLastLoop = false;
            }
            if (GetKeyState('0') < 0 && !zeroPressKeyPressedLastLoop) { //checks to make sure that the key is pressed and makes sure it was not pressed last check - also check ultimate uses
                zeroPressKeyPressedLastLoop = true;
                lazyZeroPressCheck = true;
            } else if (GetKeyState('0') >= 0){ // else Q not pressed
                zeroPressKeyPressedLastLoop = false;
                if(lazyZeroPressCheck) break;
            }
            if (GetKeyState('L') < 0 && !lPressKeyPressedLastLoop) { //checks to make sure that the key is pressed and makes sure it was not pressed last check - also check ultimate uses
                lPressKeyPressedLastLoop = true;
                lazyLPressCheck = true;
            } else if (GetKeyState('L') >= 0){ // else Q not pressed
                lPressKeyPressedLastLoop = false;
                if(lazyLPressCheck) break;
            }
        }
}

void Battle::startBattle(string username){
    bool zeroPressKeyPressedLastLoop = false, lPressKeyPressedLastLoop = false, qKeyPressedLastLoop = false, wKeyPressedLastLoop = false, eKeyPressedLastLoop = false, rKeyPressedLastLoop = false;
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
        waitForButtonPress(username,enemyName,zeroPressKeyPressedLastLoop,lPressKeyPressedLastLoop,qKeyPressedLastLoop,wKeyPressedLastLoop,eKeyPressedLastLoop,rKeyPressedLastLoop,playerBlocking,playerHealth,enemyHealth,ultimateUses,combatVal,playerAttack,enemyBlocking, playerAttackType);
        if (lazyZeroPressCheck) {
            lazyZeroPressCheck = false;
            continue;
        }
        if (lazyLPressCheck) {
            lazyLPressCheck = false;
            break;
        }
        
        cout << "Your attack hits the enemy for " << playerAttack << " damage" << endl;
        system("pause");

        //check if enemy is dead:
        if (enemyHealth <= 0){
            fightWon = true;
            break;
        }

        //reprint the stats and info:
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
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
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        //increase user xp, since fight was won.
        string playerLevel = server.sendToServer(code.cipher("14", username, enemyName, "WillNeedToFeedBackEnemyLevel")); //this will need to send the enemy level later on.
        cout <<  setfill(' ') << setw(57) << "You won the Battle!" << endl;
        cout <<  setfill(' ') << setw((77 - 16) - playerLevel.length()) << "Your level is: " << playerLevel << endl;
        system("pause");
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls"); 
        int currentPlayerLevel = account.getLevel(username);
        if(playerLevelAtStartOfFight < currentPlayerLevel){ //runs the level update for stats
            account.levelUp(username, currentPlayerLevel);
        }
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
    } else if (fightLost){ //the enemy has won the fight
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout <<  setfill(' ') << setw(58) << "You Lost the Battle!" << endl;
        system("pause");
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
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
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    bool zeroPressKeyPressedLastLoop = false, lPressKeyPressedLastLoop = false, qKeyPressedLastLoop = false, wKeyPressedLastLoop = false, eKeyPressedLastLoop = false, rKeyPressedLastLoop = false;
    bool playerBlocking = false;
    int playerHealth, enemyHealth, playerMind, enemyMind, XPDrop;
    int playerLevelAtStartOfFight = 0;
    int ultimateUses = 1;
    string enemyName = "";
    int enemyNum = 0;
    string answer;
    bool fightWon = false, fightLost = false;
    int locationX = player.getMapLocationX();
    int locationY = player.getMapLocationY();
    ReachOutToServer server;
    Cipher code;
    Account account;
    Passives passives;

    player.battleInitialize();
    cout << "\n Your passives have been set to: \n\n";
    for(int i = 0; i < player.getPassives().getActiveOffensePassivesCount(); i++){
        cout << " " << player.getPassives().getActiveOffensePassiveName(i) << " attack" << endl;
    }
    cout << endl;
    system("pause");
    system("cls");

    //Oh boy I'm trying some monster groups now
    int numberOfEnemies;
    bool potatoFight = false;
    if(quest < 10){
        numberOfEnemies = 1;
    }else{
        srand(time(NULL));
        numberOfEnemies = (rand()%2) + 1;
        for(int i = 0; i < 4; i++){
            if(rand()%4 == 0){
                numberOfEnemies += 1;
            }
        }
        /*cout << "You will be fighting " << numberOfEnemies << " enemies..." << endl;
        if(numberOfEnemies == 10){
            cout << "You are in for a slogging..." << endl;
        }
        system("pause");*/
        
        srand(time(NULL));
        if(rand()%20 == 0){
            potatoFight = true;
            numberOfEnemies = 20;
            for(int i = 0; i < 1000; i++)
            cout << "POTATO FIGHT!!! ";
            cout << "\n\nYou're doomed. :)\n";
            system("pause");
        }  
    }  
    
    system("cls");
    std::vector<TempEntity> enemies(20);//Max number of enemies is 20
    
    //**************************
    //Initalize all variables
    try {
        playerLevelAtStartOfFight = player.getLevel();
        guard.updateGuardData();
        //code.decipherS(server.sendToServer(code.cipher("6", username, guard.getInventoryString()))); //request the current stats of this user from the server //pull info from the server to get the Player's Character info
        playerHealth = player.getHealth(); //set player health
        playerMind = player.getMind();
        //player.setHealth(playerHealth);
        fightWon = fightLost = false; //set both lost and won to false
    } catch(std::invalid_argument) {
        menu.display(0, 1, "Battle initialization failed Code#: 1",false, true);
        system("pause");
        return;
    }

    try{
        code.decipher(server.sendToServer(code.cipher("25", username, to_string(quest), to_string(step), to_string(numberOfEnemies), to_string(potatoFight))), true); //Get a trash ton of enemy info for a group fight!
        for(int i = 0; i < numberOfEnemies; i++){
            enemies.at(i).setName(code.getItem(i+2, 1));
            enemies.at(i).setEnemyNumber(stoi(code.getItem(i+2, 2)));
            enemies.at(i).setHealth(stoi(code.getItem(i+2, 3))); //set enemy health
            enemies.at(i).setMind(stoi(code.getItem(i+2, 4)));
            XPDrop += stoi(code.getItem(i+2, 5));
            if(enemies.at(i).getEnemyNumber() == 2){
                if(enemies.at(i).getHealth() > 10)
                    enemies.at(i).setHealth(10);
            }
        }
    } catch(std::invalid_argument) {
        menu.display(0, 1, "Battle initialization failed Code#: 2",false, true);
        system("pause");
        return;
    }

    //**************************
    //Display player and enemies
    system("cls");
    menu.display(16, 1, username);
    menu.display(16, 2, "Health: " + to_string(playerHealth));
    menu.display(16, 3, "Mind: " + to_string(playerMind));
    for(int i = 0; i < numberOfEnemies; i++){
        menu.display(54, 1 + i, enemies.at(i).getName());
        menu.display(72, 1 + i, "Health: " + to_string(enemies.at(i).getHealth()));
        menu.display(88, 1 + i, "Mind: " + to_string(enemies.at(i).getMind()));
    }
    int cursor = 1;
    int randomizer = 0;
    //Start Battle clearing the screen
    while (!fightWon && !fightLost){//loop through displaying the stats and having the player pick options until the fight is won or lost
        int combatVal = 0;
        int playerAttack = 0;
        string playerAttackType;//set in the genius optionsOutput function   <-- this seems incorrect
        int enemyBlocking = 0;
        int killCount = 0;
        randomizer += 127;

        if(player.getPassives().isStunned()){
            menu.display(8, 8, "You are stunned. Press enter...");
            menu.waitForEnter(menu.getEnterKeyState());
            menu.display(8, 8, "                               ");
            player.setStunned(false);
        }else{
            menu.display(8, 8, "Choose an enemy to attack");
            menu.display(8, 9, "(Press \"0\" to confirm)");
            menu.display(8, 10, "                       ");
            menu.display(8, 11, "                            ");
            menu.display(8, 12, "                            ");
            menu.display(8, 13, "                            ");
            bool enemyPicked = false;
                menu.display(50, cursor, "-->");
                if(numberOfEnemies == 1){
                    enemyPicked = true;
                }
            while(!enemyPicked){//outputs the options for battle
                int choice = menu.arrowPressWait(true);
                if(choice == 0){
                    enemyPicked = true;
                }else if(choice == 1){
                    menu.display(50, cursor, "   ");
                    if(cursor > 1){
                        cursor--;
                    }else{
                        cursor = numberOfEnemies;
                    }
                    menu.display(50, cursor, "-->");
                }else if(choice == 3){
                    menu.display(50, cursor, "   ");
                    if(cursor < numberOfEnemies){
                        cursor++;
                    }else{
                        cursor = 1;
                    }
                    menu.display(50, cursor, "-->");
                }
            }
            menu.display(8, 8, "                         ");
            menu.display(8, 9, "                         ");
            
            //loops till the player presses one of Q W E R
            enemyName = enemies.at(cursor-1).getName();
            enemyHealth = enemies.at(cursor-1).getHealth();
            menu.display(8, 8, "'Q' for Primary Attack");
            menu.display(8, 9, "'W' for Block");
            menu.display(8, 10, "'E' for Utility Attack");
            menu.display(8, 11, "'R' for Ultimate Attack");
            menu.display(8, 12, "'0' to change your selection");
            menu.display(8, 13, "'L' to Run from the Battle");
            waitForButtonPress(username, enemyName, zeroPressKeyPressedLastLoop, lPressKeyPressedLastLoop, qKeyPressedLastLoop, wKeyPressedLastLoop, eKeyPressedLastLoop, rKeyPressedLastLoop, playerBlocking, playerHealth, enemyHealth, ultimateUses, combatVal, playerAttack, enemyBlocking, playerAttackType);
            
            menu.display(8, 8, "                       ");
            menu.display(8, 9, "                       ");
            menu.display(8, 10, "                       ");
            menu.display(8, 11, "                            ");
            menu.display(8, 12, "                            ");
            menu.display(8, 13, "                            ");
            if (lazyZeroPressCheck) {
                lazyZeroPressCheck = false;
                continue;
            }
            if (lazyLPressCheck) {
                lazyLPressCheck = false;
                break;
            }
            if(enemies.at(cursor-1).getEnemyNumber() == 13){
                enemyName = "normal potato";
            }
            if(playerAttackType == "Psychic"){
                enemies.at(cursor-1).updateMind(-playerAttack);
                menu.display(8, 24, "Your mental attack hits the " + enemyName + "'s mind for " + to_string(playerAttack) + " damage", false);
                system("pause");
                menu.display(8, 24, "                                                                                            ");
                menu.display(8, 25, "                                                                                            ");
                
                menu.display(94, cursor, "        ");
                if(enemies.at(cursor-1).getMind() <= 0){
                    menu.display(94, cursor, "BROKE");
                }else{
                    menu.display(94, cursor, to_string(enemies.at(cursor-1).getMind()));
                }
            }else{
                enemies.at(cursor-1).updateHealth(-playerAttack);
                menu.display(8, 24, "Your attack hits the " + enemyName + " for " + to_string(playerAttack) + " damage", false);
                int currentLine = 1;
                for(int j = 0; j < player.getPassives().getActiveOffensePassivesCount(); j++){
                    string msg = "Your attack " + player.getPassives().getOffensePassiveMessage(j) + " the " + enemyName;
                    enemies.at(cursor-1).addActiveDebuff(player.getPassives().getActiveOffensePassive(j));
                    menu.display(8, 24 + currentLine, msg, false);
                    currentLine++;
                }
                system("pause");
                for(int i = 24; i <= 24 + currentLine; i++){
                    menu.display(8, i, "                                                                              ");
                }
                
                menu.display(80, cursor, "        ");
                if(enemies.at(cursor-1).getHealth() <= 0){
                    menu.display(80, cursor, "DEAD");
                }else{
                    menu.display(80, cursor, to_string(enemies.at(cursor-1).getHealth()));
                }
            }

            //check if enemy is dead:
            for(int i = 0; i < numberOfEnemies; i++){
                if (enemies.at(i).getHealth() <= 0 || enemies.at(i).getMind() <= 0){
                    killCount++;
                }else{
                    i = numberOfEnemies;
                }
            }
            if(killCount >= numberOfEnemies){
                fightWon = true;
                break;
            }

            if(player.rollExtraAttack()){
                menu.display(8, 24, "You got an extra attack!", false);
                system("pause");
                menu.display(8, 24, "                                  ");
                menu.display(8, 25, "                                                             ");
                continue;
            }
        }

        code.decipher(server.sendToServer(code.cipher("26", username, code.subCipher(to_string(enemies.at(0).getEnemyNumber()), to_string(enemies.at(1).getEnemyNumber()), to_string(enemies.at(2).getEnemyNumber()), to_string(enemies.at(3).getEnemyNumber()), to_string(enemies.at(4).getEnemyNumber()),
        to_string(enemies.at(5).getEnemyNumber()), to_string(enemies.at(6).getEnemyNumber()), to_string(enemies.at(7).getEnemyNumber()), to_string(enemies.at(8).getEnemyNumber()), to_string(enemies.at(9).getEnemyNumber()), to_string(enemies.at(10).getEnemyNumber()), to_string(enemies.at(11).getEnemyNumber()), to_string(enemies.at(12).getEnemyNumber()), 
        to_string(enemies.at(13).getEnemyNumber()), to_string(enemies.at(14).getEnemyNumber()), to_string(enemies.at(15).getEnemyNumber()), to_string(enemies.at(16).getEnemyNumber()), to_string(enemies.at(17).getEnemyNumber()), to_string(enemies.at(18).getEnemyNumber()), to_string(enemies.at(19).getEnemyNumber())), to_string(playerBlocking), to_string(numberOfEnemies), to_string(randomizer))), true);
        for(int i = 0; i < numberOfEnemies; i++){
            //Enemy's turn to attack:
            if(enemies.at(i).getHealth() > 0 && enemies.at(i).getMind() > 0){
                int enemyAttack = stoi(code.getItem(i+2, 1));
                string emenyName;
                if(enemies.at(i).getEnemyNumber() == 13){
                    emenyName = "normal potato";
                }else{
                    emenyName = enemies.at(i).getName();
                }
                if(i + 1 == cursor){
                    enemyAttack = (enemyBlocking) ? 0 : enemyAttack; //set attack to 0 damage if enemy is blocking
                }
                string enemyAttackType = code.getItem(i+2, 2);

                //check during battle passives:
                //Passives passive;
                //passive.duringBattleEnemyAttackPassives();
                //Lol this is not how to do passives ^^^

                if(enemies.at(i).getPassives().getActiveDebuffCount() > 0){
                    int currentLine = 0;
                    for(int j = 0; j < enemies.at(i).getPassives().getActiveDebuffCount(); j++){
                        menu.display(8, 24 + currentLine, "The " + emenyName + " is " + enemies.at(i).getPassives().getDebuffMessage(j), false);
                        currentLine++;
                    }
                    system("pause");
                    
                    for(int j = 24; j <= 24 + currentLine; j++){
                        menu.display(8, j, "                                                                              ");
                    }
                }


                if(enemies.at(i).getPassives().isStunned()){
                    enemies.at(i).removeActiveDebuff(passives.STUN);
                }else if(enemyAttackType == "Psychic"){
                    bool stun = false;
                    if(rand()%20 == 0){
                        stun = true;
                        player.setStunned(stun);
                    }
                    menu.display(8, 24, "The " + emenyName + "'s mental attack hits your mind for " + to_string(enemyAttack) + " damage", false);
                    if(stun){
                        menu.display(8, 25, "You are stunned!", false);
                    }
                    system("pause");
                    menu.display(8, 24, "                                                                                  ");
                    menu.display(8, 25, "                                                                                  ");
                    menu.display(8, 26, "                                                                                  ");
                    
                    playerMind -= enemyAttack;
                    player.setMind(playerMind);
                    enemyAttack = 0;
                    
                    menu.display(22, 3, "        ");
                    menu.display(22, 3, to_string(playerMind));
                }else{
                    bool stun = false;
                    if(rand()%20 == 0){
                        stun = true;
                        player.setStunned(stun);
                    }
                    menu.display(8, 24, "The " + emenyName + "'s attack hits you for " + to_string(enemyAttack) + " damage", false);
                    if(stun){
                        menu.display(8, 25, "You are stunned!", false);
                    }
                    system("pause");
                    menu.display(8, 24, "                                                                     ");
                    menu.display(8, 25, "                                                                     ");
                    menu.display(8, 26, "                                                                     ");
                    
                    playerHealth -= enemyAttack;
                    player.setHealth(playerHealth);
                    enemyAttack = 0;
                    
                    menu.display(24, 2, "        ");
                    menu.display(24, 2, to_string(playerHealth));
                }
            }
        }
        if (playerHealth <= 0 || playerMind <= 0) {
            fightLost = true;
            break;
        }
    }
    //print out the result of the fight
    if (fightWon) { //the player has won the fight
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        menu.display(24, 1, getVictoryMessage());
        string expString = "You earned " + to_string(XPDrop) + " experience!";
        int addXP = player.getPassives().getXPMultiplier() * XPDrop;
        if(addXP > 0){
            expString += " You got an additional " + to_string(addXP) + " experience from passives!";
            XPDrop += addXP;
        }
        menu.display(24, 2, expString, false);
        int itemDrop = 0;
        srand(time(NULL));
        if(rand() % 5 == 0){
            Items item;
            itemDrop = (rand() % 8) + 1;
            if(itemDrop == 8 && rand() % 4 > 0){

            }else{
                menu.display(24, 3 , "The Enemy dropped a " + item.getName(itemDrop) + "! ", false);
            }
        }
        system("pause");
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls"); 
        //increase user xp, since fight was won.

        //This code ensures you level up after every combat, for testing purposes
        //int xpMinusOne = player.getXPForNextLevel() - player.getCurrentXP() - 1;
        //server.sendToServer(code.cipher("14", username, "-1", to_string(xpMinusOne)));

        /*I think this is irrelevant now
        for(int i = 0; i < numberOfEnemies; i++){
            string playerLevel = server.sendToServer(code.cipher("14", username, to_string(enemies.at(i).getEnemyNumber()), "WillNeedToFeedBackEnemyLevel")); //this will need to send the enemy level later on.            
            player.setCurrentXP(account.getCurrentXPForNextLevel(username));//This was added because XP was not updating in player stats after battles
        }
        */

        server.sendToServer(code.cipher("14", username, "-1", to_string(XPDrop)));
        player.updateCurrentXP(XPDrop);
        int currentPlayerLevel = account.getLevel(username);
        player.setLevel(currentPlayerLevel);
        if(playerLevelAtStartOfFight < currentPlayerLevel){ //runs the level update for stats
            //shiny new code
            //putting this here temporarily, we should probably load xp data client-side
            player.levelUp();
            player.updateCurrentXP(player.getXPForNextLevel()*-1);
        }//else{
            //moved --> player.setCurrentXP(account.getCurrentXPForNextLevel(username));//This was added because XP was not updating in player stats after battles
            //This was moved out of this else statement to try and fix the issue of recalling levelup function.
        //}
        player.setXPForNextLevel((int)account.getTotalXPForNextLevel(username));
        
        if(itemDrop > 0) player.addInventoryItem(itemDrop); //need to put this after the level up otherwise item will be lost
        player.setBattleResult(true);
        player.setMapLocation(locationX,locationY);
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
    } else if (fightLost){ //the enemy has won the fight
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        menu.display(24, 1, getDefeatMessage());
        menu.display(24, 2, "You suck!", false);
        system("pause");
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
    }
    //cout << "Player ended Battle with " << player.getHealth() << " health!\n";
    //system("pause");
}


void Battle::tempEntBattle(){
    //setPlayer(player); //load in the players stats from tempentity data
    standardBattle();
}

//probably not needed since the quest battle function does everything we need. I would like to use this and make one for travel combat.
void Battle::standardBattle(){
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    TempEntity battlingStatsOfPlayer;
    battlingStatsOfPlayer = player; //setup a duplicate account we can use for changing player stats in battle

    //setup other variables:
    bool zeroPressKeyPressedLastLoop = false, lPressKeyPressedLastLoop = false, qKeyPressedLastLoop = false, wKeyPressedLastLoop = false, eKeyPressedLastLoop = false, rKeyPressedLastLoop = false;
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
        waitForButtonPress(player.getUsername(),enemyName,zeroPressKeyPressedLastLoop,lPressKeyPressedLastLoop,qKeyPressedLastLoop,wKeyPressedLastLoop,eKeyPressedLastLoop,rKeyPressedLastLoop,playerBlocking, battlingStatsOfPlayer.getHealth(),enemyHealth,ultimateUses,combatVal,playerAttack,enemyBlocking, playerAttackType);
        if (lazyZeroPressCheck) {
            lazyZeroPressCheck = false;
            continue;
        }
        if (lazyLPressCheck) {
            lazyLPressCheck = false;
            break;
        }


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
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
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
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        //increase user xp, since fight was won.
        string playerLevel = server.sendToServer(code.cipher("14", player.getUsername(), enemyName, "WillNeedToFeedBackEnemyLevel")); //this will need to send the enemy level later on.
        cout <<  setfill(' ') << setw(57) << "You won the Battle!" << endl;
        cout <<  setfill(' ') << setw((77 - 16) - playerLevel.length()) << "Your level is: " << playerLevel << endl;
        system("pause");
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls"); 
        int currentPlayerLevel = account.getLevel(player.getUsername());
        if(playerLevelAtStartOfFight < currentPlayerLevel){ //runs the level update for stats
            account.levelUp(player.getUsername(), currentPlayerLevel);
        }
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
    } else if (fightLost){ //the enemy has won the fight
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout <<  setfill(' ') << setw(58) << "You Lost the Battle!" << endl;
        system("pause");
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
    }
    //cout << "Player ended Battle with " << player.getHealth() << " health!\n";
    //system("pause");
}

string Battle::getVictoryMessage(){
    int numberOfMessages = 3;
    srand(time(NULL));
    int message = rand()%numberOfMessages;

    switch(message){
        case 0:
            return "You kicked the enemy's brass!";
            break;
        case 1:
            return "You wrecked the enemy's world!";
            break;
        case 2:
            return "You floss all over the enemy's corpses!";
            break;
        default:
            return "You are winner!";
            break;
    }
}
string Battle::getDefeatMessage(){
    int numberOfMessages = 14;
    srand(time(NULL));
    int message = rand()%numberOfMessages;

    switch(message){
        case 0:
            return "The enemy kicked your brass!";
            break;
        case 1:
            return "The enemy wrecked your world!";
            break;
        case 2:
            return "The enemy triumphs over your pathetic might!";
            break;
        case 3:
            return "The enemy dances on your mangled corpse!";
            break;
        case 4:
            return "The enemy teabags you in the face!";
            break;
        case 5:
            return "The enemy makes you cry like a baby!";
            break;
        case 6:
            return "The enemy crushes your dreams!";
            break;
        case 7:
            return "Victory is NOT yours, loser!";
            break;
        case 8:
            return "Get thyself defeated!";
            break;
        case 9:
            return "Return to kindergarten!";
            break;
        case 10:
            return "Aw, you'll get 'em next time... JK OF COURSE YOU WON'T!";
            break;
        case 11:
            return "The enemy shoves your head into a dung heap!";
            break;
        case 12:
            return "The enemy makes you lick their feet clean!";
            break;
        case 13:
            return "The enemy hangs you upside down and throws eggs in your face!";
            break;
        default:
            return "You a noob!";
            break;
    }
}

int Battle::getPlayerHealth(){
    //return player.getHealth();
    return 0;
}