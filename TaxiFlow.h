#ifndef EX3_TAXIFLOW_H
#define EX3_TAXIFLOW_H
#include <iostream>
#include <vector>
#include <pthread.h>
#include "Point.h"
#include "Node.h"
#include "TaxiCenter.h"
#include "Driver.h"
#include "Trip.h"
#include "Luxury.h"
#include "Tcp.h"
#include "DriverDescriptor.h"
#include <unistd.h>
using namespace std;
/**
 * this class creates a taxiflow that gets the input from the user.
 */
class TaxiFlow {
    private:
        TaxiCenter center;
        Socket* socket;
        vector<DriverDescriptor*>* clients;
        vector<pthread_t> threadsVec;
        bool go;
        bool exit;
        int counter;
        pthread_mutex_t acceptMutex;
        pthread_mutex_t addMutex;
        pthread_mutex_t driveMutex;
        /**
         * method that runs the program.
         */
        void run();
        /**
        * adding drivers to the program.
        */
        void addDrivers();
        /**
        * adding a trip to the program.
        */
        void addTrip();
        /**
        * adding a cab to the program.
        */
        void addCab();
        /**
        * getting a driver location.
        */
        void getDriverLocation();
        /**
        * method that drives the cabs to their destination.
        */
        void drive();
        /**
         * tells the clients they can close now.
         */
        void closeClients();
        /**
         * gets driver from client
         * @param socket the socket that will communicate.
         * @return a driverDescriptor.
         */
        void getDriversFromClients();//void* socket);
        /**
         * communicates withe client throwout the program.
         * @param ds the client's/driver descriptor.
         */
        void communicateWithClient(DriverDescriptor* ds);

    public:
        /**
         * constructs a TaxiFlow.
         */
        TaxiFlow(Socket* socket);
        /**
         * destructs a TaxiFlow.
         */
        ~TaxiFlow();
        /*
         * this function will be responsible to get the input from the user
         * with the details of the features of the game
         */
        void getInput();
        /**
         * a wrapper for getting the clients in a thread.
         * @param tf the taxi flow.
         */
        static void* getClientsWrapper(void* tf);



    };
#endif //EX3_TAXIFLOW_H