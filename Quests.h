#include <string>
#include "Account.h"
#include "TempEntity.h"

#pragma once

using namespace std;

class Quests{
    private:
        Account account;
        TempEntity player;
    public:
        void getQuestDescription(string username, int quest);
        void getQuestLog(string username, int quest);
        void getAvailableQuests(string username, int location);
        void getAvailableQuests();
        void makeChoice();
        void doQuest(string username, int location, int quest);
        void quest1(string username, int step);

        TempEntity getPlayer(){ return player ;}
        void setPlayer(TempEntity playerE){ player = playerE; }
};
