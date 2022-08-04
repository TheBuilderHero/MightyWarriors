#include <iostream>
#include <string>

#include "Items.h"

using namespace std;

string Items::getName(int number){
    return itemNames[number];
}
int Items::getPhysicalDamage(int number){
    return physicalDamage[number];
}
int Items::getMagicDamage(int number){
    return magicDamage[number];
}
int Items::getPsychicDamage(int number){
    return psychicDamage[number];
}

int Items::getNumber(string itemName){
    for(int i = 1; i < ALL_ITEMS; i++){
        if(itemNames[i] == itemName){
            return i;
        }
    }
    return 0;
}