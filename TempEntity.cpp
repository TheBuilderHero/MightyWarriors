#include <iostream>
#include <string>

#include "TempEntity.h"

using namespace std;

string TempEntity::getName(){
    return name;
}
void TempEntity::setName(string newName){
    name = newName;
}
int TempEntity::getHealth(){
    return health;
}
void TempEntity::setHealth(int newHealth){
    health = newHealth;
}
void TempEntity::damage(int damage){
    health -= damage;
}
void TempEntity::heal(int healing){
    health += healing;
}