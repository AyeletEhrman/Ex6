#include "Trip.h"
#include "Bfs.h"

Trip::Trip(int id, Node* s, Node* e, int np, double t, int st) {
    rideId = id;
    meters = 0;
    start = s;
    end = e;
    numPassengers = np;
    tariff = t;
    startTime = st;
    route = NULL;
    map = NULL;
}
Trip::Trip() {
    rideId = 0;
    meters = 0;
    start = NULL;
    end = NULL;
    numPassengers = 0;
    tariff = 0;
    startTime = 0;
    route = NULL;
    map = NULL;
}
Trip::~Trip() {
    delete route;
}

Node* Trip::getStart() {
    return start;
}

void Trip::setStart(Node* s1) {
    start = s1;
}

void Trip::setEnd(Node* e1) {
    end = e1;
}

Node* Trip::getEnd() {
    return end;
}

void Trip::setMap(Map* m) {
    map = m;
}

int Trip::getMeters() {
    return meters;
}

void Trip::setMeters() {
    meters++;
}

int Trip::getNumPassengers() {
    return numPassengers;
}

void Trip::setNumPassengers(int np) {
    numPassengers = np;
}

double Trip::getTariff() {
    return tariff;
}

void Trip::setTariff(double t) {
    tariff = t;
}

int Trip::getStartTime() {
    return startTime;
}

void Trip::setRoute(deque<Node*>* r) {
    route = r;
}

deque<Node*>* Trip::getRoute() {
    return route;
}

void Trip::setMutex(pthread_mutex_t* mut) {
    calcMutex = mut;
}

void* Trip::calcRoute(void* trip) {
    // the first thread locks the mutex and goes in.
    pthread_mutex_lock(((Trip*)trip)->calcMutex);

    Bfs b = Bfs();
    Node* start = (GridPt*)((Trip*)trip)->getStart();
    Node* end = (GridPt*)((Trip*)trip)->getEnd();
    ((Trip*)trip)->map->initialize();
    start->setPassed();
    // sets the route for the trip.
    ((Trip*)trip)->setRoute(b.bfs(start, end));

    // unlocks the mutex.
    pthread_mutex_unlock(((Trip*)trip)->calcMutex);
}