#include "Luxury.h"

Luxury::Luxury(int cabId1, MANUFACTURER manufacturer1, COLOR color1)
        :Taxi(cabId1, manufacturer1, color1) {
}

Luxury::Luxury() {
}

Luxury::~Luxury() {
}

void Luxury::setTariff(double t) {
    tariff = t;
}

int Luxury::getType() {
    return 2;
}