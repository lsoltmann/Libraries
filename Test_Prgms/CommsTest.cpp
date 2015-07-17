//
//  CommsTest.cpp
//
//
//  Created by Lars Soltmann on 6/28/15.
//
//

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "/home/pi/Libraries/wifiCom.h"

int main(){
    COMMS link;
    unsigned char message=0;
    if (link.openConnection(35007) != 0){
        printf("Couldn't open port!\n");
        exit(0);
    }
    else{
        printf("Port opened\n");
    }

// Send data
    printf("Sending data ...\n");
    while (true) {
        link.sendData(message);
	printf("data sent: %d\n",message);
        message++;
        sleep(1);
    }


/*
// Recieve data
    printf("Waiting for data ...\n");
    while (true) {
        message=link.listenData();
        printf("Data recieved: %d\n",message);
    }
*/



    return 0;
}
