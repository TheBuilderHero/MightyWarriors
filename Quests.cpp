#include <iostream>
#include <string>

#include "GlobalVariables.h"
#include "Quests.h"
#include "Battle.h"
#include "Account.h"
#include "Menu.h"
using namespace std;

string Quests::getQuestDescription(string username, int quest){
    //Menu menu;
    switch(quest){
        case 1:
            switch(player.getQuest1Progress(1)){
                case 0:
                    return "";
                    break;
                case 1:
                    return "The name of your first target is scrawled on the parchemnt... Morg the Goblin.\nHe resides in the Glacius Desert.\n";
                    break;
                case 2:
                    return "The name of your second target is scrawled on the parchemnt... Klade the Orc.\nHe resides near Lake Argentus.\n";
                    break;
                case 3:
                    return "The name of your third target is scrawled on the parchemnt... The Black Night.\nHe resides in Arva Umbra.\n";
                    break;
                case 4:
                    return "The name of your fourth target is scrawled on the parchemnt... The Blue Wizard.\nHe resides in Silva Ignis.\n";
                    break;
                case 5:
                    return "The name of your fifth target is scrawled on the parchemnt... The Monstrous Behemoth.\nHe resides in the Ventosus Mountains.\n";
                    break;
                case 6:
                    return "The name of your sixth target is scrawled on the parchemnt... The Awful Necromancer.\nHe resides in the Glacius Desert.\n";
                    break;
                case 7:
                    return "The name of your final target is scrawled on the parchemnt...\nThe Dragon!!!\nHe resides at Lake Argentus.\n";
                    break;
                case 8:
                    return "All the monsters have been slain! Huzzah!\nThis Quest is complete.";
                    break;
                default:
                    return ("There is a problem with your Quest 1 data...\nError value: " + to_string(player.getQuest1Progress(1)));
                    break;
            }
            break;
        case 2:
            switch(player.getQuest1Progress(2)){
                case 0:
                    return "";
                    break;
                case 1:
                    return "The completely innocent Potato has been mashed, by YOU, scoundrel!";
                    break;
                default: 
                    return "There is a problem with your Quest 2 data...";
                    break;
            }
        case 3:
            switch(player.getQuest1Progress(3)){
                case 0:
                    return "";
                    break;
                case 1:
                    return "This will theoretically contain pertinent data in the future!";
                    break;
                default: 
                    return "There is a problem with your Quest 3 data...";
                    break;
            }
        case 4:
            switch(player.getQuest1Progress(4)){
                case 0:
                    return "";
                    break;
                case 1:
                    return "This will theoretically contain pertinent data in the future!";
                    break;
                default: 
                    return "There is a problem with your Quest 4 data...";
                    break;
            }
        case 5:
            switch(player.getQuest1Progress(5)){
                case 0:
                    return "";
                    break;
                case 1:
                    return "This will theoretically contain pertinent data in the future!";
                    break;
                default: 
                    return "There is a problem with your Quest 5 data...";
                    break;
            }
        case 6:
            switch(player.getQuest1Progress(6)){
                case 0:
                    return "";
                    break;
                case 1:
                    return "This will theoretically contain pertinent data in the future!";
                    break;
                default: 
                    return "There is a problem with your Quest 6 data...";
                    break;
            }
        case 7:
            switch(player.getQuest1Progress(7)){
                case 0:
                    return "";
                    break;
                case 1:
                    return "This will theoretically contain pertinent data in the future!";
                    break;
                default: 
                    return "There is a problem with your Quest 7 data...";
                    break;
            }
        default:
            return "There was a problem loading any quest data...";
            break;
    }
}

void Quests::getQuestLog(string username, int quest){
    //Menu menu;
    int quest1Step = player.getQuest1Progress(1);
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
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
}

void Quests::getAvailableQuests(string username, int location){
    //Account account; //multiple definitions causing issues
    //Menu menu;
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
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
}
void Quests::getAvailableQuests(){//TempEntity based quest call
    //Account account; //multiple definitions causing issues
    //Menu menu;
    int quest1Step = player.getQuest1Progress(1);
    bool noQuests = true;
    
    for(int i = 0; i < NUMBER_OF_QUESTS; i++){
        availableQuests[i] = false;
    }

    cout << endl;

    /* This needs to be refactored to work with X Y instead of location value
    switch(player.getLocation()){
        case 1:
            if(quest1Step == 0){
                cout << "You can start Quest 1 here.\n";
                availableQuests[0] = true;
                noQuests = false;
            }else if(quest1Step == 1){
                cout << "Here you can continue Quest 1 and fight Morg the Goblin.\n";
                availableQuests[0] = true;
                noQuests = false;
            }else if(quest1Step == 6){
                cout << "Here you can continue Quest 1 and fight the Awful Necromancer.\n";
                availableQuests[0] = true;
                noQuests = false;
            }
            break;                
        case 2:
            if(quest1Step == 2){
                cout << "Here you can continue Quest 1 and fight Klade the Orc.\n";
                availableQuests[0] = true;
                noQuests = false;
            }else if(quest1Step == 7){
                cout << "Here you can continue Quest 1 and fight...\n\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "The Dragon!!!\n";
                availableQuests[0] = true;
                noQuests = false;
            }
            if(player.getQuest1Progress(2) == 0){
                cout << "You can attempt Quest 2 here.\n";
                availableQuests[1] = true;
                noQuests = false;
            }
            if(player.getQuest1Progress(3) == 0){
                cout << "You can do Quest 3 here.\n";
                availableQuests[2] = true;
                noQuests = false;
            }
            if(player.getQuest1Progress(5) == 0){
                cout << "You can do Quest 5 here.\n";
                availableQuests[4] = true;
                noQuests = false;
            }
            if(player.getQuest1Progress(6) == 0){
                cout << "You can do Quest 6 here.\n";
                availableQuests[5] = true;
                noQuests = false;
            }
            break; 
        case 3:
            if(player.getQuest1Progress(4) == 0){
                cout << "You can do Quest 4 here.\n";
                availableQuests[3] = true;
                noQuests = false;
            }
            if(player.getQuest1Progress(7) == 0){
                cout << "You can do Quest 7 here.\n";
                availableQuests[6] = true;
                noQuests = false;
            }
            break;   
        case 4:
            if(quest1Step == 5){
                cout << "Here you can continue Quest 1 and fight the Monstrous Behemoth.\n";
                availableQuests[0] = true;
                noQuests = false;
            }
            break;   
        case 5:
            if(quest1Step == 3){
                cout << "Here you can continue Quest 1 and fight the Black Night.\n";
                availableQuests[0] = true;
                noQuests = false;
            }
            break;  
        case 6:
            if(quest1Step == 4){
                cout << "Here you can continue Quest 1 and fight the Blue Wizard.\n";
                availableQuests[0] = true;
                noQuests = false;
            }
            break;  
        default:
            cout << "It looks like you are nowhere...\n";
            
            break;
    }
    */
    if(noQuests){
        cout << "There are no Quests to do here.";
        menu.waitForEnter(menu.getEnterKeyState());
    }else{
        cout << "\n";
        makeChoice();
    }

    cout << endl;
    //menu.waitForEnter(menu.getEnterKeyState());
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
}
void Quests::makeChoice(){//I am thinking we should handle quests as an array
    //Menu menu;
    //I use an array of quest options to match an option number to a quest number. For example, option 0 --> quest 2, option 1 --> quest 5
    //Every option will be assigned (0, 1, 2, 3, etc.) even though not every quest is always available
    int questOption[NUMBER_OF_QUESTS], skips = 0, options = 0;
    for(int i = 1; i < NUMBER_OF_QUESTS + 1; i++){
        int option = i - skips;
        //The availableQuests array comes from the getAvailableQuests function. It checks if a quest number is available
        if(availableQuests[i - 1]){
            cout << "Do Quest " << i << ":                  Press \"" << option << "\"\n";
            //Here we write the quest number (e.g. 2, 3, 5) to the option number (e.g. 1, 2, 3)
            //So the quest number is 'i' and it gets written into the index [option - 1]
            questOption[option - 1] = i;
            options++;
        }else{
            skips++;
        }
    }
        cout << "Show Current Quests Info:    Press \"" << (options + 1) << "\"\n";
        cout << "Exit:                        Press \"0\"\n";
    int choice = menu.numberPressWait(options + 1, true);

    for(int i = 0; i < NUMBER_OF_QUESTS; i++){
        availableQuests[i] = false;
    }

    if(choice == 0){
        return;
    }else if(choice == (options + 1)){
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        for(int i = 0; i < options; i++){
            if(getQuestDescription(player.getUsername(), questOption[i]) != ""){
                cout << endl << getQuestDescription(player.getUsername(), questOption[i]);
            }
        }
        menu.waitForEnter(menu.getEnterKeyState());
    }else{
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        //need to refact the following to work with X Y instead of location value
        /*
        doQuest(player.getUsername(), player.getLocation(), questOption[choice - 1]);
        */
    }
}

void Quests::doQuest(string username, int location, int quest){
    //Menu menu;
    int quest1Step = player.getQuest1Progress(1);
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
            case 7:
                if(quest1Step == 8){
                    quest1(username, quest1Step);
                    noQuests = false;
                }
            default:
                cout << "It looks like you are nowhere...";
                break;
        }
    }else if(quest == 2){
        if(location == 2){
            if(player.getQuest1Progress(2) == 0){
                quest2(username, 0);
                noQuests = false;
            }
        }
    }else if(quest == 3){
        if(location == 2){
            if(player.getQuest1Progress(3) == 0){
                quest3(username, 0);
                noQuests = false;
            }
        }
    }else if(quest == 4){
        if(location == 3){
            if(player.getQuest1Progress(4) == 0){
                quest4(username, 0);
                noQuests = false;
            }
        }
    }
    else if(quest == 5){
        if(location == 2){
            if(player.getQuest1Progress(5) == 0){
                quest5(username, 0);
                noQuests = false;
            }
        }
    }else if(quest == 6){
        if(location == 2){
            if(player.getQuest1Progress(6) == 0){
                quest6(username, 0);
                noQuests = false;
            }
        }
    }else if(quest == 7){
        if(location == 3){
            if(player.getQuest1Progress(7) == 0){
                quest7(username, 0);
                noQuests = false;
            }
        }
    }
    else if(quest == 8){
        if(location == 2){
            if(player.getQuest1Progress(8) == 0){
                quest8(username, 0);
                noQuests = false;
            }
        }
    }

    if(noQuests){
        cout << "There are no Quests to do here.";
        menu.waitForEnter(menu.getEnterKeyState());
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
    }
}

void Quests::quest1(string username, int step){
    //Menu menu;
    Battle battle;
    cout << "\n";
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
            
            //battle.setPlayer(player);
            battle.questBattle(username, 1, step);
            //setPlayer(battle.getPlayer());

            //If the battle was won, we should run this code:
            if(player.getBattleResult()){
                cout << "\nYou are astonished at how incredibly weak the Void Cat turned out to be!";
                cout << "\nMight as well have been fighting a sand castle!\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou got 10000000 experience!\n";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou check the parchment again. The Void Cat's name is already fading.";
                cout << "\nA new name writes itself: Morg the Goblin. Somehow you know he is in the Glacius Desert.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
                system("cls");
                player.setQuest1Progress(0, 1);
                player.setBattleResult(false);
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
            
            //battle.setPlayer(player);
            battle.questBattle(username, 1, step);
            //setPlayer(battle.getPlayer());

            //A problem occurs if there's any server connection issues in the middle of a battle
            //Player health will trigger the quest completion, so I added a battle result boolean
            if(player.getBattleResult()){
                cout << "\nAs the goblin falls lifeless to the ground, you check your parchment again.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nA new name writes itself: Klade the Orc. Somehow you know he is near Lake Argentus.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou got 10000000 experience!\n";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                player.setQuest1Progress(0, 2);
                player.setBattleResult(false);
            }
            break;
        case 2:
            cout << "You circle the lake for hours, with no sign of the Orc. Finally, you sit beneath a tree to rest.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nBefore too long, a tall green man walks up to you. His footsteps make no sound.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\n\"I know you hunt me. Ready yourself.\"\n";
            menu.waitForEnter(menu.getEnterKeyState());
            
            //battle.setPlayer(player);
            battle.questBattle(username, 1, step);
            //setPlayer(battle.getPlayer());

            if(player.getBattleResult()){
                cout << "\nThe Orc collapses to the ground, eyes closed. He fought with honor.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nA new name writes itself: The Black Night. Somehow you know he is in Arva Umbra.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou got 10000000 experience!\n";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                player.setQuest1Progress(0, 3);
                player.setBattleResult(false);
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
            
            //battle.setPlayer(player);
            battle.questBattle(username, 1, step);
            //setPlayer(battle.getPlayer());

            if(player.getBattleResult()){
                cout << "\nThe Black Night shall ride no more. You read the enchanted parchment once again.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nA new name writes itself: The Blue Wizard. Somehow you know he is in Silva Ignis.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou got 10000000 experience!\n";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                player.setQuest1Progress(0, 4);
                player.setBattleResult(false);
            }
            break;
        case 4:
            cout << "You wander through the trees, marvelling at their strange color.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nA blast of fire just barely misses your shoulder. You wheel around, drawing your weapon!\n";
            menu.waitForEnter(menu.getEnterKeyState());
            
            //battle.setPlayer(player);
            battle.questBattle(username, 1, step);
            //setPlayer(battle.getPlayer());

            if(player.getBattleResult()){
                cout << "\nThe wizard collapses, but no body hits the ground. His robes simply crumple in the grass, \nwith his pointy hat perched neatly on top.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nA new name writes itself: The Monstrous Behemoth. Somehow you know he is in the Ventosus Mountains.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou got 10000000 experience!";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                player.setQuest1Progress(0, 5);
                player.setBattleResult(false);
            }
            break;
        case 5:
            cout << "The mountains loom ominously over everything. You dread the moment when the Monstrous Behemoth will finally appear.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nRight on time, a huge, hulking shape lumbers over the mountainside.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nSpotting you, it roars furiously, then leaps with incredible might!\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nIt clears an entire mountain in one great bound, then leaps again!\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nThis time, he lands in front of you. The menacing figure makes you feel very small.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nIn your mind, you are about to be fighting the mountain itself...";
            menu.waitForEnter(menu.getEnterKeyState());
            
            //battle.setPlayer(player);
            battle.questBattle(username, 1, step);
            //setPlayer(battle.getPlayer());

            if(player.getBattleResult()){
                cout << "\nIncredibly, the titanic being crashes into the snow. Hands shaking, you check the parchment.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nA new name has been written: The Awful Necromancer. You know he is in the Glacius Desert, and you are terrified.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou got 20000000 experience!\n";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                player.setQuest1Progress(0, 6);
                player.setBattleResult(false);
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
            
            //battle.setPlayer(player);
            battle.questBattle(username, 1, step);
            //setPlayer(battle.getPlayer());

            if(player.getBattleResult()){
                cout << "\nThe Necromancer screams, beams of light splitting his body apart, and he explodes into dust.\n";
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
                player.setQuest1Progress(0, 7);
                player.setBattleResult(false);
            }
            break;
        case 7:
            cout << "Meh, guess like a dragon showed up or some junk\n";
            menu.waitForEnter(menu.getEnterKeyState());
            
            //battle.setPlayer(player);
            battle.questBattle(username, 1, step);
            //setPlayer(battle.getPlayer());

            if(player.getBattleResult()){
                cout << "\nHuzzah, the dragon is like dead or whatever\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nWith the last enemy defeated, the enchanted parchment crumbles into dust.\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "\nYou finished the Quest! You got 50000000 experience!\n";
                //Code to add experience
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "Huzzah!\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "Huzzah!\n";
                menu.waitForEnter(menu.getEnterKeyState());
                cout << "Huzzah!\n";
                menu.waitForEnter(menu.getEnterKeyState());
                player.setQuest1Progress(0, 8);
                player.setBattleResult(false);
            }
            break;
        default:
            cout << "Error loading Quest...";
            menu.waitForEnter(menu.getEnterKeyState());
            break;
    }
}

void Quests::quest2(string username, int step){
    //Menu menu;
    Battle battle;
    if(step == 0){
        cout << "\nAs you are being a normal person doing normal things, a normal potato appears out of nowhere.\n";
        menu.waitForEnter(menu.getEnterKeyState());

        //battle.setPlayer(player);
        battle.questBattle(username, 2, 0);
        //setPlayer(battle.getPlayer());

        if(player.getBattleResult()){
            cout << "\nUNBELIEVABLE! You defeated a Normal Potato!\n";
            menu.waitForEnter(menu.getEnterKeyState());
            cout << "\nWhy would you do that? What have potatoes ever done to you?\n";
            player.setQuest1Progress(1, 1);
            player.setBattleResult(false);
        }else{
            cout << "\nUnbelievable! How could you lose a fight to a normal potato? Hang your head in shame!\n";
            menu.waitForEnter(menu.getEnterKeyState());
        }
    }
}

void Quests::quest3(string username, int step){
    //Menu menu;
    Battle battle;
    if(step == 0){
        cout << "\nQuest 3 is a garbage quest for testing.\n";
        menu.waitForEnter(menu.getEnterKeyState());

        //battle.setPlayer(player);
        battle.questBattle(username, 3, 0);
        //setPlayer(battle.getPlayer());

        if(player.getBattleResult()){
            cout << "\nQuest 3 is repeatable.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            player.setBattleResult(false);
        }
    }
}

void Quests::quest4(string username, int step){
    //Menu menu;
    Battle battle;
    if(step == 0){
        cout << "\nQuest 4 is a garbage quest for testing.\n";
        menu.waitForEnter(menu.getEnterKeyState());

        //battle.setPlayer(player);
        battle.questBattle(username, 4, 0);
        //setPlayer(battle.getPlayer());

        if(player.getBattleResult()){
            cout << "\nQuest 4 is repeatable.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            player.setBattleResult(false);
        }
    }
}

void Quests::quest5(string username, int step){
    //Menu menu;
    Battle battle;
    if(step == 0){
        cout << "\nQuest 5 is a garbage quest for testing.\n";
        menu.waitForEnter(menu.getEnterKeyState());

        //battle.setPlayer(player);
        battle.questBattle(username, 5, 0);
        //setPlayer(battle.getPlayer());

        if(player.getBattleResult()){
            cout << "\nQuest 5 is repeatable.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            player.setBattleResult(false);
        }
    }
}

void Quests::quest6(string username, int step){
    //Menu menu;
    Battle battle;
    if(step == 0){
        cout << "\nQuest 6 is a garbage quest for testing.\n";
        menu.waitForEnter(menu.getEnterKeyState());

        //battle.setPlayer(player);
        battle.questBattle(username, 6, 0);
        //setPlayer(battle.getPlayer());

        if(player.getBattleResult()){
            cout << "\nQuest 6 is repeatable.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            player.setBattleResult(false);
        }
    }
}

void Quests::quest7(string username, int step){
    //Menu menu;
    Battle battle;
    if(step == 0){
        cout << "\nQuest 7 is a garbage quest for testing.\n";
        menu.waitForEnter(menu.getEnterKeyState());

        //battle.setPlayer(player);
        battle.questBattle(username, 7, 0);
        //setPlayer(battle.getPlayer());

        if(player.getBattleResult()){
            cout << "\nQuest 7 is repeatable.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            player.setBattleResult(false);
        }
    }
}

void Quests::quest8(string username, int step){
    Battle battle;
    if(step == 0){
        cout << "\nYou stumble upon a gaggle of skunks!!!\n";
        menu.waitForEnter(menu.getEnterKeyState());

        battle.questBattle(username, 8, 0);

        if(player.getBattleResult()){
            cout << "\nYou defeat the skunks and escape with your life. But also with a nasty smell.\n";
            menu.waitForEnter(menu.getEnterKeyState());
            player.setQuest1Progress(1, 1);
            player.setBattleResult(false);
        }else{
            cout << "\nThe skunks lay you to waste. You are dead and embarassed.\n";
            menu.waitForEnter(menu.getEnterKeyState());
        }
    }
}
