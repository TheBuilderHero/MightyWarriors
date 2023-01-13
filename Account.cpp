#include <string>
#include <iostream>
#include <climits>
#include <limits>
#include <iomanip>
#include <cstdlib> //this and ctime are for the random number generator
#include <ctime> 
#include <sstream> //for the use of the cout being better with double numbers
#include <conio.h> //used for taking char inputs

#include "GlobalVariables.h"
#include "Account.h"
#include "ReachOutToServer.h"
#include "Cipher.h"
#include "Menu.h"
#include "TempEntity.h"
#include "DataGuard.h"

using namespace std;

#undef min // these are needed for the cin.ignore statments to clear out the buffer for new data.
#undef max 

/*************************************************************************
The purpose of this file to to manage the user account and Character setup
*************************************************************************/



void Account::setHealth(std::string username, int &remainingStatPoints, int numOfStatPoints){ //initial choice of health stats
    int healthS = 0;
    cout << "Enter the number of points you would like to add to your Health stat: ";
    cin >> healthS;
    if(healthS < 0) healthS = 0; //cancel negative inputs
    if (healthS <= remainingStatPoints) {
        initHealth = healthS;
        remainingStatPoints -= healthS;
    } else {
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        initHealth = initArmor = initMagicResistance = initPhysicalDamage = initMagicDamage = initAgility = initStealth = initStamina = initNaturalEnergy = initMind = initPsychicDamage = 0;
        system("pause");
        //levelUp(username, numOfStatPoints); //causing addition of multiple states
        restartLevelUp = true;
    }
}
void Account::setArmor(std::string username, int &remainingStatPoints, int numOfStatPoints){ //initial choice of Armor stats
    int armorS = 0;
    cout << "Enter the number of points you would like to add to your Armor stat: ";
    cin >> armorS;
    if(armorS < 0) armorS = 0; //cancel negative inputs
    if (armorS <= remainingStatPoints) {
        initArmor = armorS;
        remainingStatPoints -= armorS;
    } else {
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        initHealth = initArmor = initMagicResistance = initPhysicalDamage = initMagicDamage = initAgility = initStealth = initStamina = initNaturalEnergy = initMind = initPsychicDamage = 0;
        system("pause");
        restartLevelUp = true;
    }
}
void Account::setMagicResistance(std::string username, int &remainingStatPoints, int numOfStatPoints){ //initial choice of Magic Resistance stats
    int magicResistanceS = 0;
    cout << "Enter the number of points you would like to add to your Magic Resistance stat: ";
    cin >> magicResistanceS;
    if(magicResistanceS < 0) magicResistanceS = 0; //cancel negative inputs
    if (magicResistanceS <= remainingStatPoints) {
        initMagicResistance = magicResistanceS;
        remainingStatPoints -= magicResistanceS;
    } else {
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        initHealth = initArmor = initMagicResistance = initPhysicalDamage = initMagicDamage = initAgility = initStealth = initStamina = initNaturalEnergy = initMind = initPsychicDamage = 0;
        system("pause");
        restartLevelUp = true;
    }
}
void Account::setPhysicalDamage(std::string username, int &remainingStatPoints, int numOfStatPoints){ //initial choice of PhysicalDamage stats
    int attackS = 0;
    cout << "Enter the number of points you would like to add to your PhysicalDamage stat: ";
    cin >> attackS;
    if(attackS < 0) attackS = 0; //cancel negative inputs
    if (attackS <= remainingStatPoints) {
        initPhysicalDamage = attackS;
        remainingStatPoints -= attackS;
    } else {
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        initHealth = initArmor = initMagicResistance = initPhysicalDamage = initMagicDamage = initAgility = initStealth = initStamina = initNaturalEnergy = initMind = initPsychicDamage = 0;
        system("pause");
        restartLevelUp = true;
    }
}
void Account::setMagicDamage(std::string username, int &remainingStatPoints, int numOfStatPoints){ //initial choice of MagicDamage stats
    int magicDamageS = 0;
    cout << "Enter the number of points you would like to add to your MagicDamage stat: ";
    cin >> magicDamageS;
    if(magicDamageS < 0) magicDamageS = 0; //cancel negative inputs
    if (magicDamageS <= remainingStatPoints) {
        initMagicDamage = magicDamageS;
        remainingStatPoints -= magicDamageS;
    } else {
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        initHealth = initArmor = initMagicResistance = initPhysicalDamage = initMagicDamage = initAgility = initStealth = initStamina = initNaturalEnergy = initMind = initPsychicDamage = 0;
        system("pause");
        restartLevelUp = true;
    }
}
void Account::setAgility(std::string username, int &remainingStatPoints, int numOfStatPoints){ //initial choice of Agility stats
    int agilityS = 0;
    cout << "Enter the number of points you would like to add to your Agility stat: ";
    cin >> agilityS;
    if(agilityS < 0) agilityS = 0; //cancel negative inputs
    if (agilityS <= remainingStatPoints) {
        initAgility = agilityS;
        remainingStatPoints -= agilityS;
    } else {
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        initHealth = initArmor = initMagicResistance = initPhysicalDamage = initMagicDamage = initAgility = initStealth = initStamina = initNaturalEnergy = initMind = initPsychicDamage = 0;
        system("pause");
        restartLevelUp = true;
    }
}
void Account::setStealth(std::string username, int &remainingStatPoints, int numOfStatPoints){ //initial choice of Stealth stats
    int stealthS = 0;
    cout << "Enter the number of points you would like to add to your Stealth stat: ";
    cin >> stealthS;
    if(stealthS < 0) stealthS = 0; //cancel negative inputs
    if (stealthS <= remainingStatPoints) {
        initStealth = stealthS;
        remainingStatPoints -= stealthS;
    } else {
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        initHealth = initArmor = initMagicResistance = initPhysicalDamage = initMagicDamage = initAgility = initStealth = initStamina = initNaturalEnergy = initMind = initPsychicDamage = 0;
        system("pause");
        restartLevelUp = true;
    }
}
void Account::setStamina(std::string username, int &remainingStatPoints, int numOfStatPoints){ //initial choice of Stamina stats
    int staminaS = 0;
    cout << "Enter the number of points you would like to add to your Stamina stat: ";
    cin >> staminaS;
    if(staminaS < 0) staminaS = 0; //cancel negative inputs
    if (staminaS <= remainingStatPoints) {
        initStamina = staminaS;
        remainingStatPoints -= staminaS;
    } else {
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        initHealth = initArmor = initMagicResistance = initPhysicalDamage = initMagicDamage = initAgility = initStealth = initStamina = initNaturalEnergy = initMind = initPsychicDamage = 0;
        system("pause");
        restartLevelUp = true;
    }
}
void Account::setNaturalEnergy(std::string username, int &remainingStatPoints, int numOfStatPoints){ //initial choice of NaturalEnergy stats
    int naturalEnergyS = 0;
    cout << "Enter the number of points you would like to add to your NaturalEnergy stat: ";
    cin >> naturalEnergyS;
    if(naturalEnergyS < 0) naturalEnergyS = 0; //cancel negative inputs
    if (naturalEnergyS <= remainingStatPoints) {
        initNaturalEnergy = naturalEnergyS;
        remainingStatPoints -= naturalEnergyS;
    } else {
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        initHealth = initArmor = initMagicResistance = initPhysicalDamage = initMagicDamage = initAgility = initStealth = initStamina = initNaturalEnergy = initMind = initPsychicDamage = 0;
        system("pause");
        restartLevelUp = true;
    }
}
void Account::setMind(std::string username, int &remainingStatPoints, int numOfStatPoints){ //initial choice of NaturalEnergy stats
    int mindS = 0;
    cout << "Enter the number of points you would like to add to your Mind stat: ";
    cin >> mindS;
    if(mindS < 0) mindS = 0; //cancel negative inputs
    if (mindS <= remainingStatPoints) {
        initMind = mindS;
        remainingStatPoints -= mindS;
    } else {
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        initHealth = initArmor = initMagicResistance = initPhysicalDamage = initMagicDamage = initAgility = initStealth = initStamina = initNaturalEnergy = initMind = initPsychicDamage = 0;
        system("pause");
        restartLevelUp = true;
    }
}
void Account::setPsychicDamage(std::string username, int &remainingStatPoints, int numOfStatPoints){ //initial choice of NaturalEnergy stats
    int mindS = 0;
    cout << "Enter the number of points you would like to add to your Psychic Damage stat: ";
    cin >> mindS;
    if(mindS < 0) mindS = 0; //cancel negative inputs
    if (mindS <= remainingStatPoints) {
        initPsychicDamage = mindS;
        remainingStatPoints -= mindS;
    } else {
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout << "You entered an invalid number of statpoints to be added." << endl << "Restarting this proccess so you can complete this task.";
        initHealth = initArmor = initMagicResistance = initPhysicalDamage = initMagicDamage = initAgility = initStealth = initStamina = initNaturalEnergy = initMind = initPsychicDamage = 0;
        system("pause");
        restartLevelUp = true;
    }
}

void Account::createPlayer(string username){ //This is the inital user setup (should run through Race selection and Kit selection) and this should all be saved to the server
    ReachOutToServer server;
    Cipher code;

    cout << "Welcome to Character creation!" << endl;
    system("pause");
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    int raceChoice = 0;
    char answer;
    bool exitNow = false;
    while(!exitNow){ //while the user has not selected one of the five options it will continue to ask them for an aswer.
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        raceChoice = 0;
        cout << endl << "Select your Character's race:" << endl;
        cout << "Please type the number corresponding to one of the races listed below (Note, this cannot be changed later!): "<< endl << endl;
        cout << "1  Human" << endl;
        cout << " -> Humans get a random bonus stat for each battle" << endl << endl;
        cout << "2  Ghost" << endl;
        cout << " ->  Ghosts have a chance to etherealize, ignoring attacks" << endl << endl;
        cout << "3  Dino" << endl;
        cout << " ->  Has a chance to stunce enemies every round" << endl << endl;
        cout << "4  Elf" << endl;
        cout << " -> Elves have a chance for an extra attack" << endl << endl;
        cout << "5  Dryad" << endl;
        cout << " -> Dryads can reflect abilities back on an attacker" << endl << endl;
        cout << ">";
        try{
            raceChoice = menu.numberPressWaitSpecial(5, 'A', 'P', 'R', 'I', 'L');
        } catch(...) {
            raceChoice = 0;
            menu.display(0,0," Race selction issue ", false, true);
        }
        if ((raceChoice <= 0 || raceChoice > 5) && (raceChoice != 100)) {
            cin.clear(); //this and the next resolve issues with infinitely looping invalid
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
            cout << "You have entered an invalid input, Please try again." << endl;
            raceChoice = 0;
            system("pause");
            menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
        } else {
            string raceName;
            switch(raceChoice){
            case 1:
                raceName = "Human";
                break;
            case 2:
                raceName = "Ghost";
                break;
            case 3:
                raceName = "Dino";
                break;
            case 4:
                raceName = "Elf";
                break;
            case 5:
                raceName = "Dryad";
                break;
            case 100:
                raceName = "Mop";
                break;
            default:
                raceName = "not chosen";
                break;
            }
            
            bool answered = false;
            while(!answered) { //validate the chosen race
                //Menu menu;
                cout << "Your race has been set to " << raceName << ". Would you like to accept this and continue?(Y/N)" << endl << ">";
                answer = menu.yesOrNo();
                if (answer != 'n' && answer !='N' && answer !='y' && answer !='Y') { //if they did not enter y, Y, n, or, N then we will tell them what they input is invalid and retry.
                    cout << "Unrecognized input." << "   Please enter a valid input." << endl;
                    system("pause");
                    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
                    system("cls");
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
                } else if (answer =='y' || answer =='Y') { //if they are statisfied with their choice it will move on and exit both while loops
                    answered = true;
                    exitNow = true;
                } else { //if they are not satisfied with their choice it will exit the loop of asking them if they are stisfied and reask about the race which they want to select.
                    answered = true;
                }
            }
        }
    }
    menu.ClearConsoleInputBuffer();
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    //Now that the race has been chosen and validated move on to kit selection
    int kitChoice = 0;
    exitNow = false;
    while(!exitNow){ //while the user has not selected one of the four kit options it will continue to ask them for an aswer to kitChoice. << endl
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        kitChoice = 0;
        cout << endl << "Select your Character's kit:" << endl;
        cout << "Please type the number corresponding to one of the kits from the list below (Note, this cannot be changed later!): "<< endl << endl;
        cout << "1  Tank" << endl;
        cout << " -> Tanks gain +3 on Armor, Magic Resistance, and Health" << endl << endl;
        cout << "2  Assassin" << endl;
        cout << " -> Assassins gain +5 on Attack" << endl << endl;
        cout << "3  Archer" << endl;
        cout << " -> Archers gain +2 on Attack and +1 on Armor and Magic Resistance" << endl << endl;
        cout << "4  Mage" << endl;
        cout << " -> Mages gain +2 on Ability and +3 on Magic Resistance" << endl << endl;
        cout << "5  Ninja" << endl;
        cout << " -> Ninjas gain +2 on Attack and +3 on Agility and Stealth" << endl << endl;
        cout << "6  Mentalist" << endl;
        cout << " -> Mentalists gain +2 on Mind and +2 onPsychic Attack" << endl << endl;
        cout << ">";
        kitChoice = menu.numberPressWait(6);
        if (kitChoice <= 0 || kitChoice > 6) {
            cin.clear(); //this and the next resolve issues with infinitely looping invalid
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
            cout << "You have entered an invalid input, Please try again." << endl;
            kitChoice = 0;
            system("pause");
            menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
        } else {
            string kitName;
            switch(kitChoice){
                case 1:
                    kitName = "Tank";
                    break;
                case 2:
                    kitName = "Assassin";
                    break;
                case 3:
                    kitName = "Archer";
                    break;
                case 4:
                    kitName = "Mage";
                    break;
                case 5:
                    kitName = "Ninja";
                    break;
                case 6:
                    kitName = "Mentalist";
                    break;
                default:
                    kitName = "not chosen";
                    break;
            }
            int answered = 0; // 0 for false :: 1 for true
            while(!answered) { //validate the chosen race
                //Menu menu;
                cout << "Your kit has been set to " << kitName << ". Would you like to accept this and continue?(Y/N)" << endl << ">";
                answer = menu.yesOrNo();
                if (answer != 'n' && answer !='N' && answer !='y' && answer !='Y') { //if they did not enter y, Y, n, or, N then we will tell them what they input is invalid and retry.
                    cout << "Unrecognized input." << "   Please enter a valid input." << endl;
                    system("pause");
                    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
                    system("cls");
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
                } else if (answer =='y' || answer =='Y') { //if they are statisfied with their choice it will move on and exit both while loops
                    answered = 1;
                    exitNow = 1;
                } else { //if they are not satisfied with their choice it will exit the loop of asking them if they are stisfied and reask about the race which they want to select.
                    answered = 1;
                }
            }
        }
    }
    menu.ClearConsoleInputBuffer();

    //Setup Player Weapon:
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    int weaponChoice = 0;
    exitNow = false;
    while(!exitNow){ //while the user has not selected one of the weapon options it will continue to ask them for an answer to weaponChoice.
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        weaponChoice = 0;
        cout << endl << "Select your Character's weapon:" << endl;
        cout << "Please type the number corresponding to one of the kits from the list below (Note, this cannot be changed later!): "<< endl << endl;
        cout << "1  Sword" << endl;
        cout << " ->  +20 Physical Damage" << endl << endl;
        cout << "2  Bow" << endl;
        cout << " ->  +12 Physical Damage" << endl << endl;
        cout << "3  Dagger" << endl;
        cout << " ->  +12 Physical Damage" << endl << endl;
        cout << "4  Fire Rune" << endl;
        cout << " -> +18 Magic Damage and +3 Physical Damage" << endl << endl;
        cout << "5  Wind Rune" << endl;
        cout << " ->  +14 Magic Damage and +6 Physical Damage" << endl << endl;
        cout << "6  Ice Spike" << endl;
        cout << " -> +36 Magic Damage and +16 Physical Damage" << endl << endl;
        cout << "7  Black Book" << endl;
        cout << " -> +8 Magic Damage and +8 Physical Damage and +5 PsychicDamage" << endl << endl;
        cout << ">";
        weaponChoice = menu.numberPressWait(7);
        if (weaponChoice <= 0 || weaponChoice > 7) {
            cin.clear(); //this and the next resolve issues with infinitely looping invalid
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
            cout << "You have entered an invalid input, Please try again." << endl;
            weaponChoice = 0;
            system("pause");
            menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
        } else {
            string weaponName;
            switch(weaponChoice){
                case 1:
                    weaponName = "Sword";
                    break;
                case 2:
                    weaponName = "Bow";
                    break;
                case 3:
                    weaponName = "Dagger";
                    break;
                case 4:
                    weaponName = "Fire Rune";
                    break;
                case 5:
                    weaponName = "Wind Rune";
                    break;
                case 6:
                    weaponName = "Ice Spike";
                    break;
                case 7:
                    weaponName = "Black Book";
                    break;
                default:
                    weaponName = "not chosen";
                    break;
            }
            int answered = 0; // 0 for false :: 1 for true
            while(!answered) { //validate the chosen race
                //Menu menu;
                cout << "Your Weapon has been set to " << weaponName << ". Would you like to accept this and continue?(Y/N)" << endl << "";
                answer = menu.yesOrNo();
                if (answer != 'n' && answer !='N' && answer !='y' && answer !='Y') { //if they did not enter y, Y, n, or, N then we will tell them what they input is invalid and retry.
                    cout << "Unrecognized input." << "   Please enter a valid input." << endl;
                    system("pause");
                    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
                    system("cls");
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
                } else if (answer =='y' || answer =='Y') { //if they are statisfied with their choice it will move on and exit both while loops
                    answered = 1;
                    exitNow = 1;
                } else { //if they are not satisfied with their choice it will exit the loop of asking them if they are stisfied and reask about the race which they want to select.
                    answered = 1;
                }
            }
        }
    }
    menu.ClearConsoleInputBuffer();


    server.sendToServer(code.cipher("8", username, to_string(raceChoice), to_string(kitChoice), to_string(weaponChoice))); //write race and kit to .dat file on server

    //add it an inital stat personalization
    string wasAbleToSave = server.sendToServer(code.cipher("5", username, to_string(initHealth), to_string(initArmor), to_string(initMagicResistance), to_string(initPhysicalDamage), to_string(initMagicDamage), to_string(initAgility),
    to_string(initStealth), to_string(initStamina), to_string(initNaturalEnergy), to_string(initMind), to_string(initPsychicDamage))); //These send the data to the server to be saved properly in the [username].stat file
    player.runConstructorValueSetup(username);
    //menu.setPlayer(player);
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    introStory(raceChoice, username); //send the user to the intro story
    menu.changePass(username); //before sending them to the logon screen they need to set their new account's password.
}
void Account::levelUp(std::string username, int numOfStatPoints){
    Cipher code;
    ReachOutToServer server;
    restartLevelUp = false;
    int remainingStatPoints = numOfStatPoints;
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    cout << "(Health, Armor, Magic Resistance, Physical Damage, Magic Damage, Agility, Stealth, Stamina, NaturalEnergy, Mind, Pyschic Damage)" << endl << "You have " + to_string(remainingStatPoints) + " points that can be distributed among the above stats" << endl;
    system("pause");
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    cout << "You have " + to_string(remainingStatPoints) + " points that can be distributed among the above stats" << endl << endl << "Please enter the number of points to add to each stat." << endl << endl;
    setHealth(username, remainingStatPoints, numOfStatPoints);
    if (remainingStatPoints > 0 && !restartLevelUp) setArmor(username, remainingStatPoints, numOfStatPoints);
    if (remainingStatPoints > 0 && !restartLevelUp) setMagicResistance(username, remainingStatPoints, numOfStatPoints);
    if (remainingStatPoints > 0 && !restartLevelUp) setPhysicalDamage(username, remainingStatPoints, numOfStatPoints);
    if (remainingStatPoints > 0 && !restartLevelUp) setMagicDamage(username, remainingStatPoints, numOfStatPoints);
    if (remainingStatPoints > 0 && !restartLevelUp) setAgility(username, remainingStatPoints, numOfStatPoints);
    if (remainingStatPoints > 0 && !restartLevelUp) setStealth(username, remainingStatPoints, numOfStatPoints);
    if (remainingStatPoints > 0 && !restartLevelUp) setStamina(username, remainingStatPoints, numOfStatPoints);
    if (remainingStatPoints > 0 && !restartLevelUp) setNaturalEnergy(username, remainingStatPoints, numOfStatPoints);
    if (remainingStatPoints > 0 && !restartLevelUp) setMind(username, remainingStatPoints, numOfStatPoints);
    if (remainingStatPoints > 0 && !restartLevelUp) setPsychicDamage(username, remainingStatPoints, numOfStatPoints);
    if (remainingStatPoints > 0 && !restartLevelUp) { //if the user did not use all their stat points we will restart the proccess
        cout << remainingStatPoints << endl;
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cout << "You did not use all your Stat Points..." << endl << "Restarting this proccess so you can complete this task.";
        system("pause");
        initHealth = initArmor = initMagicResistance = initPhysicalDamage = initMagicDamage = initAgility = initStealth = initStamina = initNaturalEnergy = initMind = initPsychicDamage = 0; //reset all to 0
        levelUp(username, numOfStatPoints);
    } else if (restartLevelUp) {
        initHealth = initArmor = initMagicResistance = initPhysicalDamage = initMagicDamage = initAgility = initStealth = initStamina = initNaturalEnergy = initMind = initPsychicDamage = 0; //reset all to 0
        levelUp(username, numOfStatPoints);
    } else {
    cout << "Your stat points have been to set to the following: " << endl << "Health: " << initHealth << endl << "Armor: " << initArmor << endl << "Magic Resistance: " 
    << initMagicResistance << endl << "Physical Damage: " << initPhysicalDamage << endl << "Magic Damage: " << initMagicDamage << endl << "Agility: " << initAgility << endl
    << "Stealth: " << initStealth << endl << "Stamina: " << initStamina << endl << "NaturalEnergy: " << initNaturalEnergy << endl << "Mind: " << initMind << endl << "Psychic Damage: " << initPsychicDamage << endl;
    //place all stats in dataguard to be saved to server if the program is closed.
    guard.updateSaveValueMaxHealth(initHealth);
    guard.updateSaveValueArmor(initArmor);
    guard.updateSaveValuePhysicalDamageMax(initPhysicalDamage);
    guard.updateSaveValueMagicResistance(initMagicResistance);
    guard.updateSaveValueMagicDamageMax(initMagicDamage);
    guard.updateSaveValueAgility(initAgility);
    guard.updateSaveValueStealth(initStealth);
    guard.updateSaveValueStamina(initStamina);
    guard.updateSaveValueNaturalEnergy(initNaturalEnergy);
    guard.updateSaveValueMaxMind(initMind);
    guard.updateSaveValuePsychicDamageMax(initPsychicDamage);
    //also update the current stats:
    
    //player.

    //Will need to modify with new data guard
    //Replacing this with temp entity //string wasAbleToSave = server.sendToServer(code.cipher("16", username, to_string(initHealth), to_string(initArmor), to_string(initMagicResistance), to_string(initPhysicalDamage), to_string(initMagicDamage), to_string(initAgility), to_string(initStealth), to_string(initStamina), to_string(initNaturalEnergy), to_string(initMind), to_string(initPsychicDamage))); 
    //These send the data to the server to be saved properly in the [username].stat file

    system("pause");
    }
}

int Account::getHealth(std::string username){ //reuturns the users current Health stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.getItemS(1));
}
int Account::getPhysicalDamage(std::string username){ //returns attack damage for an attack
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.getItemS(4));
}
string Account::getPhysicalDamageString(std::string username){ //reuturns the users current Attack stat range instead of an amount of damage for attacks
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return code.getItemS(4);
}
int Account::getArmor(std::string username){ //reuturns the users current Armor stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username))); 
    return stoi(code.getItemS(2));
}
int Account::getMagicResistance(std::string username){ //reuturns the users current MagicResistance stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.getItemS(3));
}
int Account::getMagicDamage(std::string username){ //returns magic damage for an attack
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.getItemS(5));
}
string Account::getMagicDamageString(std::string username){ //reuturns the users current Attack stat range instead of an amount of damage for attacks
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return code.getItemS(5);
}
int Account::getAgility(std::string username){ //reuturns the users current Agility stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.getItemS(6));
}
int Account::getStealth(std::string username){ //reuturns the users current Stealth stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.getItemS(7));
}
int Account::getStamina(std::string username){ //reuturns the users current Stamina stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.getItemS(8));
}
int Account::getNaturalEnergy(std::string username){ //reuturns the users current NaturalEnergy stat
    ReachOutToServer server;
    Cipher code;
    code.decipherS(server.sendToServer(code.cipher("6", username)));
    return stoi(code.getItemS(9));
}
string Account::getMagicDamgeAbilities(std::string username){
    ReachOutToServer server;
    Cipher code;
    string magicDamageAbilities = "Magic Damage Abilities: ";
    code.decipherS(server.sendToServer(code.cipher("12", username)));
    if (code.getItemS(1) == "Magic") magicDamageAbilities += " Q";
    if (code.getItemS(2) == "Magic") magicDamageAbilities += " W";
    if (code.getItemS(3) == "Magic") magicDamageAbilities += " E";
    if (code.getItemS(4) == "Magic") magicDamageAbilities += " R";

    return magicDamageAbilities;
}
string Account::getPhysicalDamgeAbilities(std::string username){
    ReachOutToServer server;
    Cipher code;
    string physicalDamageAbilities = "Physical Damage Abilities: ";
    code.decipherS(server.sendToServer(code.cipher("12", username)));
    if (code.getItemS(1) == "Physical") physicalDamageAbilities += " Q";
    if (code.getItemS(2) == "Physical") physicalDamageAbilities += " W";
    if (code.getItemS(3) == "Physical") physicalDamageAbilities += " E";
    if (code.getItemS(4) == "Physical") physicalDamageAbilities += " R";

    return physicalDamageAbilities;
}
string Account::getKit(std::string username){ //returns the players Kit
    Cipher code;
    ReachOutToServer server;
    code.decipherS(server.sendToServer(code.cipher("13", username)));
    return code.getItemS(2);
}
string Account::getRace(std::string username){ //returns the players race
    Cipher code;
    ReachOutToServer server;
    code.decipherS(server.sendToServer(code.cipher("13", username)));
    return code.getItemS(1);
}
string Account::getWeapon(std::string username){
    Cipher code;
    ReachOutToServer server;
    code.decipherS(server.sendToServer(code.cipher("13", username)));
    return code.getItemS(3);
}
int Account::getLevel(std::string username){
    Cipher code;
    ReachOutToServer server;
    code.decipherS(server.sendToServer(code.cipher("15", username))); //this gets the player's level from the server
    string playerLevel = code.getItemS(1);
    return stoi(playerLevel);
}
double Account::getCurrentXPForNextLevel(std::string username){
    Cipher code;
    ReachOutToServer server;
    code.decipherS(server.sendToServer(code.cipher("15", username))); //this gets the total needed XP from the server
    string currentXPForNextLevel = code.getItemS(2);
    return stod(currentXPForNextLevel);
}
double Account::getTotalXPForNextLevel(std::string username){
    Cipher code;
    ReachOutToServer server;
    code.decipherS(server.sendToServer(code.cipher("15", username))); //this gets the total needed XP from the server
    string totalXPForNextLevel = code.getItemS(3);
    return stod(totalXPForNextLevel);
}

//Dakota please add a variable and code for this
int Account::getQuest1Progress(std::string username){
    return 0;
}
//Dakota please add code to save player quest progress
void Account::setQuest1Progress(std::string username, int step){
    
}

void Account::displayStats(std::string username, int bypass ,string usernameA){
    Cipher code;
    ReachOutToServer server;
    if (bypass == 0) { //standard user
        string physicalAbilities = getPhysicalDamgeAbilities(username);
        string magicalAbilites = getMagicDamgeAbilities(username);
        string raceOutput = "Player Race: " + getRace(username);
        string kitOutput = "Player Kit: " + getKit(username);
        string weaponOutput = "Player Weapon: " + getWeapon(username);
        stringstream currentXP, totalXP;
        currentXP << fixed << setprecision(0) << getCurrentXPForNextLevel(username); //format the XP
        totalXP << fixed << setprecision(0) << getTotalXPForNextLevel(username); //format the XP
        string currentXPFormatted = currentXP.str();
        string totalXPFormatted = totalXP.str();
        string playerLevelInfo = "Player Level: " + to_string(getLevel(username)) +  " With " + currentXPFormatted + "XP of " + totalXPFormatted + "XP";
        cout << "Your stats are as follows: " << endl << setfill('=') << setw(92) << "=" << endl 
        << "Health: " << setfill(' ') << setw(34) << getHealth(username) 
        << setw(5 + playerLevelInfo.length()) << playerLevelInfo << endl << setfill('-') << setw(42) << "-" << setfill(' ') 
        << setw(5 + raceOutput.length()) << raceOutput << endl 
        << "Armor: " << setfill(' ') << setw(35) << getArmor(username) 
        << setw(5 + kitOutput.length()) << kitOutput << endl << setfill('-') << setw(42) << "-" << setfill(' ') 
        << setw(5 + weaponOutput.length()) << weaponOutput << endl 
        << "Magic Resistance: " << setfill(' ') << setw(24) << getMagicResistance(username) << endl << setfill('-') << setw(42) << "-" << endl 
        << "Physical Damage: " << setfill(' ') << setw(25) << getPhysicalDamageString(username) << setfill(' ') << setw(5 + physicalAbilities.length()) << physicalAbilities << endl << setfill('-') << setw(42) << "-" << endl 
        << "Magic Damage: " << setfill(' ') << setw(28) << getMagicDamageString(username) << setfill(' ') << setw(5 + magicalAbilites.length()) << magicalAbilites << endl << setfill('-') << setw(42) << "-" << endl 
        << "Agility: " << setfill(' ') << setw(33) << getAgility(username) << endl << setfill('-') << setw(42) << "-" << endl 
        << "Stealth: " << setfill(' ') << setw(33) << getStealth(username) << endl << setfill('-') << setw(42) << "-" << endl 
        << "Stamina: " << setfill(' ') << setw(33) << getStamina(username) << endl << setfill('-') << setw(42) << "-" << endl 
        << "NaturalEnergy: " << setfill(' ') << setw(36) << getNaturalEnergy(username) << endl << setfill('-') << setw(42) << "-" << endl; //This cout statement prints out all the stats for the user to see.
        system("pause");
    } 
    if (bypass == 1) { //admin account
        if(stoi(server.sendToServer(code.cipher("1", username))) == 0) {
            string physicalAbilities = getPhysicalDamgeAbilities(username);
            string magicalAbilites = getMagicDamgeAbilities(username);
            string raceOutput = "Player Race: " + getRace(username);
            string kitOutput = "Player Kit: " + getKit(username);
            stringstream currentXP, totalXP;
            currentXP << fixed << setprecision(0) << getCurrentXPForNextLevel(username); //format the XP
            totalXP << fixed << setprecision(0) << getTotalXPForNextLevel(username); //format the XP
            string currentXPFormatted = currentXP.str();
            string totalXPFormatted = totalXP.str();
            string playerLevelInfo = "Player Level: " + to_string(getLevel(username)) +  " With " + currentXPFormatted + "XP of " + totalXPFormatted + "XP";
            cout << "Your stats are as follows: " << endl << setfill('=') << setw(92) << "=" << endl 
            << "Health: " << setfill(' ') << setw(34) << getHealth(username) 
            << setw(5 + playerLevelInfo.length()) << playerLevelInfo << endl << setfill('-') << setw(42) << "-" << setfill(' ') 
            << setw(5 + raceOutput.length()) << raceOutput << endl 
            << "Armor: " << setfill(' ') << setw(35) << getArmor(username) 
            << setw(5 + kitOutput.length()) << kitOutput << endl << setfill('-') << setw(42) << "-" << endl 
            << "Magic Resistance: " << setfill(' ') << setw(24) << getMagicResistance(username) << endl << setfill('-') << setw(42) << "-" << endl 
            << "Physical Damage: " << setfill(' ') << setw(25) << getPhysicalDamage(username) << setfill(' ') << setw(5 + physicalAbilities.length()) << physicalAbilities << endl << setfill('-') << setw(42) << "-" << endl 
            << "Magic Damage: " << setfill(' ') << setw(28) << getMagicDamage(username) << setfill(' ') << setw(5 + magicalAbilites.length()) << magicalAbilites << endl << setfill('-') << setw(42) << "-" << endl 
            << "Agility: " << setfill(' ') << setw(33) << getAgility(username) << endl << setfill('-') << setw(42) << "-" << endl 
            << "Stealth: " << setfill(' ') << setw(33) << getStealth(username) << endl << setfill('-') << setw(42) << "-" << endl 
            << "Stamina: " << setfill(' ') << setw(33) << getStamina(username) << endl << setfill('-') << setw(42) << "-" << endl 
            << "NaturalEnergy: " << setfill(' ') << setw(36) << getNaturalEnergy(username) << endl << setfill('-') << setw(42) << "-" << endl; //This cout statement prints out all the stats for the user to see.
            system("pause");
        } else {
            cout << "You did not enter a valid user which has stats to view..." << endl;
            system("pause");
        }
        menu.adminMenu(usernameA);
    }
}
/*void Account::displayStats(std::string username, TempEntity player, int bypass){
    if (bypass == 0) {//run the testing stat output (default)
        string physicalAbilities = getPhysicalDamgeAbilities(username);
        string magicalAbilites = getMagicDamgeAbilities(username);
        string raceOutput = "Player Race: " + getRace(username);
        string kitOutput = "Player Kit: " + getKit(username);
        string weaponOutput = "Player Weapon: " + getWeapon(username);
        stringstream currentXP, totalXP;
        currentXP << fixed << setprecision(0) << getCurrentXPForNextLevel(username); //format the XP
        totalXP << fixed << setprecision(0) << getTotalXPForNextLevel(username); //format the XP
        string currentXPFormatted = currentXP.str();
        string totalXPFormatted = totalXP.str();
        string playerLevelInfo = "Player Level: " + to_string(getLevel(username)) +  " With " + currentXPFormatted + "XP of " + totalXPFormatted + "XP";
        cout << "Your stats are as follows: " << endl << setfill('=') << setw(92) << "=" << endl 
        << "Health: " << setfill(' ') << setw(34) << getHealth(username) 
        << setw(5 + playerLevelInfo.length()) << playerLevelInfo << endl << setfill('-') << setw(42) << "-" << setfill(' ') 
        << setw(5 + raceOutput.length()) << raceOutput << endl 
        << "Armor: " << setfill(' ') << setw(35) << getArmor(username) 
        << setw(5 + kitOutput.length()) << kitOutput << endl << setfill('-') << setw(42) << "-" << setfill(' ') 
        << setw(5 + weaponOutput.length()) << weaponOutput << endl 
        << "Magic Resistance: " << setfill(' ') << setw(24) << getMagicResistance(username) << endl << setfill('-') << setw(42) << "-" << endl 
        << "Physical Damage: " << setfill(' ') << setw(25) << getPhysicalDamageString(username) << setfill(' ') << setw(5 + physicalAbilities.length()) << physicalAbilities << endl << setfill('-') << setw(42) << "-" << endl 
        << "Magic Damage: " << setfill(' ') << setw(28) << getMagicDamageString(username) << setfill(' ') << setw(5 + magicalAbilites.length()) << magicalAbilites << endl << setfill('-') << setw(42) << "-" << endl 
        << "Agility: " << setfill(' ') << setw(33) << getAgility(username) << endl << setfill('-') << setw(42) << "-" << endl 
        << "Stealth: " << setfill(' ') << setw(33) << getStealth(username) << endl << setfill('-') << setw(42) << "-" << endl 
        << "Stamina: " << setfill(' ') << setw(33) << getStamina(username) << endl << setfill('-') << setw(42) << "-" << endl 
        << "NaturalEnergy: " << setfill(' ') << setw(36) << getNaturalEnergy(username) << endl << setfill('-') << setw(42) << "-" << endl; //This cout statement prints out all the stats for the user to see.
        system("pause");
    }
}*/

void Account::logonScreen(int type){ //defualt is case 1 - that is a standard logon... Case 2 is change password logon
    Cipher code;
    //Menu menu;
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    ReachOutToServer server;
    string usernameE;
    string passwordE;
    int validLogon;
    switch (type){
        case 1:{
            unsigned int UsernameLength = 38;
            unsigned int passwordLength = 38;
            unsigned short int cursorPos = 3; //starts with username
            bool makingDecision = true;
            menu.display(37, 1, "Logon Screen");
            menu.display(12, 2, "Please enter your username and password (Use tab to switch or press ESC for new account)");
            string UsernameString = "Username:";
            menu.display(37-UsernameString.length(), 3, UsernameString);
            menu.display(37, 3, "> ", false, false);
            string passString = "Password:";
            menu.display(37-passString.length(), 5, passString);
            menu.display(37, 5, "> ", false, false);
            char input;
            menu.display(UsernameLength, cursorPos, "", false, false); //inital cursor start position
            bool currentSelectionUsername = true;
            vector<char> username;
            vector<char> password;
            while(makingDecision){//swaps between username and password
                input = _getch();
                
                menu.display(0,0,"                                  ");
                if(cursorPos == 3) menu.display(UsernameLength, cursorPos, "", false, false); //this brings you back to either one of the two positions
                if(cursorPos == 5) menu.display(passwordLength, cursorPos, "", false, false); //this brings you back to either one of the two positions

                if (input == 9){
                    if(currentSelectionUsername){
                        cursorPos = 5;
                        menu.display(passwordLength, cursorPos, "", false, false); //this brings you back to either one of the two positions
                        currentSelectionUsername = false;
                    } else {
                        cursorPos = 3;
                        menu.display(UsernameLength, cursorPos, "", false, false); //this brings you back to either one of the two positions
                        currentSelectionUsername = true;
                    }
                } else if (input == 8){
                    if(cursorPos == 3){
                        if(username.size() > 0) {
                            username.pop_back();
                            menu.display(UsernameLength, cursorPos, " ", false, false); //this brings you back to either one of the two positions
                            UsernameLength--;
                            menu.display(UsernameLength, cursorPos, "", false, false); //this brings you back to either one of the two positions
                        }
                    } else if(cursorPos == 5){
                        if(password.size() > 0) {
                            password.pop_back();
                            menu.display(passwordLength, cursorPos, " ", false, false); //this brings you back to either one of the two positions
                            passwordLength--;
                            menu.display(passwordLength, cursorPos, "", false, false); //this brings you back to either one of the two positions
                        }
                    }
                } else if (input == 27){
                    //menu.displayMessageWithPause(20,20,"Escape");
                    createNewAccount();
                } else { //backspace == 8 //esc == 27
                    if (GetKeyState(VK_RETURN) < 0){ //check for password completion
                        while(GetKeyState(VK_RETURN) < 0){}
                        makingDecision = false;
                        break;
                    } else if (cursorPos == 5){
                        password.emplace_back(input);
                        cout << "*";
                        passwordLength++;
                    } else if (cursorPos == 3){
                        username.emplace_back(input);
                        cout << input;
                        UsernameLength++;
                    }
                }/*
                menu.display(0,0,"This is the char: " + to_string(input));
                if(cursorPos == 3) menu.display(UsernameLength, cursorPos, " ", false, false); //this brings you back to either one of the two positions
                if(cursorPos == 5) menu.display(passwordLength, cursorPos, " ", false, false); //this brings you back to either one of the two positions*/
            }
            for(int i = 0; i < username.size(); i++) usernameE += username.at(i);
            for(int i = 0; i < password.size(); i++) passwordE += password.at(i);
            validLogon = stoi(server.sendToServer(code.cipher("3", usernameE, passwordE)));
            if (validLogon == 1){//logon is valid
                player.runConstructorValueSetup(usernameE, true);//setup temp entity to be used in the whole program
                //TempEntity player{usernameE, true};
                //menu.setPlayer(player); 
                menu.menu(usernameE);
            } else {
                string invalidMessage = "Invalid Username or Password...";
                menu.display(12, 0, invalidMessage, false, true);
                menu.displayMessageWithPause(12+invalidMessage.length(), 1, "", false);
                //logon is invalid
                logonScreen();
            }
            break;
        }
        case 2:{ //change password verification
            menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
            menu.display(19, 1, "Please confirm your current credentials");
            menu.display(23, 2, "Please enter your username");
            menu.display(37, 3, "> ", false, false);
            cin >> usernameE;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
            menu.display(16, 2, "Please enter the CURRENT password for the account");
            menu.display(37, 3, "> ", false, false);
            cin >> passwordE;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
            validLogon = stoi(server.sendToServer(code.cipher("3", usernameE, passwordE)));
            if (validLogon == 1){//logon is valid
                menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
                system("cls");
                menu.changePass(usernameE);
            } else {
                menu.display(20, 4, "Invalid Username or Password...", false, true);
                system("pause");
                //logon is invalid
                logonScreen(); // try again
            }
            break;
        }
        case 3:{ // adminbypass panel
            menu.display(18, 2, "You are at the admin bypass panel", false, false);
            menu.display(18, 3, "Please enter the admin username", false, false);
            menu.display(18, 4, ">", false, false);
            cin >> usernameE;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
            menu.display(18, 5, "Please enter the password for the account", false, false);
            menu.display(18, 6, ">", false, false);
            cin >> passwordE;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
            validLogon = stoi(server.sendToServer(code.cipher("3", usernameE, passwordE)));
            if (validLogon == 1){//logon is valid
                menu.adminMenu(usernameE);
            } else {
                menu.display(18, 7, "Invalid Username or Password...", false, true);
                system("pause");
                //logon is invalid
                logonScreen();
            }
            break;
        }
    }
}

void Account::createNewAccount(){ //runs through the code to create a new user account from scratch
    int valid; // is the username valid or not (1 meaning the username is valid, 0 meaning the username is taken)
    ReachOutToServer server;//declare server object to use sendserver function to check if server has someone by this username
    Cipher code; //declare the Cipher class so that I can use the functions cipher and decipher
    Account account;
    string username; //declare the local username for the user creating their account

    //ask user for the username they would like to use
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    menu.display(18, 2, "What would you like the username of your new account to be?", false, false);
    menu.display(18, 3, "Please type a valid username.", false, false);
    menu.display(18, 4, ">", false, false);
    cin >> username;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");

    //check to make sure the username is valid and not already taken
    if (username.find(code.getDelimiterLayer1()) != std::string::npos || username.find("&") != std::string::npos || username.find("=") != std::string::npos || username.find("'") != std::string::npos || username.find("-") != std::string::npos|| username.find("+") != std::string::npos|| username.find(",") != std::string::npos|| username.find("<") != std::string::npos|| username.find(">") != std::string::npos|| username.find("..") != std::string::npos|| username.find("^") != std::string::npos|| username.find(".") != std::string::npos|| username.find(code.getDelimiterLayer1()) != std::string::npos || username.find(code.getDelimiterLayer2()) != std::string::npos || username.find(code.getDelimiterLayer3()) != std::string::npos || username.find(code.getDelimiterLayer4()) != std::string::npos) { // make sure the username is not using the delimiter and a few other characters //this list was taken from https://support.google.com/mail/answer/9211434?hl=en
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        menu.display(1, 1, "The username " + username + " is not valid Please enter a different username.", false, true);
        system("pause");
        logonScreen();
    } else {
        valid = stoi(server.sendToServer(code.cipher("1", username))); // the response for this will either be 1 or 0 as a string (1 meaning the username is valid, 0 meaning the username is taken)
        if (username == newaccountMenu1 || username == newaccountMenu2 || username == newaccountMenu3 || username == newaccountMenu4) valid = 0; //set valid to false if they try to use no in any of the forms
        switch (valid){
            case 0:
            //the username is invalid so restart the process
            menu.display(1, 1, "The username " + username + " is not valid. Please enter a different username.", false, true);
            system("pause");
            menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
            system("cls");
            logonScreen();
            break;
            case 1:{
            //username is valid
            //Menu menu;
            string createAccountCheck;
            menu.display(1, 1, "The username " + username + " is valid and you can use it as your username.", false, false);
            menu.display(1, 2, "Would you like to continue and create an account with this username? (Y/N)", true, false);
            createAccountCheck = menu.yesOrNo();
            if(createAccountCheck == "y" || createAccountCheck == "Y"){
                menu.display(1, 3, "We will now create the account", true, false);
                server.sendToServer(code.cipher("2", username));
                menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
                system("cls");
                account.createPlayer(username); // creates the Character for the user to use in the game

            } else if (createAccountCheck == "N" || createAccountCheck == "n"){
                menu.display(1, 3, "Account will not be created.", false, true);
                system("pause");
                logonScreen();
            } else {
                menu.display(1, 3, "Input not recognized.", false, true);
                system("pause");
                logonScreen();
            }
            break;
            }
        }
    }
}

void Account::newOrExistingAccout(){ // asks and runs through everything for new accounts and if existing brings the user to the logon screen.
    Cipher code;
    //ask the user if they have an account with MightyWarrior game
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    string answer;
    menu.display(1, 1, "Do you have an account yet? (Y/N)", false, false);
    cin >> answer;
    
    //if yes bring them to the logon screen
    if(answer == "y" || answer == "Y"){
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        logonScreen();
    } else if (answer == "n" || answer == "N") {//if no start the signup prossess
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        createNewAccount(); // take user to the function for creatiing accounts 
    } else if (answer == "adminbypass"){
        menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
        system("cls");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// clear out cin buffer
        logonScreen(3);
    } else {
        menu.display(1, 1, "Your answer was not \"Y\" or \"N\".", false, false);
        menu.display(1, 2, "Please try again.", false, true);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear out cin buffer
        system("pause");//pause the window so the user can read the message, then they can press any key to continue.
        newOrExistingAccout(); // take user to beguining of this function again
    }
}

void Account::introStory(int raceChoice, string username){ //this random story generation should probably be moved onto the server.
    menu.display(1,1," ", true, false);//this is require to keep the cls from making the whole screen an odd color.
    system("cls");
    srand((unsigned)time(0)); //takes a seed for the random number based on the time
    int randomStoryChoice;
    randomStoryChoice = (rand()%3)+1;
    menu.display(1, 1, "Welcome to the game Mighty Warriors!", false, false);
    menu.display(1, 2, storyTree(raceChoice, randomStoryChoice), false, true);
    menu.display(1, 6, "", false, true);
    system("pause");
}

string Account::storyTree(int raceChoice, int randomStoryChoice){ // i1 is just a placement value for the actual determing value that should be added to make this more random in chance for story line.
    string output;
    //need to make this all fetched from the server.
    switch(raceChoice){
        case 1: //Human
        {
            switch(randomStoryChoice){
                case 1:
                    output = "in the year 3001, forces of mutants began appearing all over the world. the human race was faced with sudden stife and death. beginning in the city of hooligans, void cat, and his most trusted generals, The Gamer, The Builder, Quak, and Jonny, made their way through the land and destroyed whoever opposed their rule. after they successfully conquered the largest city, humanity had little hope left. they knew that in order to rid the land of this menice, they would have to reach out to the other four races for help. but humanity was prideful. would the other races help?..... your task is to recruit the other four races in the battle against the mutants and to rid the land of radiation.";
                    break;
                case 2:
                    output = "[Story 2 for user to read about their Character based on input about it]";
                    break;
                case 3:
                    output = "[Story 3 for user to read about their Character based on input about it]";
                    break;
                default:
                    output = "[Story default for user to read about their Character based on input about it]";
                }
            break;
        }
        case 2: //Ghost
        {
            switch(randomStoryChoice){
                case 1:
                    output = "3001. the ghosts had been living....? for centuries without worry. they didnt bother anyone, an no one bothered them, without reason of course. that is until the mutants ravaged... the rundown houses and \"empty\" streets of the ghost towns around leaving radiation that even effected and affected the Ghosts. angry and disturbed, the ghosts made their move. they began attacking any camp they could. unfortunatly the radioactive weapons quickly quelled the revolt. desperate for help, the ghosts are sending you to get the other races together. your task is to recruit the other four races in the battle against the mutantsand to rid the land of radiation.";
                    break;
                case 2:
                    output = "[Story 2 for user to read about their Character based on input about it]";
                    break;
                case 3:
                    output = "[Story 3 for user to read about their Character based on input about it]";
                    break;
                default:
                    output = "[Story default for user to read about their Character based on input about it]";
                }
            break;
        }
        case 3: //Dino
        {
            switch(randomStoryChoice){
                case 1:
                    output = "in the year 3001... dinos cant talk. but if they could they'd ask you for help. they are sending you out because the mutants are invading. the four Generals of the mutant army are marching quickly on the dino empire... your task is to recruit the other four races in the battle against the mutants and to rid the land of radiation.";
                    break;
                case 2:
                    output = "[Story 2 for user to read about their Character based on input about it]";
                    break;
                case 3:
                    output = "[Story 3 for user to read about their Character based on input about it]";
                    break;
                default:
                    output = "[Story default for user to read about their Character based on input about it]";
                }
            break;
        }
        case 4: //Elf
        {
            switch(randomStoryChoice){
                case 1:
                    output = "the year 3001. an army of mutants marches on the last stronghold of elves. General Quak and General Jonny have taken all but the best cities, burning and pillaging as they went. the elven race has had its armies reduced by half. the ensuing battle results in a draw. though not a win, it gave hope to the dwindling moral of the elven soldiers. finally there was a way out. the elven commander wasted no time. he is sending you as a emisary to the other races... your task is to recruit the other four races in the battle against the mutants and to rid the land of radiation.";
                    break;
                case 2:
                    output = "[Story 2 for user to read about their Character based on input about it]";
                    break;
                case 3:
                    output = "[Story 3 for user to read about their Character based on input about it]";
                    break;
                default:
                    output = "[Story default for user to read about their Character based on input about it]";
                }
            break;
        }
        case 5: //Dryad
        {
            switch(randomStoryChoice){
                case 1:
                    output = "what year is it? 3001? trees have long slow lives so it can be hard to remember the year... until void cat started to take over the world. one by one, the forests of the dryads were burnt with radiation. in their place the mutants placed a radioactive army. on and on they marched. as the number of dryads dwindled, they did the one thing they vowed they wouldnt... they reached out to the other races. they are sending you. your task is to recruit the other four races in the battle against the mutants and to rid the land of radiation.";
                    break;
                case 2:
                    output = "[Story 2 for user to read about their Character based on input about it]";
                    break;
                case 3:
                    output = "[Story 3 for user to read about their Character based on input about it]";
                    break;
                default:
                    output = "[Story default for user to read about their Character based on input about it]";
                }
            break;
        }
        default:
            output = "Failed story pull";
            break;
    }

    return output;
}