#include "Passives.h"

using namespace std;

void Passives::preBattlePassives(){
    
}
void Passives::duringBattlePlayerAttackPassives(){

}
void Passives::duringBattleEnemyAttackPassives(){

}
void Passives::postBattlePassives(){

}

//Passive list:
void Passives::redirectAttack(){

}
void Passives::ignoreAttack(){

}
void Passives::bonusStats(){

}
void Passives::stun(){

}
void Passives::poison(){

}
void Passives::stealStats(){

}


int Passives::getBonusHealth(){
    if(tough){
        bonusHealth += 30;
    }

    return bonusHealth;
}
bool Passives::hasStunAttack(){
    return stunAttack;
}
bool Passives::isEthereal(){
    return ethereal;
}
float Passives::getXPMultiplier(){
    if(learning){
        XPMultiplier += 0.5f;
    }

    return XPMultiplier;
}

bool Passives::isStunned(){
    return stunned;
}
void Passives::setStunned(bool stun){
    stunned = stun;
}

void Passives::setAllTrue(){
    tough = true;
    stunAttack = true;
    ethereal = true;
    learning = true;
}