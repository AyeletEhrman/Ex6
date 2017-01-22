#include "TaxiCenter.h"

TaxiCenter::TaxiCenter(Map* map1) {
    map = map1;
    time = 0;
    pthread_mutex_init(&calcMutex, 0);
}

TaxiCenter::TaxiCenter() {
    map = NULL;
    time = 0;
    pthread_mutex_init(&calcMutex, 0);
}

TaxiCenter::~TaxiCenter() {
    // deletes the drivers.
    while (drivers.size() != 0) {
        delete drivers.front();
        drivers.erase(drivers.begin());
    }
    // deletes the taxis.
    while (taxis.size() != 0) {
        delete taxis.front();
        taxis.erase(taxis.begin());
    }
    // deletes the trips.
    while (trips.size() != 0) {
        delete trips.front();
        trips.erase(trips.begin());
    }
    pthread_mutex_destroy(&calcMutex);
}

void TaxiCenter::answerCalls() {
}

void TaxiCenter::sendTaxi() {
    int driverCounter = 0;
    Driver* currDriver;
    Trip* currTrip;
    GridPt *start, *end;
    int tripIndex = 0;
    // goes over the drivers, and drives them.
    while (!(trips.empty())  && (trips.size() > tripIndex)) {
        // gets the first trip.
        currTrip = trips.at(tripIndex);
        if (currTrip->getStartTime() == time) {
            for (int j = 0; j < drivers.size(); j++) {
                // start point of the trip.
                start = map->getPoint(((GridPt*)currTrip->getStart())->getPt());//*(currTrip->getStart()));
                // end point of the trip.
                end = map->getPoint((((GridPt*)currTrip->getEnd())->getPt()));//*(currTrip->getEnd())
                if ((((GridPt*)drivers.at(j)->getLocation()) == start)
                    && !(drivers.at(j)->isDriving())) {
                    // gets the first driver.
                    currDriver = drivers.at(j);
                    // waits for trip to be calculated.
                    pthread_join (calcRouteThreads.at(tripIndex), NULL);
                   // sets the drivers trip.
                    currDriver->setTrip(currTrip);
                    currDriver->setNewTrip();
                    currDriver->setRoute();

                    // pops the start of the route.
                    currDriver->getRoute()->pop_back();
                    // next time the driver will know to drive.
                    currDriver->setDriving();

                    // deletes trip from taxi center.
                    delete trips.at(tripIndex);
                    trips.erase(trips.begin() + tripIndex);
                    driverCounter++;
                    break;
                }
            }
        } else {
            tripIndex++;
        }
        if (driverCounter >= drivers.size()) {
            break;
        }
    }
}
void TaxiCenter::continueDriving() {
    for (int i = 0; i < drivers.size(); i++) {
        // if the driver needs to drive.
        if (drivers.at(i)->isDriving()) {
            // the driver drives one step.
            drivers.at(i)->drive();
        }
    }
}

Map* TaxiCenter::getMap() {
    return map;
}

void TaxiCenter::addDriver(Driver* d) {
    // adds the driver to the back of the list.
    drivers.push_back(d);
}

void TaxiCenter::addTaxi(Taxi* t) {
    // adds the taxi to the back of the list.
    taxis.push_back(t);
}

void TaxiCenter::addTrip(Trip* tr) {
    // adds the trip to the back of the list.
    trips.push_back(tr);
}

vector<Driver*> TaxiCenter::getDrivers() {
    return drivers;
}

vector<Taxi*> TaxiCenter::getTaxis() {
    return taxis;
}

vector<Trip*> TaxiCenter::getTrips() {
    return trips;
}

void TaxiCenter::assignCab(Driver* driver) {
    // goes over the taxis.
    for (int i = 0; i < taxis.size(); i++) {
        if (taxis.at(i)->getId() == driver->getCabId()) {
            // sets the cab to the driver.
            driver->setCab(taxis.at(i));
            break;
        }
    }
}

void TaxiCenter::setTime() {
    time++;
}

int TaxiCenter::getTime() {
    return time;
}

void TaxiCenter::calcTripRoute(Trip* trip) {
    int vecSize = calcRouteThreads.size();
    calcRouteThreads.resize(vecSize + 1);
    // sets the map of the trip.
    trip->setMap(map);
    trip->setMutex(&calcMutex);
    // adds the trip to the center.
    addTrip(trip);
    // thread for calculating the trip.
    pthread_create(&(calcRouteThreads.at(vecSize)), NULL, trip->calcRoute, (void*)trip);
}
