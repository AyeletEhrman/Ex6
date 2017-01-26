#ifndef EX6_VALIDINPUT_H
#define EX6_VALIDINPUT_H
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include "Driver.h"
#include "Luxury.h"
using namespace std;
/**
 * ValidInput is a class with static funcs that check if input is valid.
 */

class ValidInput {
    public:
        /**
         * parses input by some given tokens.
         * @param input the input to parse.
         * @param tokens the tokens to parse with.
         * @return the parsed input.
         */
        static vector<char*>* parseInput(string input, string tokens);
        /**
         * checks if a given num is >= min num.
         * @param num the number to check.
         * @param min the minimum value for num.
         * @return true if num >= min, false otherwise.
         */
        static bool greaterEqual(double num, double min);
        /**
         * checks if a given string is a number.
         * @param check the string to check.
         * @return true if check is a number, false otherwise.
         */
        static bool isAnumber(const char* check);
        /**
         * parses an input to a driver if valid.
         * @param input the drivers input.
         * @return the parsed driver or NULL if the input is invalid.
         */
        static Driver* validClient(string input);
        /**
         * checks if the points input is valid.
         * @param input the points input.
         * @param maxSize the max size for the point.
         * @param token the token to split the point with.
         * @return true if the input is valid, false otherwise.
         */
        static bool pointIsValid(string input, Point maxSize, string token);
        /**
         * parses a input to a point if valid.
         * @param input  the point's input.
         * @return  the parsed point or NULL if the input is invalid.
         */
        static Point validPoint(string input);
        /**
         * parses a input to a trip if valid.
         * @param input the trip's input.
         * @param map the map that the trip will be in.
         * @return the parsed trip or NULL if the trip's input is invalid.
         */
        static Trip* validTrip(string input, Map* map);
        /**
         * parses a input to a taxi if valid.
         * @param input the taxi's input.
         * @return the parsed taxi or NULL if the taxi's input is invalid.
         */
        static Taxi* validTaxi(string input);
};

#endif //EX6_VALIDINPUT_H
