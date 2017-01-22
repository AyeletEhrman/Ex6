#include "Taxi.h"

Taxi::Taxi(int cabId1, MANUFACTURER manufacturer1, COLOR color1) {
    cabId = cabId1;
    km = 0;
    manufacturer = manufacturer1;
    color = color1;
    tariff = 0;
}

Taxi::Taxi() {
}

Taxi::~Taxi() {
}

int Taxi::getId() {
    return cabId;
}

void Taxi::setKm(double k) {
    km += k;
}

double Taxi::getKm() {
    return  km;
}

void Taxi::setTariff(double t) {
    tariff = t;
}

double Taxi::getTariff() {
    return tariff;
}

MANUFACTURER Taxi::getManufacturer() {
    return manufacturer;
}

COLOR Taxi::getColor() {
    return color;
}

int Taxi::getType() {
    return 1;
}