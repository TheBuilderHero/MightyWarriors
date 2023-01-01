#include <string>
#include "TempEntity.h"

#pragma once

class Menu {
    private: 
        bool exitAdminMenu = false;
        bool stillTraveling = false;
        bool stillSimpleTraveling = false;// for the do while loop so we do not have to refresh the whole cmd
        bool stillLandmarkSimpleTraveling = false;
        bool cityTraveling = false;
    public:
        const int gameVersion     = 1;
        const int gameMajorBuild  = 0;
        const int gameMinorBuild  = 0;
        const int gamePatch       = 0;
        void getGameVersion();
        void menu(std::string username);
        void travelMenu(std::string username);
        void cityTravelMenu(std::string username);
        void displayStats();//This function uses a stored TempEntity to display player data
        void displayInventory();
        void accountInfo(std::string username);
        void adminMenu (std::string username);
        void changePass(std::string username);
        char yesOrNo();
        int numberPressWait(int maxRange, bool hasZeroOption = false);
        int numberPressWaitSpecial(int maxRange, char key1, char key2 = 0, char key3 = 0, char key4 = 0, char key5 = 0, char key6 = 0, char key7 = 0, bool hasZeroOption = false);
        int arrowPressWait(bool hasZeroOption = false, bool hasUpOption = true, bool hasRightOption = true, bool hasDownOption = true, bool hasLeftOption = true, bool hasROption = false);//returns a value based on the key pressed starting at 1 - UP going around clockwise to 4 - Left
        void waitForEnter(int enterCurrentlyPressed);
        int getEnterKeyState();
        void ClearConsoleInputBuffer();
        void display(int column, int row, std::string outputString, bool resetCursorPosition = true, bool addExtraRow = true, int color = 15);
        void displayMessageWithPause(int column, int row, std::string outputString, bool resetCursorPosition = true, bool addExtraRow = true, int color = 15);
        void clearDisplayRow(int row, int startingColumn = 0);
        std::string numberFormatting(double decimalNumber, int numberOfDecimals);
        void options();
        
        void setStillSimpleTraveling(bool trueFalse) { stillSimpleTraveling = trueFalse; }
        bool getStillSimpleTraveling() { return stillSimpleTraveling; }
        void setStillLandmarkSimpleTraveling(bool trueFalse) { stillLandmarkSimpleTraveling = trueFalse; }
        bool getStillLandmarkSimpleTraveling() { return stillLandmarkSimpleTraveling; }
        void setCityTraveling(bool trueFalse) { cityTraveling = trueFalse; }
        bool getCityTraveling() { return cityTraveling; }
};