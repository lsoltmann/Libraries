/*
wifiCom.cpp

Description: Library for wifi communication with ground station using TCP

Revision History
26 June 2015 - Created and debugged

Author: Lars Soltmann
*/

#include "wifiCom.h"

COMMS::COMMS(){
}

int COMMS::openConnection(int port){
    error_flag=0;

    // TCP Setup
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0){
        error_flag++;
	printf("---> Socket setup failure\n");
    }

    // Server (aircraft) setup
//    memset((char *)&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("192.168.1.65");
    server_address.sin_port = htons(port);
    socklen_t serverlen = sizeof(server_address);

    // Client (GCS) setup
//    memset((char *)&client_address, 0, sizeof(client_address));
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr("192.168.1.66");
    client_address.sin_port = htons(port);
    clientlen = sizeof(client_address);

    status = bind(server_socket, (struct sockaddr *) &client_address, sizeof(client_address));
    if (status < 0){
	error_flag++;
        printf("---> Socket bind failure\n");
    }

    return error_flag;
}

int COMMS::sendData(int message){
    status=sendto(server_socket, &message, 1, 0, (struct sockaddr *) &server_address, sizeof(server_address));
//    status=sendto(server_socket, &message, 1, 0, (struct sockaddr *) &client_address, sizeof(client_address));
    if (status < 0){
        printf("Send error\n");
    }
    return status;
}

unsigned char COMMS::listenData(){
    recvlen = recvfrom(server_socket, &buffer, 1, 0, (struct sockaddr *)&server_address, &serverlen);
//    recvlen = recvfrom(server_socket, &buffer, 1, 0, (struct sockaddr *)&client_address, &clientlen);
    return buffer;
}
