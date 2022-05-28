#include <iostream>
#include <string>

using namespace std;
class TempEntity{
    private:
        string name;
        int health;
    public:
        string getName();
        void setName(string newName);
        int getHealth();
        void setHealth(int newHealth);
        void damage(int damage);
        void heal(int healing);
};
