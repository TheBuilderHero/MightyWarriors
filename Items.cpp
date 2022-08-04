#include <iostream>
#include <string>

#include "Items.h"

using namespace std;

string Items::getWeaponName(int number){
    return allWeaponNames[number];
}
int Items::getPhysicalDamage(int number){
    return allWeaponPhysicalDamage[number];
}
int Items::getMagicDamage(int number){
    return allWeaponMagicDamage[number];
}
int Items::getPsychicDamage(int number){
    return allWeaponPsychicDamage[number];
}

int Items::getWeaponNumber(string weaponName){
    for(int i = 1; i < ALL_WEAPONS; i++){
        if(allWeaponNames[i] == weaponName){
            return i;
        }
    }
    return 0;
}