//
// Created by ayelet on 22/01/17.
//

#ifndef EX6_VALIDINPUT_H
#define EX6_VALIDINPUT_H

#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include "Driver.h"

using namespace std;

class ValidInput {

    public:
        static bool greaterEqual(double num, double min);
        static vector<char*>* parseInput(string input, string tokens);
        static bool isAnumber(const char* check);
        static Driver* validClient(string input);
        static bool pointIsValid(string input, Point maxSize, string token);
        static Point validPoint(string input);
        static Trip* validTrip(string input, Map* map);
        static Taxi* validTaxi(string input);

};

#endif //EX6_VALIDINPUT_H
