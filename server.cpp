
#include "TaxiFlow.h"
#include "Tcp.h"
/**
 * main func to run the server.
 * @param argc num of args
 * @param argv args to main
 * @return 0 for success
 */
int main(int argc, char *argv[]) {
    // checks we got a correct number of args.
    if (argc < 2) {
        return 0;
    }
    // initializes the server's socket.
    Socket* socket = new Tcp(1, atoi(argv[1]));
    TaxiFlow* flow = new TaxiFlow(socket);
    // flow will get the input from the user and run the program.
    flow->getInput();
    delete flow;
    delete socket;
    return 0;
}
