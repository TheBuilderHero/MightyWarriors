#include <iostream>
#include <string>

#include "TempEntity.h"
#include "Cipher.h"
#include "ReachOutToServer.h"

using namespace std;

TempEntity::TempEntity(string currentUsername){
    //causing issues with starting the program without the server running.
    //It gives a stoi error:
    
    string minMaxDelimiter = " - ";
    setUsername(currentUsername);
    ReachOutToServer server;
    Cipher code;
    //set all the stats:
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    setMaxHealth(stoi(code.getItemS(1)));
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
    setMind(stoi(code.getItemS(10)));
    //find the seperator and pull the values out of it for the min and max:
    string tempPsychicDamageString = code.getItemS(11);
    size_t pos3 = tempPsychicDamageString.find(minMaxDelimiter);
    setPsychicDamageMin(stoi(tempPsychicDamageString.substr(0, pos3)));
    tempPsychicDamageString.erase(0, pos3 + minMaxDelimiter.length());
    setPsychicDamageMax(stoi(tempPsychicDamageString)); 
    //set location:
    code.decipherS(server.sendToServer(code.cipher("18", username)));
    setLocation(stoi(code.getItemS(1)));
    if(getLocation() < 1 || getLocation() > 6){
        setLocation(1);
    }
    setQuest1Progress(0);//temporary until we add quest data to server
    //set race, kit, level, experience:
    code.decipherS(server.sendToServer(code.cipher("21", username)));
    setRace(code.getItemS(1));
    setKit(code.getItemS(2));
    setWeapon(code.getItemS(3));
    setLevel(stoi(code.getItemS(4)));
    setCurrentXP(stoi(code.getItemS(5)));
    setXPForNextLevel(stoi(code.getItemS(6)));
    setQDamageType(code.getItemS(7));
    setWDamageType(code.getItemS(8));
    setEDamageType(code.getItemS(9));
    setRDamageType(code.getItemS(10));
    
}
TempEntity::TempEntity(){//blank constructor if no username has been provided so far
    health = armor = magicResistance = physicalDamageMin = physicalDamageMax = magicDamageMin = magicDamageMax = agility = stealth = stamina = mana = 0;
    location = 1;
    quest1Progress = 0;
    level = 1;
    currentXP = 0;
    XPForNextLevel = 500;
    name = username = race = kit = weapon = "Undefined";
}
TempEntity::~TempEntity(){

}

//setter functions:
void TempEntity::setUsername(string newUsername){
    username = newUsername;
}
void TempEntity::setLocation(int currentLocationValue){
    location = currentLocationValue;
}
void TempEntity::setQuest1Progress(int newProgress){
    quest1Progress = newProgress;
}
//stats:
void TempEntity::setMaxHealth(int newHealth){
    maxHealth = newHealth;
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
void TempEntity::setMind(int newMind){
    mind = newMind;
}
void TempEntity::setPsychicDamageMin(int newPsychicDamageMin){
    psychicDamageMin = newPsychicDamageMin;
}
void TempEntity::setPsychicDamageMax(int newPsychicDamageMax){
    psychicDamageMax = newPsychicDamageMax;
}

void TempEntity::setRace(string newRace){
    race = newRace;
}
void TempEntity::setKit(string newKit){
    kit = newKit;
}
void TempEntity::setWeapon(string newWeapon){
    weapon = newWeapon;
}
void TempEntity::setQDamageType(string newDamageType){
    qDamageType = newDamageType;
}
void TempEntity::setWDamageType(string newDamageType){
    wDamageType = newDamageType;
}
void TempEntity::setEDamageType(string newDamageType){
    eDamageType = newDamageType;
}
void TempEntity::setRDamageType(string newDamageType){
    rDamageType = newDamageType;
}
void TempEntity::setLevel(int newLevel){
    level = newLevel;
}
void TempEntity::setCurrentXP(int newXP){
    currentXP = newXP;
}
void TempEntity::setXPForNextLevel(int newXPForNextLevel){
    XPForNextLevel = newXPForNextLevel;
}

//updater functions:
//stats:
void TempEntity::updateMaxHealth(int addHealth){
    maxHealth += addHealth;
}
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
void TempEntity::updateMind(int addMind){
    mind += addMind;
}
void TempEntity::updatePsychicDamageMin(int addPsychicDamageMin){
    psychicDamageMin += addPsychicDamageMin;
}
void TempEntity::updatePsychicDamageMax(int addPsychicDamageMax){
    psychicDamageMax += addPsychicDamageMax;
}

void TempEntity::updateCurrentXP(int addXP){
    currentXP += addXP;
}
void TempEntity::updateLevel(int addLevel){
    level += addLevel;
}


//Richard functions:
string TempEntity::getName(){
    return name;
}
void TempEntity::setName(string newName){
    name = newName;
}
void TempEntity::damage(int damage){
    health -= damage;
}
void TempEntity::heal(int healing){
    health += healing;
}