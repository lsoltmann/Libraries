/*
SSC005D.cpp
 
 Description: Driver for Honeywell SSCDRRN005ND2A5 pressure transducer, although the library can be used for any Honeywell digital I2C pressure transducer
 
 
 Revision History
 Rev A - 28 May 2015 - Created and debugged
 
 Author: Lars Soltmann
 */

#include "SSC005D.h"

HWSSC::HWSSC(uint8_t address){
    this->devAddr=address;
}

HWSSC::~HWSSC(){}

uint16_t HWSSC::readPressure_raw(){
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

double HWSSC::convertPressure(uint16_t pdata,int calRange,int sensRange){
    if (calRange == 1) { // 10 to 90% calibration
	press=(1.525878906e-4*pdata-1.25)*sensRange;
    }
    if (calRange == 2) { // 5 to 95% calibration
	press=(1.356336806e-4*pdata-1.111111111)*sensRange;
    }
    if (calRange == 3) { // 5 to 85% calibration
	press=(1.525878906e-4*pdata-1.125)*sensRange;
    }
    if (calRange == 4) { // 4 to 94% calibration
	press=(1.356336806e-4*pdata-1.088888889)*sensRange;
    }

    return press;
}
