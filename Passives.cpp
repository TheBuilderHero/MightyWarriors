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
    bonusHealth = 0;

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
    XPMultiplier = 0.0f;
    
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

void Passives::setEffect(int effect, bool status){
    if(effect == STUN){
        stunned = status;
    }else if(effect == POISON){
        poisoned = status;
    }
}
bool Passives::getEffectStatus(int effect){
    if(effect == STUN){
        return stunned;
    }else if(effect == POISON){
        return poisoned;
    }

    return false;
}