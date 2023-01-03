#include <string>
#include <vector>
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

bool Passives::rollExtraAttack(){
    if(extraAttack){
        if(!extraAttackUsed){
            srand(time(NULL));
            if(rand()%10 == 0){
                extraAttackUsed = true;
                return true;
            }
        }else{
            extraAttackUsed = false;
        }
    }
    return false;
}
bool Passives::checkExtraAttack(){
    return extraAttack;
}
void Passives::setExtraAttack(bool value){
    extraAttack = value;
}

void Passives::setAllTrue(){
    tough = true;
    stunAttack = true;
    extraAttack = true;
    ethereal = true;
    learning = true;
}

void Passives::addAllOffense(){
    addActiveOffensePassive(1);
    addActiveOffensePassive(2);
    addActiveOffensePassive(3);
}

void Passives::setEffect(effect chosenEffect, bool status){
    switch (chosenEffect){
        case STUN:{
            stunned = status;
            break;
        }
        case POISON:{
            poisoned = status;
            break;
        }
        case DIZZY:{
            dizzied = status;
            break;
        }

        default: //not recognized effect
            break;
    }
}
bool Passives::getEffectStatus(effect chosenEffect){
    
    switch (chosenEffect){
        case STUN:{
            return stunned;
        }
        case POISON:{
            return poisoned;
        }
        case DIZZY:{
            return dizzied;
        }
        default: //not recognized effect
            return false;
    }
}

int Passives::getActiveOffensePassivesCount(){
    return activeOffensePassivesCount;
}
int Passives::getActiveOffensePassive(int index){
    return offensePassivesList[index];
}
string Passives::getActiveOffensePassiveName(int index){
    int passive = offensePassivesList[index];
    switch(passive){
        case 1:
            return "Stun";
            break;
        case 2:
            return "Poison";
            break;
        case 3:
            return "Dizzy";
            break;
        default:
            return "Error";
            break;
    }
}
void Passives::addActiveOffensePassive(int passive){
    for(int i = 0; i < 10; i++){
        if(offensePassivesList[i] == 0){
            offensePassivesList[i] = passive;
            activeOffensePassivesCount++;
            return;
        }else if(offensePassivesList[i] == passive){
            return;
        }
    }
}
void Passives::removeActiveOffensePassive(int passive){
    for(int i = 0; i < 10; i++){
        if(offensePassivesList[i] == passive){
            offensePassivesList[i] = 0;
            activeOffensePassivesCount--;
            
            int tempList[10] = {0, 0, 0, 0, 0,  0, 0, 0, 0, 0};;;;;;;
            int tempIndex = 0; 
            for(int j = 0; j < 10; j++){
                if(offensePassivesList[j] != 0){
                    tempList[tempIndex] = offensePassivesList[j];
                    tempIndex++;
                }
            }
            for(int j = 0; j < 10; j++){
                offensePassivesList[j] = tempList[j];
            }

            return;
        }
    }
}
void Passives::clearOffensePassives(){
    for(int i = 0; i < 10; i++){
        offensePassivesList[i] = 0;
    }
    activeOffensePassivesCount = 0;
}

int Passives::getActiveDebuffCount(){
    return activeDebuffCount;
}
int Passives::getActiveDebuff(int index){
    return debuffList[index];
}
void Passives::addActiveDebuff(int debuff){
    if(debuff == STUN){
        stunned = true;
    }
    for(int i = 0; i < 10; i++){
        if(debuffList[i] == 0){
            debuffList[i] = debuff;
            activeDebuffCount++;
            return;
        }else if(debuffList[i] == debuff){
            return;
        }
    }
}
void Passives::removeActiveDebuff(int debuff){
    if(debuff == STUN){
        stunned = false;
    }
    for(int i = 0; i < 10; i++){
        if(debuffList[i] == debuff){
            debuffList[i] = 0;
            activeDebuffCount--;
            
            int tempList[10] = {0, 0, 0, 0, 0,  0, 0, 0, 0, 0};;
            int tempIndex = 0; 
            for(int j = 0; j < 10; j++){
                if(debuffList[j] != 0){
                    tempList[tempIndex] = debuffList[j];
                    tempIndex++;
                }
            }
            for(int j = 0; j < 10; j++){
                debuffList[j] = tempList[j];
            }

            return;
        }
    }
}
void Passives::clearDebuffs(){
    for(int i = 0; i < 10; i++){
        debuffList[i] = 0;
    }
    activeDebuffCount = 0;
}

string Passives::getOffensePassiveMessage(int index){
    int passive = offensePassivesList[index];

    switch(passive){
        case STUN:
            return "stuns";
            break;
        case POISON:
            return "poisons";
            break;
        case DIZZY:
            return "dizzies";
            break;
        default:
            return "does nothing to";
            break;
    }
}
string Passives::getDebuffMessage(int index){
    int debuff = debuffList[index];

    switch(debuff){
        case STUN:
            return "stunned and cannot attack!";
            break;
        case POISON:
            return "poisoned and feels bad!";
            break;
        case DIZZY:
            return "dizzy and stumbles around!";
            break;
        default:
            return "getting broken code because of Dakota!";
            break;
    }
}