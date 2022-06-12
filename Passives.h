#pragma once

class Passives{
    private:
        
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

};