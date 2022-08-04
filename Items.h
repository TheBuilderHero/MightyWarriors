#include <iostream>
#include <string>

#pragma once
class Items{
    private:
        //We possibly won't need these data values saved?
        int weaponNumber;
        std::string weaponName;
        int physicalDamage, magicDamage, psychicDamage;
        int size; //size of the item in the inventory, in case we want to limit how much you can carry

        //Trying a different method for data retrieval; all values stored in arrays so code is super clean
        int ALL_WEAPONS = 50;
        std::string allWeaponNames[50] =         {"Empty", "Sword", "Bow", "Dagger", "Fire Rune", "Wind Rune", "Ice Spike", "Black Book", "Empty", "Empty",
                                            "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty",
                                            "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty",
                                            "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty",
                                            "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty",};
        int allWeaponPhysicalDamage[50] =   {0, 20, 12, 12, 3, 6, 16, 8, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
        int allWeaponMagicDamage[50] =      {0, 0, 0, 0, 18, 14, 36, 8, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
        int allWeaponPsychicDamage[50] =    {0, 0, 0, 0, 0, 0, 0, 5, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
        int allWeaponSize[50] =             {0, 2, 2, 1, 1, 1, 2, 1, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};

    public:
        //getters... We don't need setters technically
        std::string getWeaponName(int number);
        int getPhysicalDamage(int number);
        int getMagicDamage(int number);
        int getPsychicDamage(int number);

        int getWeaponNumber(std::string weaponName);
};
