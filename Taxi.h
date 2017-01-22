#ifndef EX3_TAXI_H
#define EX3_TAXI_H
#include <iostream>
#include <boost/serialization/base_object.hpp>
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
 * this class creates a taxi.
 */
// The taxis manufacturer,
enum MANUFACTURER {
    HONDA, SUBARO, TESLA, FIAT
};
// the taxis color.
enum COLOR {
    RED, BLUE, GREEN, PINK, WHITE
};
class Taxi {
    private:
        int cabId;
        double km;
        MANUFACTURER manufacturer;
        COLOR color;
        double tariff;

    protected:
        friend class boost::serialization::access;
        template<class Archive>
        /**
         * serialize Taxi object.
         * @param ar
         * @param version
         */
        void serialize(Archive &ar, const unsigned int version) {
            ar & cabId;
            ar & km;
            ar & manufacturer;
            ar & color;
            ar & tariff;
        }

    public:
        /**
         * constructs a Taxi cab.
         * @param cabId1 cabs id
         * @param km1 num of km the cab passed.
         * @param manufacturer1 the cabs manufacturer.
         * @param color1 the cabs color.
         * @param tariff1 the tariff for a drive in the cab.
         */
        Taxi(int cabId1, MANUFACTURER manufacturer1, COLOR color1);
        /**
         * defult constructor.
         */
        Taxi();
        /**
         * destructs the Taxi cab.
         */
        ~Taxi();
        /**
         * returns the cab's id
         * @return id.
         */
        int getId();
        /**
         * sets the num of KM passed.
         * @param k the km to add.
         */
        void setKm(double k);
        /**
         * returns the cabs KM
         * @return the km passed.
         */
        double getKm();
        /**
         * sets the cabs tariff.
         * @param t the new tariff.
         */
        void setTariff(double t);
        /**
         * returns the cabs tariff.
         * @return tariff.
         */
        double getTariff();
        /**
         * returns the cabs manufactirer.
         * @return manufacturer.
         */
        MANUFACTURER getManufacturer();
        /**
         * returns the cabs color.
         * @return color.
         */
        COLOR getColor();
        /**
         * gets the type of the cab
         * @return type of cab
         */
        virtual int getType();
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Node);
#endif //EX3_TAXI_H