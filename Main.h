#pragma once

class Main {
    private:
        //Change the version number in the menu.h header file.
        //********************************************
        const int gameVersion     = 1;
        const int gameMajorBuild  = 0;
        const int gameMinorBuild  = 0;
        const int gamePatch       = 0;
        //********************************************
        
    public:
    void getGameVersion();
    void fullsc();
    void maxsc();
    void setupConsole();
    void attemptStartGame();
    void preLoadGameTest();
    void setTextSize(int size);
    void setTextSize(int scaleX, int scaleY);
};