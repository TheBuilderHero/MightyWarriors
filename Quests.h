#include <string>
#include "Account.h"
//#include "TempEntity.h"

#pragma once


class Quests{
    private:
        Account account;
        static const int NUMBER_OF_QUESTS = 7;
        bool availableQuests[7];
        int progress = 0;
    public:
        std::string getQuestDescription(std::string username, int quest);
        void getQuestLog(std::string username, int quest);
        void getAvailableQuests(std::string username, int location);
        void getAvailableQuests();
        void makeChoice();
        void doQuest(std::string username, int location, int quest);
        /* NOTE THIS WILL MAKE THE QUEST PROGRESS RESET EVERYTIME*/
        int getProgress() { return 0; } //change this later to the progress of the quest.
        void setProgress(int progress) { this->progress = progress; }


        /*
        void quest1(std::string username, int step);
        void quest2(std::string username, int step);
        void quest3(std::string username, int step);
        void quest4(std::string username, int step);
        void quest5(std::string username, int step);
        void quest6(std::string username, int step);
        void quest7(std::string username, int step);
        void quest8(std::string username, int step);*/
};
