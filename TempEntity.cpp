#include <iostream>
#include <string>

#include "TempEntity.h"
#include "Items.h"
#include "Cipher.h"
#include "ReachOutToServer.h"
#include "Main.h"

using namespace std;

TempEntity::TempEntity(string currentUsername){
    try{
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
    setNaturalEnergy(stoi(code.getItemS(9)));
    setMaxMind(stoi(code.getItemS(10)));
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
    setQuest1Progress(0, 0);//temporary until we add quest data to server
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
    catch(...){
        cout << endl << "Critical Failure in TempEntity::TempEntity(string currentUsername){" << endl;
        system("pause");
    }
    
}
TempEntity::TempEntity(string currentUsername, bool NewTempEntityProccess){ //initallizes all player info by pulling it from the server in one request
    try{

    string minMaxDelimiter = " - ";
    setUsername(currentUsername);
    ReachOutToServer server;
    Cipher code;
    //set all the stats:
    code.decipher(server.sendToServer(code.cipher("23", username)), true);
    setMaxHealth(stoi(code.getItem(2,1)));
    setHealth(stoi(code.getItem(2,1)));
    setArmor(stoi(code.getItem(2,2)));
    setMagicResistance(stoi(code.getItem(2,3)));
    //find the seperator and pull the values out of it for the min and max:
    string tempPhysicalDamageString = code.getItem(2,4);
    size_t pos1 = tempPhysicalDamageString.find(minMaxDelimiter);
    setPhysicalDamageMin(stoi(tempPhysicalDamageString.substr(0, pos1)));
    tempPhysicalDamageString.erase(0, pos1 + minMaxDelimiter.length());
    setPhysicalDamageMax(stoi(tempPhysicalDamageString));
    //find the seperator and pull the values out of it for the min and max:
    string tempMagicDamageString = code.getItem(2,5);
    size_t pos2 = tempMagicDamageString.find(minMaxDelimiter);
    setMagicDamageMin(stoi(tempMagicDamageString.substr(0, pos2)));
    tempMagicDamageString.erase(0, pos2 + minMaxDelimiter.length());
    setMagicDamageMax(stoi(tempMagicDamageString)); 
    //set the rest of the stats:
    setAgility(stoi(code.getItem(2,6)));
    setStealth(stoi(code.getItem(2,7)));
    setStamina(stoi(code.getItem(2,8)));
    setNaturalEnergy(stoi(code.getItem(2,9)));
    setMaxMind(stoi(code.getItem(2,10)));
    setMind(stoi(code.getItem(2,10)));
    //find the seperator and pull the values out of it for the min and max:
    string tempPsychicDamageString = code.getItem(2,11);
    size_t pos3 = tempPsychicDamageString.find(minMaxDelimiter);
    setPsychicDamageMin(stoi(tempPsychicDamageString.substr(0, pos3)));
    tempPsychicDamageString.erase(0, pos3 + minMaxDelimiter.length());
    setPsychicDamageMax(stoi(tempPsychicDamageString)); 
    //set location:
    map.setCurrentLocation(stoi(code.getItem(2,12))); //<-----New set location system (We do not need to also store this value it temp entity)
    //the following is from old navigation system that needs to be updated:
    setLocation(stoi(code.getItem(2,12)));
    if(getLocation() < 1 || getLocation() > 6){
        setLocation(1);
    }


    setRace(code.getItem(2,13));
    setKit(code.getItem(2,14));
    setWeapon(code.getItem(2,15));
    setLevel(stoi(code.getItem(2,16)));
    setCurrentXP(stoi(code.getItem(2,17)));
    setXPForNextLevel(stoi(code.getItem(2,18)));
    setQDamageType(code.getItem(2,19));
    setWDamageType(code.getItem(2,20));
    setEDamageType(code.getItem(2,21));
    setRDamageType(code.getItem(2,22));
    
    //code.getItem(3,1) is the quest number (we will need a function to check what quest they are currently working to complete based on the server's response)
    for(int i = 0; i < NUMBER_OF_QUESTS; i++){//initializing quest progress to 0 for now
        quest1Progress[i] = 0;
    }
    if(stoi(code.getItem(3,2)) > 0 && stoi(code.getItem(3,2)) <= 8)
        setQuest1Progress(0, stoi(code.getItem(3,2)));//temporary until we add quest data to server
    //set race, kit, level, experience:

    //set inventory!!!:
    Items itemHandler;
    for(int i = 0; i < INVENTORY_SPACES; i++){
        setInventory(i, 0); //setting all spaces to 0 for now.
    }
    for(int i = 0; i < inventorySize; i++){
        setInventory(i, stoi(code.getItem(4, (i+3))));
        
    }
    setPrimaryHand(stoi(code.getItem(4, 1)));
    setOffHand(stoi(code.getItem(4, 2)));    
    
    }
    catch(...){
        cout << endl << "Critical Failure in TempEntity::TempEntity(string currentUsername, bool NewTempEntityProccess){" << endl;
        system("pause");
    }
}
TempEntity::TempEntity(){//blank constructor if no username has been provided so far
    health = armor = magicResistance = physicalDamageMin = physicalDamageMax = magicDamageMin = magicDamageMax = agility = stealth = stamina = naturalEnergy = 0;
    location = 1;
    for(int i = 0; i < NUMBER_OF_QUESTS; i++){
        quest1Progress[i] = 0;
    }
    for(int i = 0; i < INVENTORY_SPACES; i++){
        inventory[i] = 0;
    }
    primaryHand = offHand = 0;
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
void TempEntity::setQuest1Progress(int questNumber, int newProgress){
    quest1Progress[questNumber] = newProgress;
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
void TempEntity::setNaturalEnergy(int newNaturalEnergy){
    naturalEnergy = newNaturalEnergy;
}
void TempEntity::setMaxMind(int newMind){
    maxMind = newMind;
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
void TempEntity::setInventory(int number, int itemNum){
    inventory[number] = itemNum;
}
void TempEntity::setPrimaryHand(int itemNum){
    primaryHand = itemNum;
}
void TempEntity::setOffHand(int itemNum){
    offHand = itemNum;
}
void TempEntity::setInventorySize(int newInventorySize){
    inventorySize = newInventorySize;
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
void TempEntity::updateNaturalEnergy(int addNaturalEnergy){
    naturalEnergy += addNaturalEnergy;
}
void TempEntity::updateMaxMind(int addMind){
    maxMind += addMind;
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
void TempEntity::levelUp(){
    //Probably should have the level increase occur here
    //level++; 
    int cursor = 4, statPoints = getLevel();
    bool finished = false;
    int healthBonus = 0, armorBonus = 0, magicResBonus = 0, physDamBonus = 0, magDamBonus = 0, agilityBonus = 0, stealthBonus = 0, staminaBonus = 0, nEnergyBonus = 0, mindBonus = 0, psychDamBonus = 0;

    system("cls");
    menu.display(32, 1, "!!! LEVEL UP !!!");//midpoint 8-9
    menu.display(26, 2, "You have " + to_string(statPoints) + " points remaining.");//midpoint 14-15 or 15

    menu.display(16, 4, "Increase Health:", false); menu.display(52, 4, to_string(healthBonus), false);
    menu.display(16, 5, "Increase Armor:", false); menu.display(52, 5, to_string(armorBonus), false);
    menu.display(16, 6, "Increase Magic Resistance:", false); menu.display(52, 6, to_string(magicResBonus), false);
    menu.display(16, 7, "Increase Physical Damage:", false); menu.display(52, 7, to_string(physDamBonus), false);
    menu.display(16, 8, "Increase Magic Damage:", false); menu.display(52, 8, to_string(magDamBonus), false);
    menu.display(16, 9, "Increase Agility:", false); menu.display(52, 9, to_string(agilityBonus), false);
    menu.display(16, 10, "Increase Stealth:", false); menu.display(52, 10, to_string(stealthBonus), false);
    menu.display(16, 11, "Increase Stamina:", false); menu.display(52, 11, to_string(staminaBonus), false);
    menu.display(16, 12, "Increase Natural Energy:", false); menu.display(52, 12, to_string(nEnergyBonus), false);
    menu.display(16, 13, "Increase Mind:", false); menu.display(52, 13, to_string(mindBonus), false);
    menu.display(16, 14, "Increase Psychic Damage:", false); menu.display(52, 14, to_string(psychDamBonus), false);
    menu.display(16, 16, "Press \"0\" to Finish");

    while(!finished){
        
        
        menu.display(51, cursor, "<");
            menu.display(54, cursor, ">");

        int value = menu.arrowPressWait(true);
        switch(value){
        case 0:{
            menu.display(52, 16, "Are you sure? (Y/N)");
            char ynResponse = menu.yesOrNo();
            if(ynResponse == 'y'||ynResponse == 'Y'){
                if(statPoints > 0){
                    menu.display(16, 17, "YOU STILL HAVE POINTS TO SPEND! ARE YOU SUPER SURE??? (Y/N)");
                    char ynResponse2 = menu.yesOrNo();
                    if(ynResponse2 == 'y'||ynResponse2 == 'Y') finished = true;
                    else{
                        menu.display(16, 17, "                                                          ");
                        menu.display(52, 16, "                   ");
                    }
                }else finished = true;
            }else menu.display(52, 16, "                   ");
            break;
        }
        case 1:
            menu.display(51, cursor, " ");
            menu.display(54, cursor, " ");
            if(cursor > 4) cursor--;            
            break;
        case 2:
            if(statPoints > 0){
                statPoints--; menu.display(35, 2, to_string(statPoints) + " ");
                if(cursor == 4){ healthBonus++; menu.display(52, cursor, to_string(healthBonus) + " ");}
                else if(cursor == 5){ armorBonus++; menu.display(52, cursor, to_string(armorBonus) + " ");}
                else if(cursor == 6){ magicResBonus++; menu.display(52, cursor, to_string(magicResBonus) + " ");}
                else if(cursor == 7){ physDamBonus++; menu.display(52, cursor, to_string(physDamBonus) + " ");}
                else if(cursor == 8){ magDamBonus++; menu.display(52, cursor, to_string(magDamBonus) + " ");}
                else if(cursor == 9){ agilityBonus++; menu.display(52, cursor, to_string(agilityBonus) + " ");}
                else if(cursor == 10){ stealthBonus++; menu.display(52, cursor, to_string(stealthBonus) + " ");}
                else if(cursor == 11){ staminaBonus++; menu.display(52, cursor, to_string(staminaBonus) + " ");}
                else if(cursor == 12){ nEnergyBonus++; menu.display(52, cursor, to_string(nEnergyBonus) + " ");}
                else if(cursor == 13){ mindBonus++; menu.display(52, cursor, to_string(mindBonus) + " ");}
                else if(cursor == 14){ psychDamBonus++; menu.display(52, cursor, to_string(psychDamBonus) + " ");}
            }
            break;
        case 3:
            menu.display(51, cursor, " ");
            menu.display(54, cursor, " ");
            if(cursor < 14) cursor++;
            break;
        case 4:
        if(statPoints < level){
                statPoints++; menu.display(35, 2, to_string(statPoints) + " ");
                if(cursor == 4){ healthBonus--; menu.display(52, cursor, to_string(healthBonus) + " ");}
                else if(cursor == 5){ armorBonus--; menu.display(52, cursor, to_string(armorBonus) + " ");}
                else if(cursor == 6){ magicResBonus--; menu.display(52, cursor, to_string(magicResBonus) + " ");}
                else if(cursor == 7){ physDamBonus--; menu.display(52, cursor, to_string(physDamBonus) + " ");}
                else if(cursor == 8){ magDamBonus--; menu.display(52, cursor, to_string(magDamBonus) + " ");}
                else if(cursor == 9){ agilityBonus--; menu.display(52, cursor, to_string(agilityBonus) + " ");}
                else if(cursor == 10){ stealthBonus--; menu.display(52, cursor, to_string(stealthBonus) + " ");}
                else if(cursor == 11){ staminaBonus--; menu.display(52, cursor, to_string(staminaBonus) + " ");}
                else if(cursor == 12){ nEnergyBonus--; menu.display(52, cursor, to_string(nEnergyBonus) + " ");}
                else if(cursor == 13){ mindBonus--; menu.display(52, cursor, to_string(mindBonus) + " ");}
                else if(cursor == 14){ psychDamBonus--; menu.display(52, cursor, to_string(psychDamBonus) + " ");}
            }
            break;
        default:
            cout << "Yo I don't know what happened bruh" << endl;
            break;
        }

    }

    updateMaxHealth(healthBonus);
    updateArmor(armorBonus);
    updateMagicResistance(magicResBonus);
    updatePhysicalDamageMin(physDamBonus);
    updatePhysicalDamageMax(physDamBonus);
    updateMagicDamageMin(magDamBonus);
    updateMagicDamageMax(magDamBonus);
    updateAgility(agilityBonus);
    updateStealth(stealthBonus);
    updateStamina(staminaBonus);
    updateNaturalEnergy(nEnergyBonus);
    updateMind(mindBonus);
    updatePsychicDamageMin(psychDamBonus);
    updatePsychicDamageMax(psychDamBonus);

    guard.updateSaveValueMaxHealth(healthBonus);
    guard.updateSaveValueArmor(armorBonus);
    guard.updateSaveValuePhysicalDamageMax(physDamBonus);
    guard.updateSaveValueMagicResistance(magicResBonus);
    guard.updateSaveValueMagicDamageMax(magDamBonus);
    guard.updateSaveValueAgility(agilityBonus);
    guard.updateSaveValueStealth(stealthBonus);
    guard.updateSaveValueStamina(staminaBonus);
    guard.updateSaveValueNaturalEnergy(nEnergyBonus);
    guard.updateSaveValueMaxMind(mindBonus);
    guard.updateSaveValuePsychicDamageMax(psychDamBonus);
    
}

void TempEntity::updateInventorySize(int addInventory){
    inventorySize += addInventory;
}
void TempEntity::sortInventory(){
    //int emptyIndex;
    for(int i = 0; i < inventorySize; i++){
        if(inventory[i] == 0){
            for(int j = i + 1; j < inventorySize; j++){
                if(inventory[j] != 0){
                    inventory[i] = inventory[j];
                    inventory[j] = 0;
                    j = inventorySize;
                }else if(j == inventorySize - 1){
                    i = inventorySize;
                }
            }
        }
    }
}

void TempEntity::addInventoryItem(int itemNum){
    for(int i = 0; i < inventorySize; i++){
        if(inventory[i] == 0){
            inventory[i] = itemNum;
            return;
        }
    }
    if(offHand == 0){
        offHand = itemNum;
        return;
    }
    if(primaryHand == 0){
        primaryHand = itemNum;
        return;
    }
    system("cls");
    Items itemHandler;
    bool noDecision = true;
    while(noDecision){
        menu.display(1, 1, "You can't carry the " + itemHandler.getName(itemNum) + ". You can either:");
        menu.display(1, 2, "Drop something    (Press \"1\")");
        menu.display(1, 3, "Discard new item  (Press \"2\")");

        int choice = menu.numberPressWait(2);
        if(choice == 1){
            int droppedItem = dropItem();
            if(droppedItem != 0){
                inventory[inventorySize - 1] = itemNum;
                noDecision = false;
            }
        }else{
            noDecision = false;
        }
        system("cls");
    }
}

int TempEntity::dropItem(){
    Items itemHandler;
    int items = 0;
    int page = 0;
    int choice = 0;
    bool keepLooping;
    for(int i = 0; i < getInventorySize(); i++){
        if(getInventory(i) != 0){
            items++;
        }else{
            break;
        }
    }
    do{
        keepLooping = false;
        int items2 = 0;
        system("cls");
        menu.display(1, 1, "If you drop something, you might not find it later. Drop which item?");
        for(int i = 0; i < 8; i++){
            if(items2 + (page*8) < items){
                menu.display(1, 2 + i, itemHandler.getName(inventory[i + (page*8)])); menu.display(32, 2 + i, ("Press \"" + to_string(i + 1) + "\""));
                items2++;
            }
            if(inventory[i] == 0){
                i = 24;
            }
        }
        if(items - (page*8) > 9){
            menu.display(1, 11, "Next Page");
            menu.display(32, 11, "Press \"9\"");
            items2++;
        }else if(items - (page*8) == 9){
            menu.display(1, 10, itemHandler.getName(getInventory(8 + (page*8))));
            menu.display(32, 10, "Press \"9\"");
            items2++;
        }
        menu.display(24, 3 + items2, "Cancel: Press \"0\"");
        choice = menu.numberPressWait(items2, true);
        if(choice == 9 && items - (page*8) != 9){
            page++;
            keepLooping = true;
        }else if(choice != 0){
            inventory[choice - 1 + (page*8)] = 0;
            sortInventory();
        }
    }while(keepLooping);
    system("cls");
    return choice;
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