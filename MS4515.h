/*
 MS4515.h
 
 Description: Header for MS4515 driver
 
 
 Revision History
 Rev A - 26 April 2015 - Created and debugged
 
 Author: Lars Soltmann
 */

#ifndef ____MS4515__
#define ____MS4515__

#include "/home/pi/Navio/C++/Navio/I2Cdev.h"
#include <math.h>
#include <unistd.h>
#include <string>

#define MS4515_DEFAULT_ADDRESS 0x28
#define MS4515_TYPE_A 1
#define MS4515_TYPE_B 2

class MS4515
{
public:
    MS4515(uint8_t address = MS4515_DEFAULT_ADDRESS);
    ~MS4515();
    uint16_t readPressure_raw();
    float convertPressure(uint16_t pdata,int sensType,int sensRange);

private:
    uint8_t devAddr, buffer[2];
    float press;
    uint16_t pdata;
    int status;
    int sensType;
    int sensRange;
};

#endif /* defined(____MS4515__) */
