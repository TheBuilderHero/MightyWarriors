#pragma once

class Passives{
    private:
        //all passive booleans, determines active or inactive
        bool tough = false, stunAttack = false, ethereal = false, learning = false;
        //stat bonuses
        int bonusHealth = 0;
        float XPMultiplier = 0.0f;

        //negative effects
        bool stunned = false;
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

        void setAllTrue();
};