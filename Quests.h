#include <string>
#include "Account.h"
#include "TempEntity.h"

#pragma once

using namespace std;

class Quests{
    private:
        Account account;
        TempEntity player;
        int NUMBER_OF_QUESTS = 2;
        bool availableQuests[2] = {false, false};
    public:
        void getQuestDescription(string username, int quest);
        void getQuestLog(string username, int quest);
        void getAvailableQuests(string username, int location);
        void getAvailableQuests();
        void makeChoice();
        void doQuest(string username, int location, int quest);
        void quest1(string username, int step);
        void quest2(string username, int step);

        TempEntity getPlayer(){ return player ;}
        void setPlayer(TempEntity playerE){ player = playerE; }
};
