/*
wifiCom.cpp

Description: Library for wifi communication with ground station using TCP

Revision History
26 Jun 2015 - Created and debugged
10 Jul 2015 - Updated

Author: Lars Soltmann
*/

#include "wifiCom.h"

COMMS::COMMS(){
}

std::string COMMS:getIP(){
	 tempfd = socket(AF_INET, SOCK_DGRAM, 0);
	 ifr.ifr_addr.sa_family = AF_INET;
	
	 // Get IP of wlan0
	 strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ-1);
	 ioctl(fd, SIOCGIFADDR, &ifr);
	 close(fd);
	 IPADR=inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
	 return IPADR;
}

int COMMS::openConnection(int port,int IPaddress[4]){
    error_flag=0;

    // UDP Setup
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0){
        error_flag++;
	printf("---> Socket setup failure\n");
    }
    
    // Local Setup
    lIP=getIP();
//    memset((char *)&local_address, 0, sizeof(local_address));
    local_address.sin_family = AF_INET;
    local_address.sin_addr.s_addr = inet_addr(lIP.c_str());
    local_address.sin_port = htons(port);
    local_len = sizeof(local_address);
	    
    // Other Machine Setup
    nlIP_ss<<IPaddress[0];
    nlIP_ss<<".";
    nlIP_ss<<IPaddress[1];
    nlIP_ss<<".";
    nlIP_ss<<IPaddress[2];
    nlIP_ss<<".";
    nlIP_ss<<IPaddress[3];
    nlIP_s=nlIP_ss.str();
//    memset((char *)&nonlocal_address, 0, sizeof(nonlocal_address));
    nonlocal_address.sin_family = AF_INET;
    nonlocal_address.sin_addr.s_addr = inet_addr(nlIP_s.c_str());
    nonlocal_address.sin_port = htons(port);
    nonlocal_len = sizeof(nonlocal_address);

    status = bind(server_socket, (struct sockaddr *) &local_address, sizeof(local_address));
    if (status < 0){
	error_flag++;
        printf("---> Socket bind failure\n");
    }

    return error_flag;
}

int COMMS::sendData(unsigned char data[3]){
    //Assemble message to be sent
    message[0]=34; //identifier 1
    message[1]=43; //identifier 2
    message[2]=2;  //1=command, 2=telemetry data
    message[3]=6;  //payload length, bytes
    message[4]=(data[0] >> 8) && 0xFF; //data, split into two bytes
    message[5]=data[0] && 0xFF;
    message[6]=(data[1] >> 8) && 0xFF; 
    message[7]=data[1] && 0xFF;
    message[8]=(data[2] >> 8) && 0xFF; 
    message[9]=data[2] && 0xFF;
    CK_A=0;
    CK_B=0;
    //uint8_t CK_A=0, CK_B=0;
    for (int i=3;i<10;i++){
    	CK_A+=message[i];
    	CK_B+=CK_A;
    }
    message[10]=CK_A;
    message[11]=CK_B;
    
    status=sendto(server_socket, &message, 12, 0, (struct sockaddr *) &nonlocal_address, nonlocal_len);
//    status=sendto(server_socket, &message, 1, 0, (struct sockaddr *) &client_address, sizeof(client_address));
    if (status < 0){
        printf("Send error\n");
    }
    return status;
}

unsigned char COMMS::listenData(){
    recvlen = recvfrom(server_socket, &buffer, 12, 0, (struct sockaddr *) &nonlocal_address, &nonlocal_len);
//    recvlen = recvfrom(server_socket, &buffer, 1, 0, (struct sockaddr *)&client_address, &clientlen);
    return buffer;
}
