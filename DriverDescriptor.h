
#ifndef EX5_DRIVERDESCRIPTOR_H
#define EX5_DRIVERDESCRIPTOR_H
#include "Driver.h"
using namespace std;
using namespace boost::archive;
/**
 * a class that holds driver and descriptor number.
 */
class DriverDescriptor {
    private:
        Driver* driver;
        int descriptorCommunicateClient;

        friend class boost::serialization::access;
        template<class Archive>
        /**
         * seralize a driver object.
         * @param ar
         * @param version
         */
        void serialize(Archive &ar, const unsigned int version) {
            ar & driver;
            ar & descriptorCommunicateClient;
        }
    public:
       /**
        * constructor for driver descriptor object.
        * @param driver1 the driver
        * @param descriptorCommunicateClient1 his descriptor
        * @return driver descriptor object
        */
        DriverDescriptor(Driver* driver1, int descriptorCommunicateClient1);
        /**
         * a default constructor of driver descriptor.
         * @return driver descriptor object
         */
        DriverDescriptor();
        /**
         * destructor of driver descriptor.
         */
        ~DriverDescriptor();
        /**
         * sets the descriptor of the driver
         * @param sd
         */
        void setDescriptor(int sd);
        /**
         * return the descriptor of the driver descriptor.
         * @return descriptorCommunicateClient
         */
        int getDescriptor();
        /**
         * returns the driver
         * @return driver
         */
        Driver* getDriver();
};

#endif //EX5_DRIVERDESCRIPTOR_H
