/*
 wifiCom.cpp

 Description: Library for wifi communication with ground station using UDP

 Revision History
 26 Jun 2015 - Created and debugged
 10 Jul 2015 - Updated

 Author: Lars Soltmann
 */

#ifndef ____wifiCom__
#define ____wifiCom__

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <cstring>

#define RXTXBUFFER 1024

class COMMS {
public:
    COMMS();
    int openConnection(int port,int IPaddress[4]);
    std::string getIP();
    int sendData(int txdata[],int datasize,int messageType);
    void packetize(int txdata[],int datasize,int messageType);
    void unpacketize(uint8_t recvmessage[],int recvlen);
    int listenData();
    int port;
    int IPaddress[4];
    int txdata[];
    int datasize;
    uint8_t recvmessage[RXTXBUFFER];
    int16_t rxdata[RXTXBUFFER];
    int messageType;

private:
    uint8_t message[RXTXBUFFER];
    int status;
    int error_flag;
    int server_socket;
    struct sockaddr_in local_address;
    struct sockaddr_in nonlocal_address;
    int recvlen;
    socklen_t local_len;
    socklen_t nonlocal_len;
    int tempfd;
    struct ifreq ifr;
    std::string IPADR;
    std::string lIP;
    std::string nlIP_s;
    std::stringstream nlIP_ss;
    uint8_t CK_A;
    uint8_t CK_B;
    int j;
    union u_1{
        int16_t value;
        uint8_t split[2];
    } bytes;
};

#endif
