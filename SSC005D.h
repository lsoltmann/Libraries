/*
 SSC005D.h
 
 Description: Header for Honeywell digital pressure transducer driver
 
 
 Revision History
 Rev A - 28 May 2015 - Created and debugged
 
 Author: Lars Soltmann
 */

#ifndef ____HWSSC__
#define ____HWSSC__

#include "/home/pi/Navio/C++/Navio/I2Cdev.h"
#include <math.h>
#include <unistd.h>
#include <string>

#define MS4515_DEFAULT_ADDRESS 0x28
#define MS4515_TYPE_A 1
#define MS4515_TYPE_B 2

class HWSSC
{
public:
    HWSSC(uint8_t address = MS4515_DEFAULT_ADDRESS);
    ~HWSSC();
    uint16_t readPressure_raw();
    float convertPressure(uint16_t pdata,int calRange,int sensRange);

private:
    uint8_t devAddr, buffer[2];
    double press;
    uint16_t pdata;
    int status;
    int calRange;
    int sensRange;
};

#endif
