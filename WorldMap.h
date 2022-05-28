#include <iostream>
#include <string>

using namespace std;
class WorldMap{
    public:
        string getMapDescription(int location);
        bool canTravel(int location, int direction);
        string getTravelMessage(int location, int direction);
        int travel(int location, int direction);
};