#include <string>
#include "TempEntity.h"

#pragma once

class Menu {
    private: 
        TempEntity player;
        bool exitAdminMenu = false;
        bool stillTraveling = false;
        bool stillSimpleTraveling = false;// for the do while loop so we do not have to refresh the whole cmd
    public:
        const int gameVersion     = 1;
        const int gameMajorBuild  = 0;
        const int gameMinorBuild  = 0;
        const int gamePatch       = 0;
        void getGameVersion();
        void menu(std::string username);
        void travelMenu(std::string username);
        void displayStats();//This function uses a stored TempEntity to display player data
        void displayInventory();
        void accountInfo(std::string username);
        void adminMenu (std::string username);
        void changePass(std::string username);
        char yesOrNo();
        int numberPressWait(int maxRange, bool hasZeroOption = false);
        int arrowPressWait(bool hasZeroOption);
        void waitForEnter(int enterCurrentlyPressed);
        int getEnterKeyState();
        void ClearConsoleInputBuffer();
        void display(int column, int row, std::string outputString, bool resetCursorPosition = true, bool addExtraRow = true, int color = 15);
        void display(int column, int row, std::string outputString, int lengthOfString, bool resetCursorPosition = false, bool addExtraRow = false);
        void clearDisplayRow(int row);
        std::string numberFormatting(double decimalNumber, int numberOfDecimals);

        void setPlayer(TempEntity playerE);
        TempEntity getPlayer();

        void setStillSimpleTraveling(bool trueFalse) { stillSimpleTraveling = trueFalse; }
        bool getStillSimpleTraveling() { return stillSimpleTraveling; }
};