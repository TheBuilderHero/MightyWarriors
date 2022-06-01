#include <iostream>
#include <string>

#include "Quests.h"
#include "Battle.h"
#include "Account.h"
#include "Menu.h"
using namespace std;

void Quests::getQuestDescription(string username, int quest){
    Menu menu;
    int quest1Step = account.getQuest1Progress(username);
    switch(quest){
        case 1:
            switch(quest1Step){
                case 1:
                    cout << "The name of your first target is scrawled on the parchemnt... Morg the Goblin.";
                    cout << "\nHe resides in the Glacius Desert.";
                    menu.waitForEnter(menu.getEnterKeyState());
                    system("cls");
                    break;
                case 2:
                    cout << "The name of your second target is scrawled on the parchemnt... Klade the Orc.";
                    cout << "\nHe resides near Lake Argentus.";
                    menu.waitForEnter(menu.getEnterKeyState());
                    system("cls");
                    break;
                case 3:
                    cout << "The name of your third target is scrawled on the parchemnt... The Black Night.";
                    cout << "\nHe resides in Arva Umbra.";
                    menu.waitForEnter(menu.getEnterKeyState());
                    system("cls");
                    break;
                case 4:
                    cout << "The name of your fourth target is scrawled on the parchemnt... The Blue Wizard.";
                    cout << "\nHe resides in Silva Ignis.";
                    menu.waitForEnter(menu.getEnterKeyState());
                    system("cls");
                    break;
                case 5:
                    cout << "The name of your fifth target is scrawled on the parchemnt... The Monstrous Behemoth.";
                    cout << "\nHe resides in the Ventosus Mountains.";
                    menu.waitForEnter(menu.getEnterKeyState());
                    system("cls");
                    break;
                case 6:
                    cout << "The name of your sixth target is scrawled on the parchemnt... The Awful Necromancer.";
                    cout << "\nHe resides in the Glacius Desert.";
                    menu.waitForEnter(menu.getEnterKeyState());
                    system("cls");
                    break;
                case 7:
                    cout << "The name of your final target is scrawled on the parchemnt...";
                    menu.waitForEnter(menu.getEnterKeyState());
                    cout << "The Dragon!!!";
                    menu.waitForEnter(menu.getEnterKeyState());
                    cout << "\nHe resides at Lake Argentus.";
                    menu.waitForEnter(menu.getEnterKeyState());
                    system("cls");
                    break;
                case 8:
                    cout << "All the monsters have been slain! Huzzah!\nThis Quest is complete.";
                    menu.waitForEnter(menu.getEnterKeyState());
                    system("cls");
                    break;
                default:
                    cout << "There is a problem with your Quest 1 data...";
                    menu.waitForEnter(menu.getEnterKeyState());
                    system("cls");
                    break;
            }
            break;
        default:
            cout << "There was a problem loading any quest data...";
            menu.waitForEnter(menu.getEnterKeyState());
            system("cls");
            break;
    }
}

void Quests::getQuestLog(string username, int quest){
    Menu menu;
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
    menu.waitForEnter(menu.getEnterKeyState());
    system("cls");
}

void Quests::getAvailableQuests(string username, int location){
    //Account account; //multiple definitions causing issues
    Menu menu;
    int quest1Step = account.getQuest1Progress(username);
    bool noQuests = true;

    cout << endl;

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
                menu.waitForEnter(menu.getEnterKeyState());
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

    cout << endl;
    menu.waitForEnter(menu.getEnterKeyState());
    system("cls");
}

void Quests::doQuest(string username, int location, int quest){
    Menu menu;
    int quest1Step = account.getQuest1Progress(username);
    bool noQuests = true;

    if(quest == 1){
        switch(location){
            case 1:
                if(quest1Step == 0 || quest1Step == 1 || quest1Step == 6){
                    quest1(username, quest1Step);
                    noQuests = false;
                }
                break;
            case 2:
                if(quest1Step == 2 || quest1Step == 7){
                    quest1(username, quest1Step);
                    noQuests = false;
                }
                break;
            case 3:
                break;
            case 4:
                if(quest1Step == 5){
                    quest1(username, quest1Step);
                    noQuests = false;
                }
                break;
            case 5:
                if(quest1Step == 3){
                    quest1(username, quest1Step);
                    noQuests = false;
                }
                break;
            case 6:
                if(quest1Step == 4){
                    quest1(username, quest1Step);
                    noQuests = false;
                }
                break;
            default:
                cout << "It looks like you are nowhere...";
                break;
        }
    }

    if(noQuests){
        cout << "There are no Quests to do here.";
        menu.waitForEnter(menu.getEnterKeyState());
        system("cls");
    }
}

void Quests::quest1(string username, int step){
    Menu menu;
    Battle battle;
    TempEntity player;
    switch(step){
        case 0:
            cout << "You lumber across the frozen sands, not knowing which way to turn.\n (press Enter)";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nThe air somehow gets colder, and a shadow darkens the ground. You feel its presence engulf you.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nThe shade concentrates into a single form. It seems to stand in front of you.";
            cout << "\nFloating in the air--No, in its outstretched hand, is some old parchment.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nThe shade's voice is a windy howl. 'A page ... of death. All those listed here ... must be slain.'\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nYou take the parchment, and a name etches itself into existence. 'The Void Cat'...\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nAs you look up, dread fills every corner of your being. The Void Cat is stepping towards you!\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nThe shadow cackles horribly, and slowly fades from your senses. But The Void Cat approaches...\n";
            menu.waitForEnter(menu.getEnterKeyState());
            
            battle.questBattle(username, 1, step);

            player.setHealth(battle.getPlayerHealth());

            cout << "Player ended Battle with " << player.getHealth() << " health!\n";
            menu.waitForEnter(menu.getEnterKeyState());
            //If the battle was won, we should run this code:
            if(player.getHealth() > 0){
                cout << "You are astonished at how incredibly weak the Void Cat turned out to be!";
                cout << "\nMight as well have been fighting a sand castle!\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou got 10000000 experience!\n";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou check the parchment again. The Void Cat's name is already fading.";
                cout << "\nA new name writes itself: Morg the Goblin. Somehow you know he is in the Glacius Desert.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                system("cls");
                account.setQuest1Progress(username, 1);
            }
            break;
        case 1:
            cout << "You eventually come upon a hut made of sticks and mud. You bang on the door.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nA small green creature pokes his nose out. You cry out, \"I have come to slay you!\"\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nThe goblin blinks at you. \"Morg no want fighting. Stranger want tea?\"\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nYou pause. \"...No way! You gotta die, son!\"\n";
            menu.waitForEnter(menu.getEnterKeyState());
            battle.questBattle(username, 1, step);

            player.setHealth(battle.getPlayerHealth());

            if(player.getHealth() > 0){
                cout << "As the goblin falls lifeless to the ground, you check your parchment again.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nA new name writes itself: Klade the Orc. Somehow you know he is near Lake Argentus.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou got 10000000 experience!\n";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                account.setQuest1Progress(username, 2);
            }
            break;
        case 2:
            cout << "You circle the lake for hours, with no sign of the Orc. Finally, you sit beneath a tree to rest.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nBefore too long, a tall green man walks up to you. His footsteps make no sound.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\n\"I know you hunt me. Ready yourself.\"\n";
            menu.waitForEnter(menu.getEnterKeyState());
            battle.questBattle(username, 1, step);

            player.setHealth(battle.getPlayerHealth());

            if(player.getHealth() > 0){
                cout << "The Orc collapses to the ground, eyes closed. He fought with honor.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nA new name writes itself: The Black Night. Somehow you know he is in Arva Umbra.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou got 10000000 experience!\n";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                account.setQuest1Progress(username, 3);
            }
            break;
        case 3:
            cout << "You gaze around the fields. The only signs of life are a few livestock.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nAfter a while, you spot a black figure on the horizon. It approaches even from some distance.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nSeveral minutes later, the figure hardly seems any closer.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nYou eventually sit down after realizing how long you'll be waiting.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nYou yawn. You can just make out the horse and the rider.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nThis is taking forever...\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nYou can barely keep your eyes open at this point.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nYou can't stand it any longer. You fall asleep.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nzzzzzzzzzzzzzzzzzzzzzzzzzzz\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nzzzzzzzzzzzzzzzzzzzzzzzzzzz\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nSomeone kicks you in the head! It's the Black Night! You scramble for your weapon!\n";
            menu.waitForEnter(menu.getEnterKeyState());
            battle.questBattle(username, 1, step);

            player.setHealth(battle.getPlayerHealth());

            if(player.getHealth() > 0){
                cout << "The Black Night shall ride no more. You read the enchanted parchment once again.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nA new name writes itself: The Blue Wizard. Somehow you know he is in Silva Ignis.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou got 10000000 experience!\n";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                account.setQuest1Progress(username, 4);
            }
            break;
        case 4:
            cout << "You wander through the trees, marvelling at their strange color.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nA blast of fire just barely misses your shoulder. You wheel around, drawing your weapon!\n";
            menu.waitForEnter(menu.getEnterKeyState());
            battle.questBattle(username, 1, step);

            player.setHealth(battle.getPlayerHealth());

            if(player.getHealth() > 0){
                cout << "The wizard collapses, but no body hits the ground. His robes simply crumple in the grass, \nwith his pointy hat perched neatly on top.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nA new name writes itself: The Monstrous Behemoth. Somehow you know he is in the Ventosus Mountains.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou got 10000000 experience!";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                account.setQuest1Progress(username, 5);
            }
            break;
        case 5:
            cout << "The mountains loom ominously over everything. \nYou dread the moment when the Monstrous Behemoth will finally appear.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nRight on time, a huge, hulking shape lumbers over the mountainside.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nSpotting you, it roars furiously, then leaps with incredible might!\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nIt clears an entire mountain in one great bound, then leaps again!\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nThis time, he lands in front of you. The menacing figure makes you feel very small.\n";
            cout << "\nIn your mind, you are about to be fighting the mountain itself...";
            menu.waitForEnter(menu.getEnterKeyState());
            battle.questBattle(username, 1, step);

            player.setHealth(battle.getPlayerHealth());

            if(player.getHealth() > 0){
                cout << "Incredibly, the titanic being crashes into the snow. Hands shaking, you check the parchment.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nA new name has been written: The Awful Necromancer. You know he is in the Glacius Desert, and you are terrified.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou got 20000000 experience!\n";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                account.setQuest1Progress(username, 6);
            }
            break;
        case 6:
            cout << "It is cold. Bitterly cold. Your toes feel as though they are frozen together.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nIt is almost noon, but it is getting colder.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nIt is getting darker.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nThe cold is so intense, and the clouds are like charcoal.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nDead silence falls over the whole landscape. \nIt is now pitch black, and the cold is more than anything you have ever imagined.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nA blue light begins glowing, and a figure appears in its midst.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nYou can feel it is the very embodiment of death itself.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            battle.questBattle(username, 1, step);

            player.setHealth(battle.getPlayerHealth());

            if(player.getHealth() > 0){
                cout << "The Necromancer screams, beams of light splitting his body apart, and he explodes into dust.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nThe clouds clear, the sun begins warming everything, \nbut even so you collapse to your knees and put your head in your hands.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nTears stream down your face. Your mind feels like wet dough,";
                cout << "\noozing out of your head as thoughts and memories all melt into a sick mess.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYour hands shake and you look at the parchment once more.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nA name is written. You know it is the last.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nThe Dragon.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou know he is at Lake Argentus.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou got 30000000 experience!\n";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                account.setQuest1Progress(username, 7);
            }
            break;
        case 7:
            cout << "Meh, guess like a dragon showed up or some junk\n";
            menu.waitForEnter(menu.getEnterKeyState());
            battle.questBattle(username, 1, step);

            player.setHealth(battle.getPlayerHealth());

            if(player.getHealth() > 0){
                cout << "Huzzah, the dragon is like dead or whatever\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nWith the last enemy defeated, the enchanted parchment crumbles into dust.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "You finished the Quest! You got 50000000 experience!\n";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "Huzzah!\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "Huzzah!\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "Huzzah!\n";
                menu.waitForEnter(menu.getEnterKeyState());
                account.setQuest1Progress(username, 8);
            }
            break;
        default:
            cout << "Error loading Quest...";
            menu.waitForEnter(menu.getEnterKeyState());
            break;
    }
}