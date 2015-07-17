/*
wifiCom.cpp

Description: Library for wifi communication with ground station using UDP

Revision History
26 Jun 2015 - Created and debugged
10 Jul 2015 - Updated

Author: Lars Soltmann
*/

#include "wifiCom.h"

COMMS::COMMS(){
}

std::string COMMS::getIP(){
	 tempfd = socket(AF_INET, SOCK_DGRAM, 0);
	 ifr.ifr_addr.sa_family = AF_INET;

	 // Get IP of wlan0
	 strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ-1);
	 ioctl(tempfd, SIOCGIFADDR, &ifr);
	 close(tempfd);
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

    status = bind(server_socket, (struct sockaddr *) &local_address, local_len);
    if (status < 0){
	error_flag++;
        printf("---> Socket bind failure\n");
    }

    return error_flag;
}

void COMMS::packetize(int txdata[],int datasize,int messageType){
    //Assemble message to be sent
    message[0]=messageType; // 1 = command, 2 = telemetry
    message[1]=datasize*2; // payload length, bytes (2 bytes per piece of data)
    j=0;
    for (int i=2;i<2*datasize+1;i=i+2){
	bytes.value=txdata[j];
        message[i]=bytes.split[1];
        message[i+1]=bytes.split[0];
        j++;
    }
    CK_A=0;
    CK_B=0;
    for (int i=1;i<2*datasize+2;i++){
        CK_A+=message[i];
        CK_B+=CK_A;
    }
    message[2*datasize+2]=CK_A;
    message[2*datasize+3]=CK_B;
}

void COMMS::unpacketize(uint8_t recvmessage[],int recvlen){
    j=0;
    for (int i=2;i<recvmessage[1]+1;i=i+2){
        bytes.split[1]=recvmessage[i];
	bytes.split[0]=recvmessage[i+1];
	rxdata[j]=bytes.value;
        j++;
    }
}

int COMMS::sendData(int txdata[],int datasize,int messageType){
    packetize(txdata,datasize,messageType);
  status=sendto(server_socket, &message, 2*datasize+4, 0, (struct sockaddr *) &nonlocal_address, nonlocal_len);
    if (status < 0){
        printf("Send error\n");
    }
    return status;
}

int COMMS::listenData(){
    status=0;
    recvlen = recvfrom(server_socket, &recvmessage, sizeof(recvmessage), 0, (struct sockaddr *) &nonlocal_address, &nonlocal_len);
    if (recvlen>0){
        CK_A=0;
        CK_B=0;
    	for (int i=1;i<recvlen-2;i++){
    	CK_A+=recvmessage[i];
    	CK_B+=CK_A;
    	}
	if (CK_A==recvmessage[recvlen-2] && CK_B==recvmessage[recvlen-1]){
		unpacketize(recvmessage,recvlen);
	}
    	else {
    		status=2;
    	}
    }
    else {
    	status=1;
    }

    return status;
}
