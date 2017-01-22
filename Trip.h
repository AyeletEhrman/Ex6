#ifndef EX3_TRIP_H
#define EX3_TRIP_H
#include "Point.h"
#include "GridPt.h"
#include "Map.h"
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
using namespace std;
using namespace boost::archive;
/**
 * this class creates a trip.
 */
class Trip {
    private:
        int rideId;
        int meters;
        Node* start;
        Node* end;
        Map* map;
        int numPassengers;
        double tariff;
        int startTime;
        deque<Node*>* route;
        pthread_mutex_t* calcMutex;

        friend class boost::serialization::access;
        template<class Archive>
        /**
         * serialize Trip object.
         * @param ar
         * @param version
         */
        void serialize(Archive &ar, const unsigned int version) {
            ar & rideId;
            ar & meters;
            ar & start;
            ar & end;
            ar & numPassengers;
            ar & tariff;
            ar & route;
            ar & startTime;
        }
    public:
        /**
         * constructs a trip.
         * @param rideId the trips id.
         * @param start the starting poin of the trip.
         * @param end the ending point of the trip.
         * @param numPassengers number of passengers for the trip.
         * @param tariff the trips tariff.
         * @param stratTime the starting time of the trip.
         */
        Trip(int rideId, Node* start, Node* end, int numPassengers, double tariff, int stratTime);
        /**
         * default constructer.
         */
        Trip();
        /**
         * destructas the trip..
         */
        ~Trip();
        /**
         * returns the starting point.
         * @return start
         */
        Node* getStart();
        /**
         * sets the starting point of the trip.
         * @param s1 the new starting point.
         */
        void setStart(Node* s1);
        /**
         * returns the ending point.
         * @return end.
         */
        Node* getEnd();
        /**
         * sets the ending point of the trip.
         * @param e1 the new ending point.
         */
        void setEnd(Node* e1);
        /**
         * sets a map for the trip.
         * @param m the map.
         */
        void setMap(Map* m);
        /**
         * returns the number of meters passed in trip.
         * @return meters.
         */
        int getMeters();
        /**
         * sets the number of meters.
         */
        void setMeters();
        /**
         * returns the number of passengers.
         * @return numPassengers.
         */
        int getNumPassengers();
        /**
         * adds to the number of passengers.
         * @param np number of passengers to add.
         */
        void setNumPassengers(int np);
        /**
         * returns the trip tariff.
         * @return tariff.
         */
        double getTariff();
        /**
         * sets the tariff.
         * @param t the new tariff.
         */
        void setTariff(double t);
        /**
         * gets the time for the trip to start
         * @return startTime
         */
        int getStartTime();
        /**
         * sets the route of the trip.
         * @param r the route.
         */
        void setRoute(deque<Node*>* r);
        /**
         * gets the route of the trip.
         * @return the route.
         */
        deque<Node*>* getRoute();
        /**
         * sets the mutex of the current trip.
         * @param mut
         */
        void setMutex(pthread_mutex_t* mut);
        /**
         * calcs the route of the trip.
         * @param trip the trip we're calculaing.
         * @return the route.
         */
        static void* calcRoute(void* trip);
};
#endif //EX3_TRIP_H