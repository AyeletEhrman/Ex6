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
    int x, y, numOfObs;
    // will read the ','.
    char comma;
    Point mapSize;
    // reads the map size.
    cin >> skipws >> x >> y;
    mapSize = Point(x,y);
    Map* map = new Map(mapSize);
    // reads the number of obstacles.
    cin >> skipws >> numOfObs;
    // reads the obstacle.
    for (int i = 0; i < numOfObs; i++) {
        cin >> x >> comma >> y;
        GridPt obs = GridPt(Point(x,y));
        //obstacles.push_back(&obs);
        map->addObstacle(&obs);
    }
    // creates the taxi center with the given map.
    center = TaxiCenter(map);
    // tuns the commands.
    run();
    delete map;
}

void TaxiFlow::run() {
    // the command from the user.
    int command;
    do {
        // reads the command.
        cin >> command;
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
            // for '4' - close clients.
            case 7:
                closeClients();
                break;
            // for '9' - drives the cars.
            case 9:
                drive();
                break;
            default:
                break;
        }
    // for '7' - end program.
    } while (command != 7);
}

void TaxiFlow::addDrivers() {
    int numDrivers;
    // gets the number of drivers from the user.
    cin >> numDrivers;
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
    int id, xStart, yStart, xEnd, yEnd, numPassengers, startTime;
    double tariff;
    // skips the punctuation marks.
    char skip;
    // gets the trip's details from the user.
    cin >> id >> skip >> xStart >> skip >> yStart >> skip >> xEnd
        >> skip >> yEnd >> skip >> numPassengers >> skip >> tariff >> skip >> startTime;
    // gets the starting point from the map.
    GridPt* start = center.getMap()->getPoint(Point(xStart,yStart));//center.getMap()->getPoint(Point(xStart,yStart));
    // gets the ending point from the map.
    GridPt* end = center.getMap()->getPoint(Point(xEnd,yEnd));//center.getMap()->getPoint(Point(xEnd,yEnd));
    // creates the new trip.
    Trip* trip = new Trip(id, start, end, numPassengers, tariff, startTime);
    // calcs the route of the trip.
    center.calcTripRoute(trip);
}

void TaxiFlow::addCab() {
    int id, type;
    char manufacturerSign, colorSign;
    // skips the punctuation marks.
    char skip;
    MANUFACTURER manufacturer;
    COLOR color;
    Taxi* taxi;
    // gets the cab's details from the user.
    cin >> id >> skip >> type >> skip >> manufacturerSign >> skip >> colorSign;
    // assigns the cars manufacturer.
    switch (manufacturerSign) {
        case 'H':
            manufacturer = HONDA;
            break;
        case 'S':
            manufacturer = SUBARO;
            break;
        case 'T':
            manufacturer = TESLA;
            break;
        case 'F':
            manufacturer = FIAT;
            break;
        default:
            break;
    }
    // assigns the cars color.
    switch (colorSign) {
        case 'R':
            color = RED;
            break;
        case 'B':
            color = BLUE;
            break;
        case 'G':
            color = GREEN;
            break;
        case 'P':
            color = PINK;
            break;
        case 'W':
            color = WHITE;
            break;
        default:
            break;
    }
    // assigns the taxis type.
    if (type == 1) {
        taxi = new Taxi(id, manufacturer, color);
    } else if (type == 2) {
        taxi = new Luxury(id, manufacturer, color);
    } else {
        return;
    }
    // adds the taxi.
    center.addTaxi(taxi);
}

void TaxiFlow::getDriverLocation() {
    int id;
    // gets the drivers id.
    cin >> id;
    // gets the drivers from the center.
    vector<Driver*> drivers = center.getDrivers();
    // looks for the driver.
    for (int i = 0; i < drivers.size(); i++) {
        if (id == drivers.at(i)->getId()) {
            while (drivers.at(i)->getPrevTime() != center.getTime()) {
                sleep(1);
            }
            // prints the location of the given driver.
            cout << *(drivers.at(i)->getLocation()) << endl;
            break;
        }
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
    //  receive the clients.
    ((TaxiFlow*)tf)->getDriversFromClients();
}

void TaxiFlow::getDriversFromClients() {//void* socket) {
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
