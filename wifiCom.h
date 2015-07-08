/*
 wifiCom.cpp

 Description: Library for wifi communication with ground station using TCP

 Revision History
 26 June 2015 - Created and debugged

 Author: Lars Soltmann
 */

#ifndef ____wifiCom__
#define ____wifiCom__

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class COMMS {
public:
    COMMS();
    int openConnection(int port);
    int sendData(int message);
    unsigned char listenData();
    int port;
    int message;
    unsigned char buffer;

private:
    int status;
    int error_flag;
    int server_socket;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int recvlen;
    socklen_t clientlen;
};







#endif
