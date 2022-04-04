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

void Battle::startBattle(string username){
    int playerHealth, enemyHealth;
    string answer;
    bool fightWon, fightLost;
    ReachOutToServer server;
    Cipher code;
    //**************************
    //Initalize all variables
    code.decipherS(server.sendToServer(code.cipher("6", username))); //request the current stats of this user from the server //pull info from the server to get the Player's Character info
    enemyHealth = 20;
    playerHealth = stoi(code.itemS1); //set player health
    fightWon = fightLost = false; //set both lost and won to false
    code.decipherS(server.sendToServer(code.cipher("7", username))); //request the current stats of a enemy from the server //pull data from the server regarding the enemy to fight
    enemyHealth = stoi(code.itemS1); //set enemy health
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
        cout << endl << setfill(' ') << setw(30) << "Player Health: " << playerHealth << setfill(' ') << setw(50) << "Enemy Health: " << enemyHealth << endl; //print the current stats of both the enemy and the Player
        cout << endl << endl << endl << setfill(' ') << setw(63) << "Please choose an attack option" <<//give the user a list of options to choose from in order to fight the enemy
        endl << setfill(' ') << setw(41) << "Attack 1" << setfill(' ') << setw(25) <<"(type number \"1\")" << endl;
        cout << setfill(' ') << setw(41) << "Attack 2" << setfill(' ') << setw(25) <<"(type number \"2\")" << endl;
        cout << setfill(' ') << setw(41) << "Attack 3" << setfill(' ') << setw(25) <<"(type number \"3\")" << endl;
        cout << setfill(' ') << setw(41) << "Attack 4" << setfill(' ') << setw(25) <<"(type number \"4\")" << endl;
        cout << setfill(' ') << setw(41) << "Attack 5" << setfill(' ') << setw(25) <<"(type number \"5\")" << endl;
        cout << setfill(' ') << setw(41) << "Attack 6" << setfill(' ') << setw(25) <<"(type number \"6\")" << endl 
        << setfill(' ') << setw(35) << "> ";
        cin >> combatVal;
        switch (combatVal){
            case 1: // attack option 1
                enemyHealth -= 1;
                break;
            case 2:
                enemyHealth = 0;
                break;
            case 3:
                playerHealth -= 1;
                break;
            case 4:
                playerHealth = 0;
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                system("cls");
                cout << "You entered an invalid number... Please try again..." << endl;
                system("pause");
                system("cls");
        }
        if (playerHealth <= 0) {
            fightLost = true;
        } else if (enemyHealth <= 0){
            fightWon = true;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
    }
    //print out the result of the fight
    if (fightWon) { //the player has won the fight
        cout << "You won the Battle!" << endl;
        system("pause");
        system("cls");
    } else if (fightLost){ //the enemy has won the fight
        cout << "You Lost the Battle!" << endl;
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