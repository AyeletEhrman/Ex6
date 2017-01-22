#include "Point.h"

Point::Point(int x1, int y1) {
    x = x1;
    y = y1;
}

Point::Point() {
    x = 0;
    y = 0;
}

Point::~Point() {
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Point::setX(int newX) {
    x = newX;
}

void Point::setY(int newY) {
    y = newY;
}

bool Point::operator == (const Point &p1) const {
    return ((getX() == p1.getX()) && (getY() == p1.getY()));
}

bool Point::operator != (const Point &p1) const {
    return ((getX() != p1.getX()) || (getY() != p1.getY()));
}