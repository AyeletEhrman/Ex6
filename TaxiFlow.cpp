#include "TaxiFlow.h"

BOOST_CLASS_EXPORT_GUID(Node, "Node");
BOOST_CLASS_EXPORT_GUID(GridPt, "GridPt");
BOOST_CLASS_EXPORT_GUID(Taxi, "Taxi");
BOOST_CLASS_EXPORT_GUID(Luxury, "Luxury");

TaxiFlow::TaxiFlow(Socket* socket1) {
    socket = socket1;
    socket->initialize();
    clients = new vector<DriverDescriptor*>;
    pthread_mutex_init(&acceptMutex, 0);
    pthread_mutex_init(&addMutex, 0);
    pthread_mutex_init(&driveMutex, 0);
    go = false;
    exit = false;
    counter = 0;
}

TaxiFlow::~TaxiFlow() {
    while (clients->size() != 0) {
        delete clients->front();
        clients->erase(clients->begin());
    }
    delete clients;
    pthread_mutex_destroy(&acceptMutex);
    pthread_mutex_destroy(&addMutex);
    pthread_mutex_destroy(&driveMutex);
}

void TaxiFlow::getInput() {
    bool checkMap = true;
    string input;
    int numOfObs;
    Map* map = NULL;
    // loop that gets the map again and again until we get a valid map.
    while (checkMap) {
        if (map != NULL) {
            delete map;
        }
        // reads the map size.
        getline(cin, input);
        if (!(vi.pointIsValid(input, Point(1001, 1001), " "))) {
            cout << "-1" << endl;
            continue;
        }
        Point mapSize = vi.validPoint(input);
        map = new Map(mapSize);
        // reads the number of obstacles.
        getline(cin, input);
        if (!(vi.isAnumber(input.data()))) {
            cout << "-1" << endl;
            continue;
        }
        numOfObs = atoi(input.data());
        // reads the obstacles.
        for (int i = 0; i < numOfObs; i++) {
            getline(cin, input);
            if (!(vi.pointIsValid(input, map->getSize(), ","))) {
                cout << "-1" << endl;
                break;
            }
            GridPt obs = GridPt(vi.validPoint(input));
            map->addObstacle(&obs);
        }
        // check if we got enough obstacles.
        if (map->getObstacles()->size() != numOfObs) {
            continue;
        }
        // we got a correct map input.
        checkMap = false;
    }
    // creates the taxi center with the given map.
    center = TaxiCenter(map);
    // runs the commands.
    run();
    delete map;
}

void TaxiFlow::run() {
    // the command from the user.
    string sCommand;
    int command;
    do {
        // reads the command.
        getline(cin, sCommand);
        while (sCommand.length() == 0) {
            getline(cin, sCommand);
        }
        // checks command is valid.
        if (!vi.isAnumber(sCommand.data())){
            sCommand = "-1";
        }
        command = atoi(sCommand.data());
        switch (command) {
            // for '1' -adds drivers.
            case 1:
                addDrivers();
                break;
                // for '2' -adds a trip.
            case 2:
                addTrip();
                break;
                // for '3' -adds a cab.
            case 3:
                addCab();
                break;
                // for '4' - gets a drivers location.
            case 4:
                getDriverLocation();
                break;
                // for '7' - close clients.
            case 7:
                center.terminateThreadPool();
                closeClients();
                break;
                // for '9' - drives the cars.
            case 9:
                drive();
                break;
            default:
                cout << "-1" << endl;
                break;
        }
        // for '7' - end program.
    } while (command != 7);
}

void TaxiFlow::addDrivers() {
    string sNumDrivers;
    int numDrivers;
    // gets the number of drivers from the user.
    getline(cin, sNumDrivers);
    if (!vi.isAnumber(sNumDrivers.data())){
        cout << "-1" << endl;
        return;
    }
    numDrivers = atoi(sNumDrivers.data());
    // num drivers should be positive.
    if (!vi.greaterEqual(numDrivers, 0)) {
        cout << "-1" << endl;
        return;
    }
    threadsVec.resize(numDrivers);
    // opens threads for getting the clients.
    for (int i = 0; i < numDrivers; i++) {
        pthread_create(&threadsVec[i], NULL, getClientsWrapper, (void*)this);
    }
    // wait until all client's are received.
    while (center.getDrivers().size() != numDrivers) {
        sleep(1);
    }
}

void TaxiFlow::addTrip() {
    string input;
    // get the trip details.
    getline(cin, input);
    // check if trip is valid.
    Trip* trip = vi.validTrip(input, center.getMap());
    if (trip == NULL) {
        cout << "-1" << endl;
        return;
    }
    // calcs the route of the trip.
    center.calcTripRoute(trip);
}

void TaxiFlow::addCab() {
    string input;
    // gets the cab's details from the user.
    getline(cin, input);
    // check if cab input is valid.
    Taxi* taxi = vi.validTaxi(input);
    if (taxi == NULL) {
        cout << "-1" << endl;
        return;
    }
    // adds the taxi.
    center.addTaxi(taxi);
}

void TaxiFlow::getDriverLocation() {
    int id;
    string sId;
    bool foundDriver = false;
    // gets the drivers id.
    getline(cin, sId);
    while (sId.length() == 0) {
        getline(cin, sId);
    }
    // checks if id is valid.
    if (vi.isAnumber(sId.data())) {
        id = atoi(sId.data());
        // gets the drivers from the center.
        vector<Driver *> drivers = center.getDrivers();
        // looks for the driver.
        for (int i = 0; i < drivers.size(); i++) {
            if (id == drivers.at(i)->getId()) {
                while (drivers.at(i)->getPrevTime() != center.getTime()) {
                    sleep(1);
                }
                // prints the location of the given driver.
                cout << *(drivers.at(i)->getLocation()) << endl;
                foundDriver = true;
                break;
            }
        }
    }
    // no matching id.
    if (!foundDriver) {
        cout << "-1" << endl;
    }
}

void TaxiFlow::drive() {
    // increases the time.
    center.setTime();
    // now all threads of clients will tell the drivers to drive.
    go = true;
    int numDrivers = center.getDrivers().size();
    // wait for all drivers to drive.
    while (counter != numDrivers) {
        sleep(1);
    }
    // stop driving.
    go = false;
    counter = 0;
    // send taxi.
    center.sendTaxi();
}

void TaxiFlow::closeClients() {
    // now all threads of clients will tell the drivers to exit.
    exit = true;
    for (int i = 0; i < clients->size(); i++) {
        // wait for all cliemts to exit.
        pthread_join (threadsVec[i], NULL);
    }
}

void* TaxiFlow::getClientsWrapper(void* tf) {
    // receive the clients.
    ((TaxiFlow*)tf)->getDriversFromClients();
}

void TaxiFlow::getDriversFromClients() {
    char buffer[1000];
    // the firt thread to come will go in and lock.
    pthread_mutex_lock(&acceptMutex);
    // accept client.
    ((Tcp*)socket)->acceptClient();
    // get the client's descriptor.
    int descriptorComm = ((Tcp*)socket)->getDescriptorCommunicateClient();
    // unlock the tread.
    pthread_mutex_unlock(&acceptMutex);
    // recieve the drivers data from client.
    ((Tcp*) socket)->receiveData(buffer, sizeof(buffer), descriptorComm);
    Driver *driver;
    // gets the driver from client.
    boost::iostreams::basic_array_source<char> device(buffer, sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);
    // deserizlizes the driver from client.
    boost::archive::binary_iarchive ia(s);
    ia >> driver;
    // sets the drivers map.
    driver->setMap(center.getMap());
    //assigns the driver his cab.
    center.assignCab(driver);
    //sends the cab to the driver.
    Taxi *t = driver->getCab();
    std::string serial_str2;
    boost::iostreams::back_insert_device<std::string> inserter2(serial_str2);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s2(inserter2);
    boost::archive::binary_oarchive oa2(s2);
    // serilizes the taxi.
    oa2 << t;
    // flush the stream to finish writing into the buffer
    s2.flush();
    // sends the taxi.
    ((Tcp*) socket)->sendData(serial_str2, descriptorComm);
    // adds the driver to the taxi center.
    //center.addDriver(driver);
    DriverDescriptor* ds = new DriverDescriptor(driver, descriptorComm);
    // lock for adding driver.
    pthread_mutex_lock(&addMutex);
    // add the driver descriptor.
    clients->push_back(ds);
    // add driver.
    center.addDriver(ds->getDriver());
    // unlock.
    pthread_mutex_unlock(&addMutex);
    // go to the tread that will communicate with client throwout the rest of the program.
    communicateWithClient(ds);
}

void TaxiFlow::communicateWithClient(DriverDescriptor* ds) {
    // communicate until exit time.
    while (!exit) {
        // if go is true and the current client did'nt drive this round.
        if (go && (ds->getDriver()->getPrevTime() != center.getTime())) {
            if (ds->getDriver()->isDriving()) {
                // tells the client to be prepared to drive.
                socket->sendData("go", ds->getDescriptor());
                // drives the car.
                ds->getDriver()->drive();
                // sends the new location to client.
                std::string serial_str1;
                boost::iostreams::back_insert_device<std::string> inserter1(serial_str1);
                boost::iostreams::stream
                        <boost::iostreams::back_insert_device<std::string> > s1(inserter1);
                boost::archive::binary_oarchive oa1(s1);
                GridPt* newLocation = new GridPt(ds->getDriver()->getLocation()->getPt());
                // serilizes the new location.
                oa1 << newLocation;
                // flush the stream to finish writing into the buffer
                s1.flush();
                // sends the data.
                socket->sendData(serial_str1, ds->getDescriptor());
                delete newLocation;
            }
            // mutex for setting the time and counter.
            pthread_mutex_lock(&driveMutex);
            ds->getDriver()->setTime(center.getTime());
            counter++;
            // unlock.
            pthread_mutex_unlock(&driveMutex);
        }
    }
    // tells the client to exit.
    socket->sendData("exit", ds->getDescriptor());
}