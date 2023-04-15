#include <string>
#include "Account.h"
#include "TempEntity.h"

#pragma once


class Quests{
    private:
        Account account;
        static const int NUMBER_OF_QUESTS = 7;
        bool availableQuests[7];
    public:
        std::string getQuestDescription(std::string username, int quest);
        void getQuestLog(std::string username, int quest);
        void getAvailableQuests(std::string username, int location);
        void getAvailableQuests();
        void makeChoice();
        void doQuest(std::string username, int location, int quest);
        void quest1(std::string username, int step);
        void quest2(std::string username, int step);
        void quest3(std::string username, int step);
        void quest4(std::string username, int step);
        void quest5(std::string username, int step);
        void quest6(std::string username, int step);
        void quest7(std::string username, int step);
        void quest8(std::string username, int step);
};
