#include "Socket.h"
#include "Driver.h"
#include "Luxury.h"
#include "Tcp.h"
#include "ValidInput.h"

BOOST_CLASS_EXPORT_GUID(Node, "Node");
BOOST_CLASS_EXPORT_GUID(GridPt, "GridPt");
BOOST_CLASS_EXPORT_GUID(Taxi, "Taxi");
BOOST_CLASS_EXPORT_GUID(Luxury, "Luxury");
using namespace std;
/**
 * main func to run the client.
 * @param argc num of args
 * @param argv args to main
 * @return 0 for success
 */
int main(int argc, char *argv[]) {
    // declarations.
    ValidInput vi;
    string input;
    Driver* driver;
    // we expect to get ip and port
    if (argc < 3) {
        return 0;
    }

    // gets the driver's details from the user.
    cin >> input;
    driver = vi.validClient(input);
    if (driver == NULL) {

        cout << "invalid driver :( " << endl;

        return 0;
    }

    cout << "valid driver:) " << endl;

    // create the socket.
    Socket* socket = new Tcp(0, atoi(argv[2]));
    // we can get localhost or ip string for ip address.
    if (strcmp(argv[1], "localhost") == 0) {
        socket->setIp("127.0.0.1");
    } else {
        socket->setIp(argv[1]);
    }
    socket->initialize();

    //DriverDescriptor* ds = new DriverDescriptor(driver, ((Tcp*)socket)->getDescriptorCommunicateClient());
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    // flush the stream to finish writing into the buffer.
    s.flush();
    // send driver information to server.
    socket->sendData(serial_str, 0);

    char buffer[1000];
    Taxi *taxi;
    // get the taxi of the driver.
    socket->receiveData(buffer, sizeof(buffer), socket->getSocketDescriptor());
    boost::iostreams::basic_array_source<char> device2(buffer, sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device2);
    boost::archive::binary_iarchive ia2(s2);
    ia2 >> taxi;
    driver->setCab(taxi);

    string command;
    GridPt* location = new GridPt();
    // a loop to get the information from the server.
    do {
        socket->receiveData(buffer, sizeof(buffer), socket->getSocketDescriptor());
        command = buffer;
        // if server sent "go" we prepare to get a new location.
        if (strcmp(command.data(), "go") == 0) {
            if (location != NULL) {
                delete location;
            }
            // gets the location.
            socket->receiveData(buffer, sizeof(buffer), socket->getSocketDescriptor());
            boost::iostreams::basic_array_source<char> device5(buffer, sizeof(buffer));
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s5(device5);
            boost::archive::binary_iarchive ia5(s5);
            ia5 >> location;
            // set the driver's location.
            driver->setLocation(location);
        }
    // if server sent "exit" we exit the loop.
    } while (strcmp(command.data(), "exit") != 0);
    delete driver;
    delete location;
    delete taxi;
    delete socket;
    return 0;
}
