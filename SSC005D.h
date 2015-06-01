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

#define HWSSC_DEFAULT_ADDRESS 0x28
#define HWSSC_cal_10_95 1
#define HWSSC_cal_05_95 2
#define HWSSC_cal_05_85 3
#define HWSSC_cal_04_94 4

class HWSSC
{
public:
    HWSSC(uint8_t address = HWSSC_DEFAULT_ADDRESS);
    ~HWSSC();
    uint16_t readPressure_raw();
    double convertPressure(uint16_t pdata,int calRange,int sensRange);

private:
    uint8_t devAddr, buffer[2];
    double press;
    uint16_t pdata;
    int status;
    int calRange;
    int sensRange;
};

#endif
