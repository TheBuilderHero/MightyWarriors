#include <string>
#include "Account.h"
//#include "TempEntity.h"

#pragma once


class Quests{
    private:
        Account account;
        static const int NUMBER_OF_QUESTS = 7; //remove
        bool availableQuests[7]; //remove
        int questID = 0;
        int progress = 0;
        std::string questName = "";
        std::string questDescription = "";
    public:
        Quests(int questID, int progress, std::string questName, std::string questDescription);
        std::string getQuestDescription();// { return questDescription; }; //maybe change this somehow later.
        std::string getQuestName() {return questName; }
        int getID() { return questID; }
        void getQuestLog(); //run when quest completes
        void getAvailableQuests(std::string username, int location); //remove?
        void getAvailableQuests();
        void makeChoice();
        void doQuest(std::string username, int location, int quest);
        /* NOTE THIS WILL MAKE THE QUEST PROGRESS RESET EVERYTIME*/
        int getProgress() { return 0; } //change this later to the progress of the quest.
        void setProgress(int progress) { this->progress = progress; }
};
