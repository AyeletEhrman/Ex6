#ifndef EX3_PASSENGER_H
#define EX3_PASSENGER_H
#include "Point.h"
#include <cstdlib>
/**
 * this class creates a passenger that needs a ride.
 */
class Passenger {
    private:
        Point source;
        Point destination;
    public:
        /**
         * constructs a passenger.
         * @param s the source of the passenger.
         * @param d the destination of the passeger.
         */
        Passenger(Point s, Point d);
        /**
         * destructs the passenger.
         */
        ~Passenger();
        /**
         * returns the source of the passenger.
         * @return source.
         */
        Point getSource();
        /**
         * returns the destionation pf the passenger.
         * @return destionation.
         */
        Point getDestination();
        /**
         * sets the passengers source.
         * @param s the new source.
         */
        void setSource(Point s);
        /**
         * sets the destination of th epasseger.
         * @param d the new destionation.
         */
        void setDestination(Point d);
        /**
         * gets the score that the passenger gave the driver.
         * @return the score.
         */
        int getScore();
};

#endif //EX3_PASSENGER_H