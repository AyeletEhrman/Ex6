//
// Created by ayelet on 22/01/17.
//


#include "ValidInput.h"


vector<char*>* ValidInput::parseInput(string input, string tokens) {
    vector<char*>* parsed = new vector<char*>;
    char* str = new char[input.length() + 1];
    strcpy(str, input.c_str());
    char* splits;
    splits = strtok(str, tokens.data());

    while (splits != NULL) {
        parsed->push_back(splits);
        splits = strtok (NULL, tokens.data());
    }
    return parsed;
}

bool ValidInput::greaterEqual(int num, int min) {
    return (num >= min);
}

bool ValidInput::isAnumber(const char* check) {
    if (check == NULL) {
        return false;
    }
    string str(check);
    for (int i = 0; i < (str.length() - 1); i++) {
        if (!isdigit(str.at(i))) {
            return false;
        }
    }
    return true;

}

Driver* ValidInput::validClient(string input) {
    int id = -1, age = -1, experience = -1, cabId = -1;
    char statusSign;
    MaritalStatus status;

    vector<char*>* parsed = parseInput(input, ",");
    if (parsed->size() != 5) {
        delete parsed;
        return NULL;
    }
    try {
        if (!(isAnumber(parsed->at(0))) || !(isAnumber(parsed->at(1)))
            || !(isAnumber(parsed->at(3))) || !(isAnumber(parsed->at(4)))) {
            delete parsed;
            return NULL;
        }
        id = stoi(parsed->at(0));
        age = stoi(parsed->at(1));
        statusSign = *(parsed->at(2));
        experience = stoi(parsed->at(3));
        cabId = stoi(parsed->at(4));
    } catch(exception e) {
        delete parsed;
        return NULL;
    }
    if (!(greaterEqual(id, 0)) || !(greaterEqual(age, 0))
          || !(greaterEqual(experience, 0)) || !(greaterEqual(cabId, 0))) {
        delete parsed;
        return NULL;
    }
    // assigns the right status for the driver.
    switch (statusSign) {
        case 'S':
            status = SINGLE;
            break;
        case 'M':
            status = MARRIED;
            break;
        case 'D':
            status = DIVORCED;
            break;
        case 'W':
            status = WIDOWED;
            break;
        default:
            delete parsed;
            return NULL;;
    }


    cout << "valid driver:) " << endl;

    delete parsed;
    // creates the new driver and serialize it.
    return new Driver(id, age, status, cabId, experience);
}

bool ValidInput::pointIsValid(string input, Point maxSize, string token) {
    int x, y;
    vector<char*>* parsed = parseInput(input, token);
    if (parsed->size() != 2) {
        delete parsed;
        return false;
    }
    try {
        if (!(isAnumber(parsed->at(0))) || !(isAnumber(parsed->at(1)))) {
            delete parsed;
            return false;
        }
        x = stoi(parsed->at(0));
        y = stoi(parsed->at(1));
    } catch(exception e) {
        delete parsed;
        return false;
    }
    // check positive
    if (!(greaterEqual(x, 0)) || !(greaterEqual(y, 0))
        || (greaterEqual(x, maxSize.getX())) || (greaterEqual(y, maxSize.getY()))) {
        delete parsed;
        return false;
    }
    delete parsed;
    return true;
}
Point ValidInput::validPoint(string input) {
    int x, y;
    vector<char*>* parsed = parseInput(input, " ,");
    x = stoi(parsed->at(0));
    y = stoi(parsed->at(1));
    return Point(x,y);
}