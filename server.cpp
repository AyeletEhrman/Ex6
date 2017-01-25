
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
/*
 *
#include "Job.h"
#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>
using namespace std;

void* print(void *id_ptr) {
	int id = *(int *)id_ptr;
	for (int i = 1; i <= 10; i++) {
		cout << "print " << id << ": " << i << endl;
		sleep(1);
	}
	return NULL;
}

int main() {
	char ch;
	ThreadPool pool(3);
	Job *arr[5];
	int num[5] = {1, 2, 3, 4, 5};


	for (int i = 0; i < 5; i++) {

		arr[i] = new Job(print, num + i);
		pool.addJob(arr[i]);
	}

	cout << "type char to exit" << endl;
	cin >> ch;
	for (int i =0; i< 5; i++) {
		delete arr[i];
	}

	pool.terminate();
	coutt << "end of main" << endl;
}


 */