#ifndef EX2_DRIVER_H
#define EX2_DRIVER_H
#include <iostream>
#include "Taxi.h"
#include "Point.h"
#include "Trip.h"
#include "GridPt.h"
#include "Bfs.h"
#include "Map.h"
#include <boost/serialization/deque.hpp>
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
 * This class creates a cab Driver.
 */
// Marital status.
enum MaritalStatus {
    SINGLE, MARRIED, DIVORCED, WIDOWED
};
class Driver {
    private:
        int id, age, experience, customers, cabId;
        MaritalStatus status;
        double avSatisfaction;
        Taxi* cab;
        Map* map;
        bool driving;
        bool newTrip;
        GridPt* firstLocation;
        GridPt* location;
        vector<Node*>* route;
        Trip* trip;
        int prevDrivingTime;

        friend class boost::serialization::access;
        template<class Archive>
        /**
         * seralize a driver object.
         * @param ar
         * @param version
         */
        void serialize(Archive &ar, const unsigned int version) {
            ar & id;
            ar & age;
            ar & experience;
            ar & customers;
            ar & cabId;
            ar & status;
            ar & avSatisfaction;
            ar & cab;
            ar & driving;
            ar & firstLocation;
            ar & location;
            ar & newTrip;
            ar & route;
            ar & prevDrivingTime;
        }
    public:
        /**
         * constructs a Driver.
         * @param id1 drivers id
         * @param age1 drivers age
         * @param status1 drivers marital status
         * @param cabInfo1 drivers cab info
         * @param experience1 drivers driving experience.
         */
        Driver(int id1, int age1, MaritalStatus status1, int cabId1, int experience1);
        /**
         * default contructor of driver.
         */
        Driver();
        /**
         * destructs driver.
         */
        ~Driver();
        /**
         * returns the drivers id.
         * @return id
         */
        int getId();
        /**
         * sets the drivers age.
         * @param a the new age.
         */
        void setAge(int a);
        /**
         * returns the drivers age.
         * @return age
         */
        int getAge();
        /**
         * sets the drivers marital status.
         * @param st the new status.
         */
        void setStatus(MaritalStatus st);
        /**
         * returns the drivers marital status.
         * @return the status.
         */
        MaritalStatus getStatus();
        /**
         * sets the drivers driving experience.
         * @param exp the new experience.
         */
        void setExperience(int exp);
        /**
         * returns the drivers years of experience.
         * @return years of experience.
         */
        int getExperience();
        /**
         * sets the average satisfaction.
         * @param score the score to add for the avarage.
         */
        void setSatisfaction(int score);
        /**
         * returns the average satisfaction.
         * @return satisfaction.
         */
        double getSatisfaction();
        /**
         * gets the drivers cab id
         * @return the cab id
         */
        int getCabId();
        /**
         * sets the drivers cab info.
         * @param t the cab.
         */
        void setCab(Taxi* t);
        /**
         * returns the cab info.
         * @return the cab.
         */
        Taxi* getCab();
        /**
         * adds customers to driver.
         * @param c num of customers to add.
         */
        void addCustomers(int c);
        /**
         * returns the number of customers.
         * @return num of customers.
         */
        int getNumCustomers();
        /**
         * sets a map for a driver.
         * @param m the map.
         */
        void setMap(Map* m);
        /**
         * return drivers location
         * @return location.
         */
        GridPt* getLocation();
        /**
         * set the loction of driver.
         * @param loc the location point
         */
        void setLocation(GridPt* loc);
        /**
         * assign a trip to the driver.
         * @param trip the trip for the driver
         */
        void setTrip(Trip* trip);
        /**
         * get the driver trip.
         * @return trip that assigned to driver
         */
        Trip* getTrip();
        /**
         * sets the route of driver.
         * @param route1 route for driver
         */
        void setRoute();//deque<Node*>* route1);
        /**
         * gets the route from the driver
         * @return the route to drive
         */
        vector<Node*>* getRoute();
        /**
         * drives the car.
         */
        void drive();
        /**
         * checks if a driver is in the midddle of driving.
         * @return true if driving, false otherwise.
         */
        bool isDriving();
        /**
         * sets the driving status.
         */
        void setDriving();
        /**
         * return if driver just got new trip or not.
         * @return true or false
         */
        bool gotNewTrip();
        /**
         * change the bool newtrip of driver.
         */
        void setNewTrip();
        /**
         * sets the time of previous driving time.
         * @param time
         */
        void setTime(int time);
        /**
         * gets the prevtime of driver
         * @return prevDrivingTime
         */
        int getPrevTime();
};
#endif //EX2_DRIVER_H
