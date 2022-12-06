// DiceRoller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

struct Characteristics
{
    int str;
    int t;
    int sv;
    int ap;
    bool isRapid;
    bool isShock;
    bool isShred;
    bool isPower;
};

Characteristics ourCharacteristics;

bool weaponIsWounded(int str, int t, int roll)
{
    return (str >= t * 2 && roll >= 2) || (str > t && roll >= 3) || (str == t && roll >= 4) || (str < t && roll >= 5) ||
           (str <= t / 2 && roll >= 6);
}

int Calculation(int rapidRoll, int critRoll, std::vector<int> woundRolls, std::vector<int> saveRolls)
{
    int numberOfShots = 1;
    int tempAp = ourCharacteristics.ap;
    if (ourCharacteristics.isRapid)
    {
        if (rapidRoll == 6)
        {
            numberOfShots = 3;
        }
        else if (rapidRoll > 3)
        {
            numberOfShots = 2;
        }
    }
    int tempResult = 0;
    if (critRoll == 6)
    {
        if (ourCharacteristics.isShred)
        {
            tempAp--;
        }
        if (ourCharacteristics.isPower)
        {
            tempAp = -7;
        }
        if (ourCharacteristics.isShock)
        {
            if (numberOfShots == 1)
            {
                return 1;
            }
            else
            {
                numberOfShots--;
                tempResult++;
            }
        }
    }
    int S = ourCharacteristics.str;
    int T = ourCharacteristics.t;
    int totalSave = ourCharacteristics.sv - tempAp;
    for (int i = 0; i < numberOfShots; i++)
    {
        int WOUND_ROLL = woundRolls[i];
        if (weaponIsWounded(S, T, WOUND_ROLL) && saveRolls[i] < totalSave)
        {
            tempResult++;
        }
    }
    return tempResult;
}

int main()
{
    int coutZeros = 0;
    int countOnes = 0;
    int countTwos = 0;
    int countThirds = 0;

    ourCharacteristics.str = 4;
    ourCharacteristics.t = 3;
    ourCharacteristics.sv = 4;
    ourCharacteristics.ap = -1;
    ourCharacteristics.isRapid = true;
    ourCharacteristics.isShock = false;
    ourCharacteristics.isShred = false;
    ourCharacteristics.isPower = false;

    for (int rapidRoll = 1; rapidRoll < 7; rapidRoll++)
        for (int critRoll = 1; critRoll < 7; critRoll++)
            for (int firstWoundRoll = 1; firstWoundRoll < 7; firstWoundRoll++)
                for (int secondWoundRoll = 1; secondWoundRoll < 7; secondWoundRoll++)
                    for (int thirdWoundRoll = 1; thirdWoundRoll < 7; thirdWoundRoll++)
                    {
                        std::vector<int> woundRolls = {firstWoundRoll, secondWoundRoll, thirdWoundRoll};
                        for (int firstSaveRoll = 1; firstSaveRoll < 7; firstSaveRoll++)
                            for (int secondSaveRoll = 1; secondSaveRoll < 7; secondSaveRoll++)
                                for (int thirdSaveRoll = 1; thirdSaveRoll < 7; thirdSaveRoll++)
                                {
                                    std::vector<int> saveRolls = {firstSaveRoll, secondSaveRoll, thirdSaveRoll};
                                    int result = Ñalculation(rapidRoll, critRoll, woundRolls, saveRolls);
                                    if (result == 0)
                                    {
                                        coutZeros++;
                                    }
                                    if (result == 1)
                                    {
                                        countOnes++;
                                    }
                                    if (result == 2)
                                    {
                                        countTwos++;
                                    }
                                    if (result == 3)
                                    {
                                        countThirds++;
                                    }
                                }
                    }

    int sum = coutZeros + countOnes + countTwos + countThirds;
    std::cout << "veroiatnost is\n";
    std::cout << "0 " << static_cast<double>(coutZeros) / sum << "\n";
    std::cout << "1 " << static_cast<double>(countOnes) / sum << "\n";
    std::cout << "2 " << static_cast<double>(countTwos) / sum << "\n";
    std::cout << "3 " << static_cast<double>(countThirds) / sum << "\n";
}
