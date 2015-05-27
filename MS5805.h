/*
 MS5805.h
 
 Description: Header for MS5805 driver
 
 
 Revision History
 Rev A - 26 April 2015 - Created and debugged
 
 Author: Lars Soltmann
 */

#ifndef ____MS5805__
#define ____MS5805__

#include "/home/pi/Navio/C++/Navio/I2Cdev.h"
#include <math.h>
#include <unistd.h>
#include <string>

#define D1 0x4A
#define D2 0x5A
#define RESET 0x1E
#define ADCREAD 0x00
#define CRC 0xA0
#define CAL_C1 0xA2
#define CAL_C2 0xA4
#define CAL_C3 0xA6
#define CAL_C4 0xA8
#define CAL_C5 0xAA
#define CAL_C6 0xAE
#define MS5805_DEFAULT_ADDRESS 0x76

class MS5805
{
public:
    MS5805(uint8_t devaddr = MS5805_DEFAULT_ADDRESS);
    ~MS5805();
    void initialize();
    void read_pressure_temperature();
    float getPressure();
    float getTemperature();
    
private:
    uint8_t address, buff[2], buffer[3];
    uint16_t C1, C2, C3, C4, C5, C6;
    uint32_t tempi, pressi;
    float temp;
    float press;
    float dT, T2;
    float OFF, OFF2;
    float SENS, SENS2;
};




#endif /* defined(____MS5805__) */
