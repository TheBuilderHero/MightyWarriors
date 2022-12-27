#pragma once
//#include "Main.h"
#include <queue>
#include <string>

class Interactions{
    private:
        std::queue<std::string> interactionLines;

    public:
        Interactions(int name/*std::vector<std::string> &test*/);
        Interactions();
        void interact(int location); //used for any interactions with anything in the same when just dialogue is invloved.
        void setLocationInteractionDialogue(std::string line);
        void pullInteractionsAndNPCs();
};