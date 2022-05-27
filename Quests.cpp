#include <iostream>
#include <string>

#include "Quests.h"
#include "Battle.h"
#include "Account.h"
using namespace std;

Account account;

void getQuestDescription(string username, int quest){
    int quest1Step = account.getQuest1Progress(username);
    switch(quest){
        case 1:
            switch(quest1Step){
                case 1:
                    cout << "The name of your first target is scrawled on the parchemnt... Morg the Goblin.";
                    cout << "\nHe resides in the Glacius Desert.";
                    system("pause");
                    system("cls");
                    break;
                case 2:
                    cout << "The name of your second target is scrawled on the parchemnt... Klade the Orc.";
                    cout << "\nHe resides near Lake Argentus.";
                    system("pause");
                    system("cls");
                    break;
                case 3:
                    cout << "The name of your third target is scrawled on the parchemnt... The Black Night.";
                    cout << "\nHe resides in Arva Umbra.";
                    system("pause");
                    system("cls");
                    break;
                case 4:
                    cout << "The name of your fourth target is scrawled on the parchemnt... The Blue Wizard.";
                    cout << "\nHe resides in Silva Ignis.";
                    system("pause");
                    system("cls");
                    break;
                case 5:
                    cout << "The name of your fifth target is scrawled on the parchemnt... The Monstrous Behemoth.";
                    cout << "\nHe resides in the Ventosus Mountains.";
                    system("pause");
                    system("cls");
                    break;
                case 6:
                    cout << "The name of your sixth target is scrawled on the parchemnt... The Awful Necromancer.";
                    cout << "\nHe resides in the Glacius Desert.";
                    system("pause");
                    system("cls");
                    break;
                case 7:
                    cout << "The name of your final target is scrawled on the parchemnt...";
                    system("pause");
                    cout << "The Dragon!!!";
                    system("pause");
                    cout << "\nHe resides at Lake Argentus.";
                    system("pause");
                    system("cls");
                    break;
                case 8:
                    cout << "All the monsters have been slain! Huzzah!\nThis Quest is complete.";
                    system("pause");
                    system("cls");
                    break;
                default:
                    cout << "There is a problem with your Quest 1 data...";
                    system("pause");
                    system("cls");
                    break;
            }
            break;
        default:
            cout << "There was a problem loading any quest data...";
            system("pause");
            system("cls");
            break;
    }
}

void getQuestLog(string username, int quest){
    int quest1Step = account.getQuest1Progress(username);
    string output = "";
    switch(quest){
        case 1:
            switch(quest1Step){
                case 8:
                    output = "\nUpon defeating The Dragon in Lake Argentus, the enchanted parchment slowly crumbled into dust.\n This Quest is complete.";
                case 7:
                    output = "\nYou defeated the Awful Necromancer in the Glacius Desert." + output;
                case 6:
                    output = "\nYou defeated the Monstrous Behemoth in the Ventosus Mountains." + output;
                case 5:
                    output = "\nYou defeated the Blue Wizard in the Silva Ignis." + output;
                case 4:
                    output = "\nYou defeated the Black Night in Arva Umbra." + output;
                case 3:
                    output = "\nYou defeated Klade the Orc near Lake Argentus." + output;
                case 2:
                    output = "\nYou defeated Morg the Goblin in the Glacius Desert." + output;
                case 1:
                    output = "A shadow appeared to you in the cold of the Glacius Desert.\nHe handed you an enchanted piece of parchment with a list of monsters to destroy.\nYou were then attacked by the Void Cat, which you defeated easily." + output;
                    break;
                default:
                    output = "There was a problem loading your Quest 1 log...";
                    break;
            }
            break;
        default:
            output = "There was a problem loading any Quest logs...";
            break;
    }

    cout << output;
    system("pause");
    system("cls");
}

void getAvailableQuests(string username, int location){
    Account account;
    int quest1Step = account.getQuest1Progress(username);
    bool noQuests = true;

    switch(location){
        case 1:
            if(quest1Step == 0){
                cout << "You can start Quest 1 here.";
                noQuests = false;
            }else if(quest1Step == 1){
                cout << "Here you can continue Quest 1 and fight Morg the Goblin.";
                noQuests = false;
            }else if(quest1Step == 6){
                cout << "Here you can continue Quest 1 and fight the Awful Necromancer.";
                noQuests = false;
            }
            break;                
        case 2:
            if(quest1Step == 2){
                cout << "Here you can continue Quest 1 and fight Klade the Orc.";
                noQuests = false;
            }else if(quest1Step == 7){
                cout << "Here you can continue Quest 1 and fight...";
                system("pause");
                cout << "The Dragon!!!";
                noQuests = false;
            }
            break; 
        case 3:
            break;   
        case 4:
            if(quest1Step == 5){
                cout << "Here you can continue Quest 1 and fight the Monstrous Behemoth.";
                noQuests = false;
            }
            break;   
        case 5:
            if(quest1Step == 3){
                cout << "Here you can continue Quest 1 and fight the Black Night.";
                noQuests = false;
            }
            break;  
        case 6:
            if(quest1Step == 4){
                cout << "Here you can continue Quest 1 and fight the Blue Wizard.";
                noQuests = false;
            }
            break;  
        default:
            cout << "It looks like you are nowhere...";
            break;
    }

    if(noQuests){
        cout << "There are no Quests to do here.";
    }

    system("pause");
    system("cls");
}

void doQuest(string username, int location, int quest){
    int quest1Step = account.getQuest1Progress(username);
    bool noQuests = true;

    switch(location){
        case 1:
            //if(quest)
    }
}