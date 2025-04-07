#pragma once 

#include <iostream>
#include <limits>
#include <algorithm>

using namespace std; 

// Current frequency of the arm and gondola motors
void getCurrentArmFrequency(int currentArmyFrequency);
void getCurrentGondolaFrequency(int currentGondolaFrequency);
int RampUp(int currentArmFrequency, int currentGondolaFrequency);
unsigned long getGondolaInterval(int currentGondolaFrequency);
unsigned long getArmInterval(int currentArmFrequency);
