#include "Passenger.h"

Passenger::Passenger(Point s, Point d) {
    source = s;
    destination = d;
}

Passenger::~Passenger() {
}

Point Passenger::getSource() {
    return source;
}

Point Passenger::getDestination() {
    return destination;
}

void Passenger::setSource(Point s) {
    source = s;
}

void Passenger::setDestination(Point d) {
    destination = d;
}

int Passenger::getScore() {
    return (rand() %6);
}