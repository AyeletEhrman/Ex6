/************************************************************
* File description: Socket class. creating socket, close 	*
* socket and method prints the errors occurs while			*
* creating sockets, in all the different methods involved	*
************************************************************/
#include "Socket.h"
#include <unistd.h>

#define NONE 0

/***********************************************************************
* function name: Socket												   *
* The Input: none													   *
* The output: none										               *
* The Function operation: creating new Socket object, with the computer*
* ip, and no port number and socket descriptor, 0 backlogs.			   *
***********************************************************************/
Socket::Socket() {
	ip_address = IP;
	backLog = NONE;
	socketDescriptor = NONE;
	isServer = true;
	port_number = NONE;
}

/***********************************************************************
* function name: ~Socket											   *
* The Input: none													   *
* The output: none										               *
* The Function operation: default destructor					       *
***********************************************************************/
Socket::~Socket() {
	close(socketDescriptor);
}

