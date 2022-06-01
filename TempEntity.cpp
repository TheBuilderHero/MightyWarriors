#include <iostream>
#include <string>

#include "TempEntity.h"
#include "Cipher.h"
#include "ReachOutToServer.h"

using namespace std;

TempEntity::TempEntity(string currentUsername){
    string minMaxDelimiter = " - ";
    setUsername(currentUsername);
    ReachOutToServer server;
    Cipher code;
    //set all the stats:
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    setHealth(stoi(code.getItemS(1)));
    setArmor(stoi(code.getItemS(2)));
    setMagicResistance(stoi(code.getItemS(3)));
    //find the seperator and pull the values out of it for the min and max:
    string tempPhysicalDamageString = code.getItemS(4);
    size_t pos1 = tempPhysicalDamageString.find(minMaxDelimiter);
    setPhysicalDamageMin(stoi(tempPhysicalDamageString.substr(0, pos1)));
    tempPhysicalDamageString.erase(0, pos1 + minMaxDelimiter.length());
    setPhysicalDamageMax(stoi(tempPhysicalDamageString));
    //find the seperator and pull the values out of it for the min and max:
    string tempMagicDamageString = code.getItemS(5);
    size_t pos2 = tempMagicDamageString.find(minMaxDelimiter);
    setMagicDamageMin(stoi(tempMagicDamageString.substr(0, pos2)));
    tempMagicDamageString.erase(0, pos2 + minMaxDelimiter.length());
    setMagicDamageMax(stoi(tempMagicDamageString)); 
    //set the rest of the stats:
    setAgility(stoi(code.getItemS(6)));
    setStealth(stoi(code.getItemS(7)));
    setStamina(stoi(code.getItemS(8)));
    setMana(stoi(code.getItemS(9)));
}

//setter functions:
void TempEntity::setUsername(string newUsername){
    username = newUsername;
}
void TempEntity::setHealth(int newHealth){
    health = newHealth;
}
void TempEntity::setArmor(int newArmor){
    armor = newArmor;
}
void TempEntity::setMagicResistance(int newMagicResistance){
    magicResistance = newMagicResistance;
}
void TempEntity::setPhysicalDamageMin(int newPhysicalDamageMin){
    physicalDamageMin = newPhysicalDamageMin;
}
void TempEntity::setPhysicalDamageMax(int newPhysicalDamageMax){
    physicalDamageMax = newPhysicalDamageMax;
}
void TempEntity::setMagicDamageMin(int newMagicDamageMin){
    magicDamageMin = newMagicDamageMin;
}
void TempEntity::setMagicDamageMax(int newMagicDamageMax){
    magicDamageMax = newMagicDamageMax;
}
void TempEntity::setAgility(int newAgility){
    agility = newAgility;
}
void TempEntity::setStealth(int newStealth){
    stealth = newStealth;
}
void TempEntity::setStamina(int newStamina){
    stamina = newStamina;
}
void TempEntity::setMana(int newMana){
    mana = newMana;
}

//updater functions:
void TempEntity::updateHealth(int addHealth){
    health += addHealth;
}
void TempEntity::updateArmor(int addArmor){
    armor += addArmor;
}
void TempEntity::updateMagicResistance(int addMagicResistance){
    magicResistance += addMagicResistance;
}
void TempEntity::updatePhysicalDamageMin(int addPhysicalDamageMin){
    physicalDamageMin += addPhysicalDamageMin;
}
void TempEntity::updatePhysicalDamageMax(int addPhysicalDamageMax){
    physicalDamageMax += addPhysicalDamageMax;
}
void TempEntity::updateMagicDamageMin(int addMagicDamageMin){
    magicDamageMin += addMagicDamageMin;
}
void TempEntity::updateMagicDamageMax(int addMagicDamageMax){
    magicDamageMax += addMagicDamageMax;
}
void TempEntity::updateAgility(int addAgility){
    agility += addAgility;
}
void TempEntity::updateStealth(int addStealth){
    stealth += addStealth;
}
void TempEntity::updateStamina(int addStamina){
    stamina += addStamina;
}
void TempEntity::updateMana(int addMana){
    mana += addMana;
}


//Richard functions:
string TempEntity::getName(){
    return name;
}
void TempEntity::setName(string newName){
    name = newName;
}
/*int TempEntity::getHealth(){
    return health;
}
void TempEntity::setHealth(int newHealth){
    health = newHealth;
}*/
void TempEntity::damage(int damage){
    health -= damage;
}
void TempEntity::heal(int healing){
    health += healing;
}