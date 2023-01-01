#include <string>
#include "Account.h"
#include "TempEntity.h"

#pragma once

using namespace std;

class Quests{
    private:
        Account account;
        int NUMBER_OF_QUESTS = 7;
        bool availableQuests[7];
    public:
        string getQuestDescription(string username, int quest);
        void getQuestLog(string username, int quest);
        void getAvailableQuests(string username, int location);
        void getAvailableQuests();
        void makeChoice();
        void doQuest(string username, int location, int quest);
        void quest1(string username, int step);
        void quest2(string username, int step);
        void quest3(string username, int step);
        void quest4(string username, int step);
        void quest5(string username, int step);
        void quest6(string username, int step);
        void quest7(string username, int step);
};
