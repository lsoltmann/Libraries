/*
 MS4515.cpp
 
 Description: Driver for MS4515 pressure transducer
 
 
 Revision History
 Rev A - 26 April 2015 - Created and debugged
 
 Author: Lars Soltmann
 */

#include "MS4515.h"

MS4515::MS4515(uint8_t address){
    this->devAddr=address;
}

MS4515::~MS4515(){}

uint16_t MS4515::readPressure_raw(){
    // Pressure Only
    uint8_t buffer[2];
    I2Cdev::readBytes(devAddr, 0, 2, buffer);
    pdata = (buffer[0] << 8) | buffer[1];
    status = pdata >> 14;
    pdata = (pdata & 0x3FFF);

    // Pressure and Temperature
//    I2Cdev::readBytes(address, 0, 4, buffer);
//    pdata = (buffer[2] << 16) | buffer[3];
//    tdata = (buffer[0] << 16) | buffer[1];
//    status = pdata >> 14;
//    pdata = (pdata & 0x3FFF);

    return pdata;
}

float MS4515::convertPressure(uint16_t pdata,int sensType,int sensRange){
    if (sensType == 1) {
	press=(7.629860221e-5*(-16383+2*pdata))*sensRange;
    }
    if (sensType == 2) {
	press=(6.782097974e-5*(-16383+2*pdata))*sensRange;
    }

    return press;
}
