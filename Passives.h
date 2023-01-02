#include <string>
#include <vector>

#pragma once

class Passives{
    private:
        //all passive booleans, determines active or inactive
        bool tough = false, stunAttack = false, ethereal = false, learning = false;
        
        //stat bonuses
        int bonusHealth = 0;
        float XPMultiplier = 0.0f;

        int offensePassivesList[10] = {0, 0, 0, 0, 0,  0, 0, 0, 0, 0};
        int activeOffensePassivesCount = 0;

        int debuffList[10] = {0, 0, 0, 0, 0,  0, 0, 0, 0, 0};
        int activeDebuffCount = 0;

        //negative effects
        bool stunned = false;
        bool poisoned = false;
        bool dizzied = false;

    public:
        //call to passives before, during, and after battle
        void preBattlePassives();
        void duringBattlePlayerAttackPassives();
        void duringBattleEnemyAttackPassives();
        void postBattlePassives();

        //Passive list:
        void redirectAttack();
        void ignoreAttack();
        void bonusStats();
        void stun();
        void poison();
        void stealStats();


        //Oh dear
        int getBonusHealth();
        bool hasStunAttack();
        bool isEthereal();
        float getXPMultiplier();

        bool isStunned();
        void setStunned(bool stun);

        void setEffect(int effect, bool status);
        bool getEffectStatus(int effect);

        void setAllTrue();
        void addAllOffense();

        int getActiveOffensePassivesCount();
        int getActiveOffensePassive(int index);
        std::string getActiveOffensePassiveName(int index);
        void addActiveOffensePassive(int passive);
        void removeActiveOffensePassive(int passive);
        void clearOffensePassives();

        int getActiveDebuffCount();
        int getActiveDebuff(int index);
        std::string getActiveDebuffName(int index);
        void addActiveDebuff(int debuff);
        void removeActiveDebuff(int debuff);
        void clearDebuffs();

        std::string getOffensePassiveMessage(int index);
        std::string getDebuffMessage(int index);

        static const int STUN = 1, POISON = 2, DIZZY = 3;
};