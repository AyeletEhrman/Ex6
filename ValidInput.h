//
// Created by ayelet on 22/01/17.
//

#ifndef EX6_VALIDINPUT_H
#define EX6_VALIDINPUT_H

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class ValidInput {

    public:
        static bool greaterEqual(int num, int min);
        static vector<char*>* parseInput(string input);
};


#endif //EX6_VALIDINPUT_H
