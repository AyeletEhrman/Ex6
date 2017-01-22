#ifndef EX3_TAXICENTER_H
#define EX3_TAXICENTER_H
#include <vector>
#include "Driver.h"
#include <pthread.h>
using namespace std;
/**
 * this class creates a Taxi Center.
 * the Taxi center knows how tho send cabs to passengers.
 */
class TaxiCenter {
    private:
        vector<Driver*> drivers;
        vector<Taxi*> taxis;
        vector<Trip*> trips;
        vector<pthread_t> calcRouteThreads;
        pthread_mutex_t calcMutex;
        Map* map;
        int time;
    public:
        /**
         * constructs a TaxiCenter.
         */
        TaxiCenter(Map* map1);
        /**
         * defult constructor for the TaxiCenter
         * @return
         */
        TaxiCenter();
        /**
         * destructs a TaxiCenter.
         */
        ~TaxiCenter();
        /**
         * recievs calls from customers.
         */
        void answerCalls();
        /**
         * sends a Taxi to a custemor.
         */
        void sendTaxi();
        /**
         * keep driving taxis on their trip.
         */
        void continueDriving();
        /**
         * returns the taxi centers map.
         * @return the map.
         */
        Map* getMap();
        /**
         * adds a driver to the center.
         * @param d th new driver.
         */
        void addDriver(Driver* d);
        /**
         * adds a taxi to the center.
         * @param t th new taxi.
         */
        void addTaxi(Taxi* t);
        /**
         * adds a trip to the center.
         * @param tr th new trip.
         */
        void addTrip(Trip* tr);
        /**
         * returns the drivers of the taxi center.
         * @return drivers.
         */
        vector<Driver*> getDrivers();
        /**
         * returns the taxis of the taxi center.
         * @return taxis.
         */
        vector<Taxi*> getTaxis();
        /**
         * returns the trips of the taxi center.
         * @return trips.
         */
        vector<Trip*> getTrips();
        /**
         * assigns a cab to a driver.
         * @param driver the driver that the cab will be assigned to.
         */
        void assignCab(Driver* driver);
        /**
         * moves clock
         */
        void setTime();
        /**
         * gets the current time
         * @return current time
         */
        int getTime();
        /**
         * calcs a trip's route.
         * @param trip the trip for calculation.
         */
        void calcTripRoute(Trip* trip);
};
#endif //EX3_TAXICENTER_H