#include <string>

#pragma once

class Menu {
    public:
        const int gameVersion     = 1;
        const int gameMajorBuild  = 0;
        const int gameMinorBuild  = 0;
        const int gamePatch       = 0;
        void getGameVersion();
        void menu(std::string username);
        void adminMenu (std::string username);
        void changePass(std::string username);
        char yesOrNo();
        int numberPressWait(int maxRange, bool hasZeroOption = false);
        void ClearConsoleInputBuffer();
        void display(int column, int row, std::string outputString, bool resetCursorPosition = true, bool addExtraRow = true);
        std::string numberFormatting(double decimalNumber, int numberOfDecimals);
};