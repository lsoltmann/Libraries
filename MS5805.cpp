/*
 MS5805.cpp
 
 Description: Driver for MS5805 pressure transducer
 
 
 Revision History
 Rev A - 26 April 2015 - Created and debugged
 
 Author: Lars Soltmann
 */

#include "MS5805.h"
#include <stdio.h>

MS5805::MS5805(uint8_t devaddr){
    this->address = devaddr;
}

MS5805::~MS5805(){}

void MS5805::initialize() {
    uint8_t buff[2];
    I2Cdev::writeBytes(address, RESET, 0, 0);
    I2Cdev::readBytes(address, CAL_C1, 2, buff);
    C1 = buff[0]<<8 | buff[1];
    I2Cdev::readBytes(address, CAL_C2, 2, buff);
    C2 = buff[0]<<8 | buff[1];
    I2Cdev::readBytes(address, CAL_C3, 2, buff);
    C3 = buff[0]<<8 | buff[1];
    I2Cdev::readBytes(address, CAL_C4, 2, buff);
    C4 = buff[0]<<8 | buff[1];
    I2Cdev::readBytes(address, CAL_C5, 2, buff);
    C5 = buff[0]<<8 | buff[1];
    I2Cdev::readBytes(address, CAL_C6, 2, buff);
    C6 = buff[0]<<8 | buff[1];
    
    // *!*!*!*!*!*!*!*!*!*!
    C6 = 27058;
    // *!*!*!*!*!*!*!*!*!*!

printf("Warning! Force value on MS5805 coefficint 6!\n");
}


void MS5805::read_pressure_temperature() {
    I2Cdev::writeBytes(address, D1, 0, 0);
    usleep(20000);
    I2Cdev::readBytes(address, ADCREAD, 3, buffer);
    pressi = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
    
    I2Cdev::writeBytes(address, D2, 0, 0);
    usleep(20000);
    I2Cdev::readBytes(address, ADCREAD, 3, buffer);
    tempi = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
    
    dT = tempi - C5 * pow(2, 8);
    temp = (2000 + ((dT * C6) / pow(2, 23)));
    
    OFF = C2 * pow(2, 17) + (C4 * dT) / pow(2, 6);
    SENS = C1 * pow(2, 16) + (C3 * dT) / pow(2, 7);
    
    
    if (temp >= 2000)
    {
        T2 = 0;
        OFF2 = 0;
        SENS2 = 0;
    }
    if (temp < 2000)
    {
        T2 = 11 * dT * dT / pow(2, 35);
        OFF2 = 31 * pow(temp - 2000, 2) / pow(2,3);
        SENS2 = 63 * pow(temp - 2000, 2) / pow(2,5);
    }
    
    temp = temp - T2;
    OFF = OFF - OFF2;
    SENS = SENS - SENS2;
    
    // Final calculations
    press = ((pressi * SENS) / pow(2, 21) - OFF) / pow(2, 15) / 100;
    temp = temp / 100;
}

float MS5805::getTemperature() {
    return temp;
}


float MS5805::getPressure() {
    return press;
}
