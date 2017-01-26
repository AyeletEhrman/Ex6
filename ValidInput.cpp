#include "ValidInput.h"

vector<char*>* ValidInput::parseInput(string input, string tokens) {
    vector<char*>* parsed = new vector<char*>;
    char* str = (char*)input.data();
    char* splits;
    // get the first part of the input.
    splits = strtok(str, tokens.data());
    // until we finish going over the input.
    while (splits != NULL) {
        // add the current split to the parsed vec.
        parsed->push_back(splits);
        splits = strtok (NULL, tokens.data());
    }
    // return the parsed input.
    return parsed;
}

bool ValidInput::greaterEqual(double num, double min) {
    // return true if num is >= from min.
    return (num >= min);
}

bool ValidInput::isAnumber(const char* check) {
    if (check == NULL) {
        return false;
    }
    // cnvert to string.
    string str(check);
    // go over the sring.
    for (int i = 0; i < str.length(); i++) {
        // if the curr char of string isn't a digit.
        if (!isdigit(str.at(i))) {
            // check is not a number.
            return false;
        }
    }
    // check is a number.
    return true;
}

Driver* ValidInput::validClient(string input) {
    int id = -1, age = -1, experience = -1, cabId = -1;
    char statusSign;
    MaritalStatus status;
    // check if the input ends with ",".
    if (input.at(input.length() - 1) == ',') {
        return NULL;
    }
    // parse the input with "," token.
    vector<char*>* parsed = parseInput(input, ",");
    // check if we did'nt get the right amount of values for driver.
    if (parsed->size() != 5) {
        delete parsed;
        return NULL;
    }
    try {
        // check if we got all the numbers values for id, age, exp, cabId.
        if (!(isAnumber(parsed->at(0))) || !(isAnumber(parsed->at(1)))
            || !(isAnumber(parsed->at(3))) || !(isAnumber(parsed->at(4)))) {
            delete parsed;
            return NULL;
        }
        // puts the values in place.
        id = atoi(parsed->at(0));
        age = atoi(parsed->at(1));
        string sSign(parsed->at(2));
        // only one char for the status.
        if (sSign.length() != 1) {
            delete parsed;
            return NULL;
        }
        statusSign = *(parsed->at(2));
        experience = atoi(parsed->at(3));
        cabId = atoi(parsed->at(4));
    } catch(exception e) {
        delete parsed;
        return NULL;
    }
    // checks that the range of id, age, exp, cabId are correct.
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
            status =t MARRIED;
            break;
        case 'D':
            status = DIVORCED;
            break;
        case 'W':
            status = WIDOWED;
            break;
        default:
            // status is invalid.
            delete parsed;
            return NULL;
    }
    delete parsed;
    // creates the new driver and serialize it.
    return new Driver(id, age, status, cabId, experience);
}

bool ValidInput::pointIsValid(string input, Point maxSize, string token) {
    int x, y;
    // check if the input ends with ",".
    if (input.at(input.length() - 1) == ',') {
        return false;
    }
    vector<char*>* parsed = parseInput(input, token);
    // check if we did'nt get the right amount of values for point.
    if (parsed->size() != 2) {
        delete parsed;
        return false;
    }
    try {
        // checks the vals for x, y are numbers.
        if (!(isAnumber(parsed->at(0))) || !(isAnumber(parsed->at(1)))) {
            delete parsed;
            return false;
        }
        // assign values for x,y.
        x = atoi(parsed->at(0));
        y = atoi(parsed->at(1));
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
    // parse input with "," token.
    vector<char*>* parsed = parseInput(input, " ,");
    // assigns the x, y value.
    x = atoi(parsed->at(0));
    y = atoi(parsed->at(1));
    delete parsed;
    // returns the point.
    return Point(x,y);
}

Trip* ValidInput::validTrip(string input, Map* map) {
    int id, xStart, yStart, xEnd, yEnd, numPassengers, startTime;
    double tariff;
    Point start;
    Point end;
    // if end of input is comma
    if (input.at(input.length() - 1) == ',') {
        return NULL;
    }
    // get the parsed input
    vector<char*>* parsed = parseInput(input, ",");
    // we excpect to get 8 args
    if (parsed->size() != 8) {
        delete parsed;
        return NULL;
    }
    // we get all the args according to their type and check them.
    try {
        if (!(isAnumber(parsed->at(0))) || !(isAnumber(parsed->at(1)))
            || !(isAnumber(parsed->at(2))) || !(isAnumber(parsed->at(3)))
            || !(isAnumber(parsed->at(4))) || !(isAnumber(parsed->at(5)))
            || !(isAnumber(parsed->at(7)))) {
            delete parsed;
            return NULL;
        }
        id = atoi(parsed->at(0));
        xStart = atoi(parsed->at(1));
        yStart = atoi(parsed->at(2));
        xEnd = atoi(parsed->at(3));
        yEnd = atoi(parsed->at(4));
        numPassengers = atoi(parsed->at(5));
        tariff = strtod(parsed->at(6), NULL);
        startTime = atoi(parsed->at(7));
        start = Point(xStart, yStart);
        end = Point(xEnd, yEnd);
    } catch(exception e) {
        delete parsed;
        return NULL;
    }
    // check more validation terms.
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
    // if the input ends with a comma
    if (input.at(input.length() - 1) == ',') {
        return NULL;
    }
    // get the parsed input
    vector<char*>* parsed = parseInput(input, ",");
    // we expect to get 4 args
    if (parsed->size() != 4) {
        delete parsed;
        return NULL;
    }
    // we get all the args according to their type and check them.
    try {
        if (!(isAnumber(parsed->at(0))) || !(isAnumber(parsed->at(1)))) {
            delete parsed;
            return NULL;
        }
        id = atoi(parsed->at(0));
        type = atoi(parsed->at(1));
        string sManu(parsed->at(2));
        string sColor(parsed->at(3));
        if ((sManu.length() != 1) || (sColor.length() != 1)) {
            delete parsed;
            return NULL;
        }
        manufacturerSign = *(parsed->at(2));
        colorSign = *(parsed->at(3));
    } catch(exception e) {
        delete parsed;
        return NULL;
    }
    // id should be positive.
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
            delete parsed;
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
            delete parsed;
            return NULL;
    }
    delete parsed;
    // assigns the taxis type.
    if (type == 1) {
        return new Taxi(id, manufacturer, color);
    } else if (type == 2) {
        return new Luxury(id, manufacturer, color);
    } else {
        return NULL;
    }
}
