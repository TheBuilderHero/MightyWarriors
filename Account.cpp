#include <string>
#include <iostream>

#include "Account.h"

using namespace std;

/*************************************************************************
The purpose of this file to to manage the user account and Character setup
*************************************************************************/



void Account::setHealth(){ //inital choise of health stats
    int healthS;
    cout << "Enter the number of points you would like to add to your Health stat: ";
    cin >> healthS;
    if (healthS <= remainingStatPoints) {
        health = healthS;
        remainingStatPoints -= healthS;
    } else {
        cout << "You entered an invalid number of statpoint to be added." << endl << "Restarting this proccess so you can complete this task.";
        health = attack = armor = magicResistance = 0;
        createCharacter();
    }
}
void Account::setAttack(){ //inistal choice of Attack stats
    int attackS;
    cout << "Enter the number of points you would like to add to your Attack stat: ";
    cin >> attackS;
    if (attackS <= remainingStatPoints) {
        attack = attackS;
        remainingStatPoints -= attackS;
    } else {
        cout << "You entered an invalid number of statpoint to be added." << endl << "Restarting this proccess so you can complete this task.";
        health = attack = armor = magicResistance = 0;
        createCharacter();
    }
}
void Account::setArmor(){ //initial choice of Armor stats
    int armorS;
    cout << "Enter the number of points you would like to add to your Armor stat: ";
    cin >> armorS;
    if (armorS <= remainingStatPoints) {
        armor = armorS;
        remainingStatPoints -= armorS;
    } else {
        cout << "You entered an invalid number of statpoint to be added." << endl << "Restarting this proccess so you can complete this task.";
        health = attack = armor = magicResistance = 0;
        createCharacter();
    }
}
void Account::setMagicResistance(){ //initial choice of Magic Resistance stats
    int magicResistanceS;
    cout << "Enter the number of points you would like to add to your Magic Resistance stat: ";
    cin >> magicResistanceS;
    if (magicResistanceS <= remainingStatPoints) {
        magicResistance = magicResistanceS;
        remainingStatPoints -= magicResistanceS;
    } else {
        cout << "You entered an invalid number of statpoint to be added." << endl << "Restarting this proccess so you can complete this task.";
        health = attack = armor = magicResistance = 0;
        createCharacter();
    }
}

void logonScreen(int type = 1); //this allows us to use the logon screen function at the end of this function and pass in the defualt value of 1
void Account::createCharacter(){ //running through the stat choosing - This is the inital user setup
    remainingStatPoints = 3;
    system("cls");
    cout << "(1ST - Health, 2ND - Attack, 3RD - Armor, 4TH - Magic Resistance)" << endl << "You have 3 points that can be distributed among the above stats" << endl;
    system("pause");
    system("cls");
    cout << "(1ST - Health, 2ND - Attack, 3RD - Armor, 4TH - Magic Resistance)" << endl << "You have 3 points that can be distributed among the above stats" << endl << endl << "Please enter the number of points to add to each stat." << endl << endl;
    setHealth();
    if (remainingStatPoints > 0) setAttack();
    if (remainingStatPoints > 0) setArmor();
    if (remainingStatPoints > 0) setMagicResistance();
    if (remainingStatPoints > 0) { //if the user did not use all their stat points we will restart the proccess
        cout << remainingStatPoints << endl;
        system("cls");
        cout << "You did not use all your Stat Points..." << endl << "Restarting this proccess so you can complete this task.";
        system("pause");
        health = attack = armor = magicResistance = 0; //reset all to 0
        createCharacter();
    }
    //Need to write the stats to file so that they are stored to be opened again later.
    //if the code makes it to this point then the user is done and will go to main menu.
    cout << "Your stat points have been to set to the following: " << endl << "Health: " << health << endl << "Attack: " << attack << endl << "Armor: " << armor << endl << "Magic Resistance: " << magicResistance << endl;
    // HasGoneThroughInitalSetup = true; //sets the value to true because the user has successfully added the 3 inital setup points to their Character.
    system("pause");
    logonScreen();
}