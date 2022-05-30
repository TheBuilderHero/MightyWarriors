#include <iostream>
#include <string>

#include "Quests.h"
#include "Battle.h"
#include "Account.h"
using namespace std;

void Quests::getQuestDescription(string username, int quest){
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

void Quests::getQuestLog(string username, int quest){
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

void Quests::getAvailableQuests(string username, int location){
    //Account account; //multiple definitions causing issues
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

void Quests::doQuest(string username, int location, int quest){
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
        system("pause");
        system("cls");
    }
}

void Quests::quest1(string username, int step){
    Battle battle;
    TempEntity player;
    switch(step){
        case 0:
            cout << "You lumber across the frozen sands, not knowing which way to turn.\n";
            system("pause");
            cout << "\nThe air somehow gets colder, and a shadow darkens the ground. You feel its presence engulf you.\n";
            system("pause");
            cout << "\nThe shade concentrates into a single form. It seems to stand in front of you.";
            cout << "\nFloating in the air--No, in its outstretched hand, is some old parchment.\n";
            system("pause");
            cout << "\nThe shade's voice is a windy howl. 'A page ... of death. All those listed here ... must be slain.'\n";
            system("pause");
            cout << "\nYou take the parchment, and a name etches itself into existence. 'The Void Cat'...\n";
            system("pause");
            cout << "\nAs you look up, dread fills every corner of your being. The Void Cat is stepping towards you!\n";
            system("pause");
            cout << "\nThe shadow cackles horribly, and slowly fades from your senses. But The Void Cat approaches...\n";
            system("pause");

            //I think this should be changed to a special battle function made for Quests
            //in which we can specify monsters to be fought and return the result of the battle
            battle.questBattle(username, 1, step, player);
            //battle.startBattle(username);

            //If the battle was won, we should run this code:
            if(player.getHealth() > 0){
                cout << "You are astonished at how incredibly weak the Void Cat turned out to be!";
                cout << "\nMight as well have been fighting a sand castle!\n";
                system("pause");
                cout << "You got 10000000 experience!\n";
                //Code to add experience
                system("pause");
                cout << "\nYou check the parchment again. The Void Cat's name is already fading.";
                cout << "\nA new name writes itself: Morg the Goblin. Somehow you know he is in the Glacius Desert.\n";
                account.setQuest1Progress(username, 1);
            }
            break;
        case 1:
            cout << "You eventually come upon a hut made of sticks and mud. You bang on the door.";
            system("pause");
            cout << "\nA small green creature pokes his nose out. You cry out, 'I have come to slay you!'";
            system("pause");
            cout << "\nThe goblin blinks at you. 'Morg no want fighting. Stranger want tea?'";
            system("pause");
            cout << "\nYou pause. '...No way! You gotta die, son!'";
            system("pause");
            battle.questBattle(username, 1, step, player);

            if(player.getHealth() > 0){
                cout << "As the goblin falls lifeless to the ground, you check your parchment again.";
                system("pause");
                cout << "\nA new name writes itself: Klade the Orc. Somehow you know he is near Lake Argentus.";
                system("pause");
                cout << "You got 10000000 experience!";
                //Code to add experience
                system("pause");
                account.setQuest1Progress(username, 2);
            }
            break;
        case 2:
            cout << "You circle the lake for hours, with no sign of the Orc. Finally, you sit beneath a tree to rest.";
            system("pause");
            cout << "\nBefore too long, a tall green man walks up to you. His footsteps make no sound.";
            system("pause");
            cout << "\n'I know you hunt me. Ready yourself.'";
            system("pause");
            battle.questBattle(username, 1, step, player);

            if(player.getHealth() > 0){
                cout << "The Orc collapses to the ground, eyes closed. He fought with honor.";
                system("pause");
                cout << "\nA new name writes itself: The Black Night. Somehow you know he is in Arva Umbra.";
                system("pause");
                cout << "You got 10000000 experience!";
                //Code to add experience
                system("pause");
                account.setQuest1Progress(username, 3);
            }
            break;
        case 3:
            cout << "You gaze around the fields. The only signs of life are a few livestock.";
            system("pause");
            cout << "\nAfter a while, you spot a black figure on the horizon. It approaches even from some distance.";
            system("pause");
            cout << "\nSeveral minutes later, the figure hardly seems any closer.";
            system("pause");
            cout << "\nYou eventually sit down after realizing how long you'll be waiting.";
            system("pause");
            cout << "\nYou yawn. You can just make out the horse and the rider.";
            system("pause");
            cout << "\nThis is taking forever...";
            system("pause");
            cout << "\nYou can barely keep your eyes open at this point.";
            system("pause");
            cout << "\nYou can't stand it any longer. You fall asleep.";
            system("pause");
            cout << "\nzzzzzzzzzzzzzzzzzzzzzzzzzzz";
            system("pause");
            cout << "\nzzzzzzzzzzzzzzzzzzzzzzzzzzz";
            system("pause");
            cout << "\nSomeone kicks you in the head! It's the Black Night! You scramble for your weapon!";
            system("pause");
            battle.questBattle(username, 1, step, player);

            if(player.getHealth() > 0){
                cout << "The Black Night shall ride no more. You read the enchanted parchment once again.";
                system("pause");
                cout << "\nA new name writes itself: The Blue Wizard. Somehow you know he is in Silva Ignis.";
                system("pause");
                cout << "You got 10000000 experience!";
                //Code to add experience
                system("pause");
                account.setQuest1Progress(username, 4);
            }
            break;
        case 4:
            cout << "You wander through the trees, marvelling at their strange color.";
            system("pause");
            cout << "\nA blast of fire just barely misses your shoulder. You wheel around, drawing your weapon!";
            system("pause");
            battle.questBattle(username, 1, step, player);

            if(player.getHealth() > 0){
                cout << "The wizard collapses, but no body hits the ground. His robes simply crumple in the grass, with his pointy hat perched neatly on top.";
                system("pause");
                cout << "\nA new name writes itself: The Monstrous Behemoth. Somehow you know he is in the Ventosus Mountains.";
                system("pause");
                cout << "You got 10000000 experience!";
                //Code to add experience
                system("pause");
                account.setQuest1Progress(username, 5);
            }
            break;
        case 5:
            cout << "The mountains loom ominously over everything. You dread the moment when the Monstrous Behemoth will finally appear.";
            system("pause");
            cout << "\nRight on time, a huge, hulking shape lumbers over the mountainside.";
            system("pause");
            cout << "\nSpotting you, it roars furiously, then leaps with incredible might!";
            system("pause");
            cout << "\nIt clears an entire mountain in one great bound, then leaps again!";
            system("pause");
            cout << "\nThis time, he lands in front of you. The menacing figure makes you feel very small.";
            cout << "\nIn your mind, you are about to be fighting the mountain itself...";
            system("pause");
            battle.questBattle(username, 1, step, player);

            if(player.getHealth() > 0){
                cout << "Incredibly, the titanic being crashes into the snow. Hands shaking, you check the parchment.";
                system("pause");
                cout << "\nA new name has been written: The Awful Necromancer. You know he is in the Glacius Desert, and you are terrified.";
                system("pause");
                cout << "You got 20000000 experience!";
                //Code to add experience
                system("pause");
                account.setQuest1Progress(username, 6);
            }
            break;
        case 6:
            cout << "It is cold. Bitterly cold. Your toes feel as though they are frozen together.";
            system("pause");
            cout << "\nIt is almost noon, but it is getting colder.";
            system("pause");
            cout << "\nIt is getting darker.";
            system("pause");
            cout << "\nThe cold is so intense, and the clouds are like charcoal.";
            system("pause");
            cout << "\nDead silence falls over the whole landscape. It is now pitch black, and the cold is more than anything you have ever imagined.";
            system("pause");
            cout << "\nA blue light begins glowing, and a figure appears in its midst.";
            system("pause");
            cout << "You can feel it is the very embodiment of death itself.";
            system("pause");
            battle.questBattle(username, 1, step, player);

            if(player.getHealth() > 0){
                cout << "The Necromancer screams, beams of light splitting his body apart, and he explodes into dust.";
                system("pause");
                cout << "The clouds clear, the sun begins warming everything, but even so you collapse to your knees and put your head in your hands.";
                system("pause");
                cout << "Tears stream down your face. Your mind feels like wet dough,";
                cout << "\noozing out of your head as thoughts and memories all melt into a sick mess.";
                system("pause");
                cout << "Your hands shake and you look at the parchment once more.";
                system("pause");
                cout << "\nA name is written. You know it is the last.";
                system("pause");
                cout << "\nThe Dragon.";
                system("pause");
                cout << "\nYou know he is at Lake Argentus.";
                system("pause");
                cout << "You got 30000000 experience!";
                //Code to add experience
                system("pause");
                account.setQuest1Progress(username, 7);
            }
            break;
        case 7:
            cout << "Meh, guess like a dragon showed up or some junk";
            system("pause");
            battle.questBattle(username, 1, step, player);

            if(player.getHealth() > 0){
                cout << "Huzzah, the dragon is like dead or whatever";
                system("pause");
                cout << "\nWith the last enemy defeated, the enchanted parchment crumbles into dust.";
                system("pause");
                cout << "You finished the Quest! You got 50000000 experience!";
                //Code to add experience
                system("pause");
                cout << "Huzzah!";
                system("pause");
                cout << "Huzzah!";
                system("pause");
                cout << "Huzzah!";
                system("pause");
                account.setQuest1Progress(username, 8);
            }
            break;
        default:
            cout << "Error loading Quest...";
            break;
    }
}