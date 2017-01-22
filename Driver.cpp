#include "Driver.h"

Driver::Driver(int id1, int age1, MaritalStatus status1, int cabId1, int experience1) {
    id = id1;
    age = age1;
    status = status1;
    cabId = cabId1;
    experience = experience1;
    map = NULL;
    avSatisfaction = 0;
    customers = 0;
    driving = false;
    firstLocation = new GridPt(Point(0,0));
    location = NULL;
    route = new vector<Node*>;
    newTrip = false;
    trip = NULL;
    prevDrivingTime = -1;
}

Driver::Driver() {
}

Driver::~Driver() {
    delete firstLocation;
    delete route;
}

int Driver::getId() {
    return id;
}

void Driver::setAge(int a) {
    age = a;
}

int Driver::getAge() {
    return age;
}

void Driver::setStatus(MaritalStatus st) {
    status = st;
}

MaritalStatus Driver::getStatus() {
    return status;
}

void Driver::setExperience(int exp) {
    experience = exp;
}

int Driver::getExperience() {
    return experience;
}

void Driver::setSatisfaction(int score) {
    avSatisfaction = ((avSatisfaction * (getNumCustomers() - 1)+ score) / getNumCustomers());
}

double Driver::getSatisfaction() {
    return avSatisfaction;
}

int Driver::getCabId() {
    return cabId;
}

void Driver::setCab(Taxi* t) {
    cab = t;
}

Taxi* Driver::getCab() {
    return cab;
}

void Driver::addCustomers(int c) {
    customers += c;
}

int Driver::getNumCustomers() {
    return customers;
}

void Driver::setMap(Map* m) {
    map = m;
    location = map->getPoint(((GridPt(Point(0,0))).getPt()));
}

GridPt* Driver::getLocation() {
    if (location == NULL) {
        return firstLocation;
    }
    return location;
}

void Driver::setLocation(GridPt* loc) {
    location = loc;
}

void Driver::setTrip(Trip* trip1) {
    trip = trip1;
}

Trip* Driver::getTrip() {
    return trip;
}

vector<Node*>* Driver::getRoute() {
    return route;
}

void Driver::setRoute() {
    for (int i = trip->getRoute()->size() - 1; i >= 0 ; i--) {
        route->push_back(trip->getRoute()->at(i));
    }
}

void Driver::drive() {
    int i = 0;
    // regular taxi goes one block and luxury two blocks
    while (i < cab->getType()) {
        if (!route->empty()) {
            location = map->getPoint(((GridPt*)(route->back()))->getPt());
            route->pop_back();
            cab->setKm(0.001);
        }
        i++;
    }
    if (route->empty()) {
        // stop driving.
        setDriving();
    }
}

bool Driver::isDriving() {
    return driving;
}

void Driver::setDriving() {
    driving = !driving;
}

bool Driver::gotNewTrip() {
    return newTrip;
}

void Driver::setNewTrip() {
    newTrip = !newTrip;
}

void Driver::setTime(int time) {
    prevDrivingTime = time;
}

int Driver::getPrevTime() {
    return prevDrivingTime;
}