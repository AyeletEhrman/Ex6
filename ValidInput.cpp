//
// Created by ayelet on 22/01/17.
//


#include "ValidInput.h"

vector<char*>* ValidInput::parseInput(string input) {
    vector<char*>* parsed = new vector<char*>;
    char* str = new char[input.length() + 1];
    strcpy(str, input.c_str());
    char* splits;
    splits = strtok(str, ",");

    while (splits != NULL) {
        parsed->push_back(splits);
        splits = strtok (NULL, ",");
    }
    return parsed;
}

bool ValidInput::greaterEqual(int num, int min) {
    return (num >= min);
}