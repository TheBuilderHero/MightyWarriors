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
    cout << endl << setfill(' ') << setw(20 + username.length()) << username  << setfill(' ') << setw(47 + enemyName.length()) << enemyName << endl; //print the current stats of both the enemy and the Player
    cout << endl << setfill(' ') << setw(30) << "Player Health: " << playerHealth << setfill(' ') << setw(50) << "Enemy Health: " << enemyHealth << endl; //print the current stats of both the enemy and the Player
    cout << endl << endl << endl << setfill(' ') << setw(63) << "Please choose an attack option" <<//give the user a list of options to choose from in order to fight the enemy
    endl << setfill(' ') << setw(41) << "Attack 1" << setfill(' ') << setw(25) <<"(type number \"Q\")" << endl;
    cout << setfill(' ') << setw(38) << "Block" << setfill(' ') << setw(28) <<"(type number \"W\")" << endl;
    cout << setfill(' ') << setw(40) << "Utility" << setfill(' ') << setw(26) <<"(type number \"E\")" << endl;
    cout << setfill(' ') << setw(48) << "Ultimate Attack" << setfill(' ') << setw(18) <<"(type number \"R\")" << endl;
}

void Battle::startBattle(string username){
    bool qKeyPressedLastLoop = false, wKeyPressedLastLoop = false, eKeyPressedLastLoop = false, rKeyPressedLastLoop = false;
    bool playerBlocking = false, enemyBlocking = false;
    int playerHealth, enemyHealth;
    int ultimateUses = 1;
    string qOption = "1", wOption = "2", eOption = "3", rOption = "4";
    string answer;
    bool fightWon, fightLost;
    ReachOutToServer server;
    Cipher code;
    //**************************
    //Initalize all variables
    code.decipherS(server.sendToServer(code.cipher("6", username))); //request the current stats of this user from the server //pull info from the server to get the Player's Character info
    enemyHealth = 20;
    playerHealth = stoi(code.getItemS(1)); //set player health
    fightWon = fightLost = false; //set both lost and won to false
    code.decipherS(server.sendToServer(code.cipher("7", username))); //request the current stats of a enemy from the server //pull data from the server regarding the enemy to fight
    enemyHealth = stoi(code.getItemS(2)); //set enemy health
    string enemyName = code.getItemS(1);
    //**************************
    //Start Battle
    system("cls");
    cout << "Starting Battle simulation..." << endl; //tell user that the battle is starting
    system("pause");
    system("cls");
    //inform user who they are fighting
    cout << "Time for you to fight the worst... most evil... monster... ever... on... earth..." << endl << "Dominic!!!!!!!!" << endl;
    system("pause");
    while (!fightWon && !fightLost){//loop through displaying the stats and having the player pick options until the fight is won or lost
        system("cls");
        int combatVal = 0;
        int playerAttack = 0;
        optionsOutput(username, enemyName, playerHealth, enemyHealth); //outputs the options for battle
        
        while (1) //continues to run until broken out.
        {
            if (GetKeyState('R') < 0 && !rKeyPressedLastLoop && ultimateUses > 0) {//checks to make sure that the key is pressed and makes sure it was not pressed last check
                enemyHealth -= playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, rOption))); //gets damage info from the server to determine the amount inflicted on the enemy;
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
                enemyHealth -= playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, eOption))); //gets damage info from the server to determine the amount inflicted on the enemy;
                eKeyPressedLastLoop = true;
                break;
            } else if (GetKeyState('E') >= 0){// else E not pressed
                eKeyPressedLastLoop = false;
            }
            if (GetKeyState('W') < 0 && wKeyPressedLastLoop == false) {//checks to make sure that the key is pressed and makes sure it was not pressed last check
                //This ability now blocks instead of inflicts damage
                playerBlocking = true;
                //enemyHealth -= stoi(server.sendToServer(code.cipher("9", username, enemyName, wOption))); //gets damage info from the server to determine the amount inflicted on the enemy;
                wKeyPressedLastLoop = true;
                break;
            } else if (GetKeyState('W') >= 0){// else W not pressed
                playerBlocking = false;
                wKeyPressedLastLoop = false;
            }
            if (GetKeyState('Q') < 0 && !qKeyPressedLastLoop) { //checks to make sure that the key is pressed and makes sure it was not pressed last check - also check ultimate uses
                enemyHealth -= playerAttack = stoi(server.sendToServer(code.cipher("9", username, enemyName, qOption))); //gets damage info from the server to determine the amount inflicted on the enemy;
                qKeyPressedLastLoop = true;
                break;
            } else if (GetKeyState('Q') >= 0){ // else Q not pressed
                qKeyPressedLastLoop = false;
            }
        }
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
        cout <<  setfill(' ') << setw(57) << "You won the Battle!" << endl;
        system("pause");
        system("cls");
    } else if (fightLost){ //the enemy has won the fight
        system("cls");
        cout <<  setfill(' ') << setw(58) << "You Lost the Battle!" << endl;
        system("pause");
        system("cls");
    } /*else { //the fight was a tie //not possible
        cout << "Battle was an impossible tie..??!" << endl;
        system("pause");
        system("cls");
    }*/

    //NEED TO BE DONE//give user xp along with other, if fight was won.
    
    cout << "Would you like to Battle again? (Y/N)\n>";
    cin >> answer;
    while (!(answer == "n" || answer == "N" || answer == "y" || answer == "Y")) { //ask player if they want to battle more or go back to main menu.
        cout << endl << answer << endl;
        //answer = 'A';// set the answer variable to some other value on the start of each loop.
        cout << "Your input was not recognized." << endl << "Would you like to Battle again? (Y/N)\n>";
        cin >> answer;
    }
    if (answer == "y" || answer == "Y"){
        startBattle(username);//run battle again
    } else {
        classMenu.menu(username);//go to main menu
    }
}