#ifndef EX3_LUXURY_H
#define EX3_LUXURY_H
#include "Taxi.h"
#include <boost/serialization/export.hpp>
using namespace std;
using namespace boost::archive;
/**
 * this class creates a Luxury cab that inherites from Taxi.
 */
class Luxury : public Taxi {
    private:
        int cabId;
        int km;
        MANUFACTURER manufacturer;
        COLOR color;
        double tariff;

        friend class boost::serialization::access;
        template<class Archive>
        /**
         * serialzes a Luxury cab.
         * @param ar
         * @param version
         */
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<Taxi>(*this);
           // ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Taxi);
        }
    public:
        /**
         * constructs a Luxury cab.
         * @param cabId1 cabs id
         * @param km1 num of km the cab passed.
         * @param manufacturer1 the cabs manufacturer.
         * @param color1 the cabs color.
         * @param tariff1 the tariff for a drive in the cab.
         * @return a luxury object
         */
        Luxury(int cabId1, MANUFACTURER manufacturer1, COLOR color1);
        /**
         * a default constructor of luxury
         * @return a luxury object
         */
        Luxury();
        /**
         * destructs the Luxury cab.
         */
        ~Luxury();
        /**
         * sets the cabs tariff.
         * @param t the new tariff.
         */
        void setTariff(double t);
        /**
         * returns the type number of the cab.
         * @return the type
         */
        int getType();
};
#endif //EX3_LUXURY_H