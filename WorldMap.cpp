#include <iostream>
#include <string>

#include "Main.h"
#include "WorldMap.h"
#include "Battle.h"
#include "Menu.h"
#include "Map.h"
#include "DataGuard.h"

using namespace std;

//The map and movement are laid out thus:
// 1 - 2 -_3_
// 4 | 5 - 6
string WorldMap::getMapDescription(int location){
    switch(location){
        case 1:
            return "You are in the Glacius Desert. Frozen cacti are scattered everywhere.";
            break;
        case 2:
            return "You are at Lake Argentus. The water shimmers brightly.";
            break;
        case 3:
            return "You are in the city of Sanctus Ludovicus. Many eyes watch you from the shadows.";
            break;
        case 4:
            return "You are in the Ventosus Mountains. Strong winds nearly push you over.";
            break;
        case 5:
            return "You are in Arva Umbra. A few farmers tend crops and livestock.";
            break;
        case 6:
            return "You are in Silva Ignis. Orange and red trees surround you.";
            break;
        default:
            return "You are nowhere.";
            break;
    }

}
//direction is figured thus: 
//     1        N
//   4   2    W   E
//     3        S
bool WorldMap::canTravel(int location, int direction){
    switch(location){
        case 1:
            if(direction == 2 || direction == 3)
                return true;
            else
                return false;
            break;
        case 2:
            if(direction == 1)
                return false;
            else
                return true;
            break;
        case 3:
            if(direction == 4)
                return true;
            else
                return false;
            break;
        case 4:
            if(direction == 1)
                return true;
            else
                return false;
            break;
        case 5:
            if(direction == 1 || direction == 2)
                return true;
            else
                return false;
            break;
        case 6:
            if(direction == 4)
                return true;
            else
                return false;
            break;
        default:
            return false;
            break;
    }

}

string WorldMap::getTravelMessage(int location, int direction){
    switch(location){
        case 1:
            if(direction == 1){
                travelMessage1 = "There is only vast ocean to the North.";
                encounter = false;
                return travelMessage1;
            }else if(direction == 2){
                if(!encounter){
                    travelMessage1 = "You leave the bitter cold and advance on a huge lake.";
                }else{
                    travelMessage1 = "You leave the bitter cold, but are surprised by an enemy!";
                    travelMessage2 = "Victorious, you continue and advance on a huge lake.";
                }
                return travelMessage1;
            }else if(direction == 3){
                if(!encounter){
                    travelMessage1 = "The sands disappear behind as you enter an awesome mountain range.";
                }else{
                    travelMessage1 = "The sands disappear behind, but you are surprised by an enemy!";
                    travelMessage2 = "Victorious, you continue and enter an awesome mountain range.";
                }
                return travelMessage1;
            }else{
                travelMessage1 = "There is only vast ocean to the West.";
                encounter = false;
                return travelMessage1;
            }
            break;
        case 2:
            if(direction == 1){
                travelMessage1 = "There is only vast ocean to the North.";
                encounter = false;
                return travelMessage1;
            }else if(direction == 2){
                if(!encounter){
                    travelMessage1 = "The lake shrinks in the distance and you come upon a grand city.";
                }else{
                    travelMessage1 = "The lake shrinks in the distance, but you are surprised by an enemy!";
                    travelMessage2 = "Victorious, you continue and come upon a grand city.";
                }
                return travelMessage1;
            }else if(direction == 3){
                if(!encounter){
                    travelMessage1 = "You depart the lake and find yourself in a wide stretch of plains.";
                }else{
                    travelMessage1 = "You depart the lake, but you are surprised by an enemy!";
                    travelMessage2 = "Victorious, you continue and find yourself in a wide stretch of plains.";
                }
                return travelMessage1;
            }else{
                if(!encounter){
                    travelMessage1 = "You leave the lake behind and advance into a great tundra.";
                }else{
                    travelMessage1 = "You leave the lake behind, but you are surprised by an enemy!";
                    travelMessage2 = "Victorious, you continue and advance into a great tundras.";
                }
                return travelMessage1;
            }
            break;
        case 3:
            if(direction == 1){
                travelMessage1 = "There is only vast ocean to the North.";
                encounter = false;
                return travelMessage1;
            }else if(direction == 2){
                travelMessage1 = "There is only vast ocean to the East.";
                encounter = false;
                return travelMessage1;
            }else if(direction == 3){
                travelMessage1 = "The trees are so thick that you cannot find any route South.";
                encounter = false;
                return travelMessage1;
            }else{
                if(!encounter){
                    travelMessage1 = "The city shrinks in the distance and you come upon a glittering lake.";
                }else{
                    travelMessage1 = "The city shrinks in the distance, but you are surprised by an enemy!";
                    travelMessage2 = "Victorious, you continue and come upon a glittering lake.";
                }
                return travelMessage1;
            }
            break;
        case 4:
            if(direction == 1){
                if(!encounter){
                    travelMessage1 = "The mountains disappear behind as you enter a frozen desert.";
                }else{
                    travelMessage1 = "The mountains disappear behind, but you are surprised by an enemy!";
                    travelMessage2 = "Victorious, you continue and enter a frozen desert.";
                }
                return travelMessage1;
            }else if(direction == 2){
                travelMessage1 = "The mountains are so tall that you cannot find any path East.";
                encounter = false;
                return travelMessage1;
            }else if(direction == 3){
               travelMessage1 = "There is only vast ocean to the South.";
                encounter = false;
                return travelMessage1;
            }else{
                travelMessage1 = "There is only vast ocean to the West.";
                encounter = false;
                return travelMessage1;
            }
            break;
        case 5:
            if(direction == 1){
                if(!encounter){
                    travelMessage1 = "You depart the plains and find yourself at a shining lake.";
                }else{
                    travelMessage1 = "You depart the plains, but you are surprised by an enemy!";
                    travelMessage2 = "Victorious, you continue and find yourself at a shining lake.";
                }
                return travelMessage1;
            }else if(direction == 2){
                if(!encounter){
                    travelMessage1 = "The plains fade behind and before you appears an orange forest.";
                }else{
                    travelMessage1 = "The plains fade behind, but you are surprised by an enemy!";
                    travelMessage2 = "Victorious, you continue and before you appears an orange forest.";
                }
                return travelMessage1;
            }else if(direction == 3){
                travelMessage1 = "There is only vast ocean to the South.";
                encounter = false;
                return travelMessage1;
            }else{
                travelMessage1 = "Mountains which seem to touch the sky deter your passage West.";
                encounter = false;
                return travelMessage1;
            }
            break;
        case 6:
            if(direction == 1){
                travelMessage1 = "The trees are so thick that you cannot find any route North.";
                encounter = false;
                return travelMessage1;
            }else if(direction == 2){
                travelMessage1 = "There is only vast ocean to the East.";
                encounter = false;
                return travelMessage1;
            }else if(direction == 3){
                travelMessage1 = "There is only vast ocean to the South.";
                encounter = false;
                return travelMessage1;
            }else{
                if(!encounter){
                    travelMessage1 = "The forest fades behind and before you appear grassy plains.";
                }else{
                    travelMessage1 = "The forest fades behind, but you are surprised by an enemy!";
                    travelMessage2 = "Victorious, you continue and before you appear grassy plains.";
                }
                return travelMessage1;
            }
            break;
        default:
            return "You were nowhere, did you find your way out?";
            break;
    }
}

void WorldMap::travel(int direction, bool &failedTravel){
    
    /* //Old movement code
    if(canTravel(location, direction)){
        if(direction == 1){
            player.setLocation(location - 3);
        }else if(direction == 2){
            player.setLocation(location + 1);
        }else if(direction == 3){
            player.setLocation(location + 3);
        }else if(direction == 4){
            player.setLocation(location - 1);
        }
    }
    */
    bool ableToMove = true;
    if(direction == 1){
        ableToMove = map.canMoveFromCurrentLocation(direction);
    }else if(direction == 2){
        ableToMove = map.canMoveFromCurrentLocation(direction);
    }else if(direction == 3){
        ableToMove = map.canMoveFromCurrentLocation(direction);
    }else if(direction == 4){
        ableToMove = map.canMoveFromCurrentLocation(direction);
    }
    if (ableToMove){
        failedTravel = false;
        //cout << "move success!" << endl;
        //system("pause");
        guard.setPlayerMapLocation(map.getCurrentLocation()); //this is for saving location to the server when then program is shut down.
        //the following is code for the other travel system that probably needs some slight adjustments to the current system:
        encounter = false;
        srand(time(NULL)); 
        if(rand() % 14 == 0){ //1 in 15
            encounter = true;
        }
        int location = player.getLocation();
        //getTravelMessage(player.getLocation(), direction);
        if(encounter){
            menu.setStillSimpleTraveling(false);//no longer simple traveling (The cmd will have to re-output the travel menu.)
            menu.clearDisplayRow(2);
            menu.display(16, 2, "ENCOUNTER!");
            menu.waitForEnter(menu.getEnterKeyState());
            Battle battle;
            battle.setPlayer(player);
            battle.questBattle(player.getUsername(), 100, 10);
            setPlayer(battle.getPlayer());
            if(!player.getBattleResult()){
                menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
                system("cls");
                menu.display(16, 2, "Having been defeated, you return crying to whence you came.");
                menu.waitForEnter(menu.getEnterKeyState());
                //cout << "still Traveling? " << menu.getStillSimpleTraveling();
                //menu.waitForEnter(menu.getEnterKeyState());
                return;
            }else{
                //cout << "still Traveling? " << menu.getStillSimpleTraveling();
                menu.display(16, 2, "You may resume travelling now.");
                menu.waitForEnter(menu.getEnterKeyState());
                player.setBattleResult(false);
            }        
        } else {
            //menu.clearDisplayRow(2);
            menu.display(16, 4, "You moved hooray!");
        }
    } else {
        failedTravel = true;
        string messageFailure = "Oops! You can't go there!";
        int messageFailureLength = messageFailure.length();
        menu.displayMessageWithPause(0, 0, messageFailure);
    }
}
void WorldMap::travelLandmark(int direction, bool &failedTravel){
    bool ableToMove = true;
    if(direction == 1){
        ableToMove = map.canMoveFromCurrentLocationCity(direction);
    }else if(direction == 2){
        ableToMove = map.canMoveFromCurrentLocationCity(direction);
    }else if(direction == 3){
        ableToMove = map.canMoveFromCurrentLocationCity(direction);
    }else if(direction == 4){
        ableToMove = map.canMoveFromCurrentLocationCity(direction);
    }
    if (ableToMove){
        failedTravel = false;
        //guard.setPlayerMapLocation(map.getCurrentLocation()); //This might need an addition for city location information

        //the following is code for the other travel system that probably needs some slight adjustments to the current system:
        int location = player.getLocation();
        getTravelMessage(player.getLocation(), direction);
        menu.clearDisplayRow(2);
        menu.display(16, 2, travelMessage1);
    } else {
        failedTravel = true;
        string messageFailure = "failed move   ";
        int messageFailureLength = messageFailure.length();
        menu.displayMessageWithPause(0, 0, messageFailure);
    }
}
/*
void locationsRecord(int locationCount, int y, int x) {
    map.setPossibleTravelLocations(locationCount, y, x);
}

int getLocationX(int num) {
    return map.getPossibleTravelLocationsX(num);
}

int getLocationY(int num) {
    return map.getPossibleTravelLocationsY(num);
}
*/
/*void WorldMap::travelEncounter(string username){
    srand(time(NULL)); 
    if(rand() % 3 == 0){
        cout << "\nAn enemy surprises you!\n";
        Battle battle;
        battle.questBattle(username, 100, 10);
    }
}*/