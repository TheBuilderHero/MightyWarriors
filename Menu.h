#include <string>

#pragma once

class Menu {
    public:
        void menu(std::string username);
        void adminMenu (std::string username);
        void changePass(std::string username);
};