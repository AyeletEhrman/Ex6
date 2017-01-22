/************************************************************
* File description: Socket class header file. 				*
* contains socket properties as members, declaration on 	*
* methods, and const numbers using by all classes which		*
* inherit from Socket class									*
************************************************************/

#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

//return values to each function if error happened
#define CORRECT 0
#define ERROR_SOCKET 1
#define ERROR_BIND 2
#define ERROR_LISTEN 3
#define ERROR_CONNECT 4
#define ERROR_SEND 5
#define ERROR_RECIVE 6
#define ERROR_ACCEPT 7
#define CONNECTION_CLOSED 8

#define IP "127.0.0.1"

class Socket {
	protected:
		//true is the socket is for a server, false if for a client
		bool isServer;
		//the socket descriptor return from sock()
		int socketDescriptor;
		//ip adress
		string ip_address;
		int backLog;
		//port number
		int port_number;
	public:
		/***********************************************************************
		* function name: Socket												   *
		* The Input: none													   *
		* The output: none										               *
		* The Function operation: creating new Socket object			       *
		***********************************************************************/
		Socket();
		/***********************************************************************
		* function name: ~Socket											   *
		* The Input: none													   *
		* The output: none										               *
		* The Function operation: default destructor					       *
		***********************************************************************/
		virtual ~Socket();
		/***********************************************************************
		* function name: initialize											   *
		* The Input: none              										   *
		* The output: int number representing the return status		           *
		* The Function operation: initialize the Socket object and getting a   *
		* socket descriptor. pure virtual method							   *
		***********************************************************************/
		virtual int initialize() = 0;
		/***********************************************************************
		* function name: sendData											   *
		* The Input: string representing the data to send		               *
		* The output: int number representing the return status		           *
		* The Function operation: sending the input data to the socket         *
		* who connect to this socket. pure virtual method					   *
		***********************************************************************/
		virtual int sendData(string data, int socketDescComm) = 0;
		/***********************************************************************
		* function name: recive	`											   *
		* The Input: none										               *
		* The output: int number representing the return status	               *
		* The Function operation: getting data from the other socket and print *
		* the data															   *
		***********************************************************************/
		virtual int receiveData(char* buffer, int size, int socketDescComm) = 0;
		/***********************************************************************
		* function name: setIp	`											   *
		* The Input: string of the ip										   *
		* The output: none         											   *
		* The Function operation: getting the ip and						   *
		* seting it as the sockets ip										   *
		***********************************************************************/
        virtual void setIp(string ip) = 0;
		/***********************************************************************
		 * get the socket descriptor.
		 * @return the socket descriptor.
		 ***********************************************************************/
        virtual int getSocketDescriptor() = 0;
		/***********************************************************************
		 * fets the socket desc' of the client for communication.
		 * @return the client's desc'.
		 ***********************************************************************/
        virtual int getDescriptorCommunicateClient() = 0;
		/***********************************************************************
		 * accepts the client.
		 * @return if error accepted returns error numbr.
		 ***********************************************************************/
        virtual int acceptClient() = 0;
};

#endif /* SOCKET_H_ */
