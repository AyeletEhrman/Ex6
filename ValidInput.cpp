//
// Created by ayelet on 22/01/17.
//


#include "ValidInput.h"
#include "Luxury.h"


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

bool ValidInput::greaterEqual(double num, double min) {
    return (num >= min);
}

bool ValidInput::isAnumber(const char* check) {
    if (check == NULL) {
        return false;
    }
    string str(check);
    for (int i = 0; i < str.length(); i++) {
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
        string sSign(parsed->at(2));
        if (sSign.length() != 1) {
            return NULL;
        }
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

Trip* ValidInput::validTrip(string input, Map* map) {
    int id, xStart, yStart, xEnd, yEnd, numPassengers, startTime;
    double tariff;

    Point start;
    Point end;

    vector<char*>* parsed = parseInput(input, ",");
    if (parsed->size() != 8) {
        delete parsed;
        return NULL;
    }
    try {
        if (!(isAnumber(parsed->at(0))) || !(isAnumber(parsed->at(1)))
            || !(isAnumber(parsed->at(2))) || !(isAnumber(parsed->at(3)))
            || !(isAnumber(parsed->at(4))) || !(isAnumber(parsed->at(5)))
            || !(isAnumber(parsed->at(7)))) {
            delete parsed;
            return NULL;
        }
        id = stoi(parsed->at(0));
        xStart = stoi(parsed->at(1));
        yStart = stoi(parsed->at(2));
        xEnd = stoi(parsed->at(3));
        yEnd = stoi(parsed->at(4));
        numPassengers = stoi(parsed->at(5));
        tariff = strtod(parsed->at(6), NULL);
        startTime = stoi(parsed->at(7));

        start = Point(xStart, yStart);
        end = Point(xEnd, yEnd);
    } catch(exception e) {
        delete parsed;
        return NULL;
    }
    if (!(greaterEqual(id, 0)) || !(map->isInGrid(start))
        || !(map->isInGrid(end)) || !(greaterEqual(numPassengers, 0))
        || !(greaterEqual(startTime, 1)) || !(greaterEqual(tariff, 0))) {
        delete parsed;
        return NULL;
    }
    GridPt* gStart = map->getPoint(start);
    GridPt* gEnd = map->getPoint(end);
    // creates the new trip.
    delete parsed;
    // creates the new driver and serialize it.
    return new Trip(id, gStart, gEnd, numPassengers, tariff, startTime);
}

Taxi* ValidInput::validTaxi(string input) {
    int id, type;
    char manufacturerSign, colorSign;
    MANUFACTURER manufacturer;
    COLOR color;
    vector<char*>* parsed = parseInput(input, ",");
    if (parsed->size() != 4) {
        delete parsed;
        return NULL;
    }
    try {
        if (!(isAnumber(parsed->at(0))) || !(isAnumber(parsed->at(1)))) {
            delete parsed;
            return NULL;
        }
        id = stoi(parsed->at(0));
        type = stoi(parsed->at(1));
        string sManu(parsed->at(2));
        string sColor(parsed->at(3));
        if ((sManu.length() != 1) || (sColor.length() != 1)) {
            return NULL;
        }
        manufacturerSign = *(parsed->at(2));
        colorSign = *(parsed->at(3));

    } catch(exception e) {
        delete parsed;
        return NULL;
    }
    if (!(greaterEqual(id, 0))) {
        delete parsed;
        return NULL;
    }
    // assigns the cars manufacturer.
    switch (manufacturerSign) {
        case 'H':
            manufacturer = HONDA;
            break;
        case 'S':
            manufacturer = SUBARO;
            break;
        case 'T':
            manufacturer = TESLA;
            break;
        case 'F':
            manufacturer = FIAT;
            break;
        default:
            return NULL;
    }
    // assigns the cars color.
    switch (colorSign) {
        case 'R':
            color = RED;
            break;
        case 'B':
            color = BLUE;
            break;
        case 'G':
            color = GREEN;
            break;
        case 'P':
            color = PINK;
            break;
        case 'W':
            color = WHITE;
            break;
        default:
            return NULL;
    }
    // assigns the taxis type.
    if (type == 1) {
        return new Taxi(id, manufacturer, color);
    } else if (type == 2) {
        return new Luxury(id, manufacturer, color);
    } else {
        return NULL;
    }
}