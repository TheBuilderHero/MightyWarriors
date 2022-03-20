#include <string>
#include <iostream>

#include "Account.h"

using namespace std;

void Account::setHealth(){
    cout << "Enter the number of points you would like to add to your Health stat: ";
    cin >> health;
}
void Account::setAttack(){
    cout << "Enter the number of points you would like to add to your Health stat: ";
    cin >> attack;
}
void Account::setArmor(){
    cout << "Enter the number of points you would like to add to your Health stat: ";
    cin >> armor;
}
void Account::setMagicResistance(){
    cout << "Enter the number of points you would like to add to your Health stat: ";
    cin >> magicResistance;
}

void Account::createCharacter(){
    system("cls");
    cout << "(1ST - Health, 2ND - Attack, 3RD - Armor, 4TH - Magic Resistance)" << endl << "You have 3 points that can be added to the above stats" << endl << "Please enter the number of points to add to each stat: " << endl;
    setHealth();
    setAttack();
    setArmor();
    setMagicResistance();
}