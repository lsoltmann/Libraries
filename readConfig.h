/*
readConfig.h

 Description: Header for configuration reader library

 Revision History
 19 June 2015 - Created and debugged
 10 July 2015 - Added telemetry variables

 Author: Lars Soltmann
 */

#ifndef ____readConfig__
#define ____readConfig__

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<sstream>

class readConfig
{
public:
  readConfig(std::string name = "testconfig.txt");
  int readfile();
  int open_error;

  int dataSampleRate;
  int MS5805_active;
  int MS5611_active;
  int PPMdecode_active;
  int AHRS_active;
  int GPS_active;
  int MS4515_active;
  int SSC005D_active;
  int ADC_active;
  int RPM_active;
  int IMU_active;
  int gps_priority;
  int ppm_priority;
  int MS5611_priority;
  int MS5805_priority;
  int ahrs_priority;
  int OUTPUT_TO_SCREEN;
  int sys_orientation;
  int telem_priority;
  int telem_active;
  int ip1;
  int ip2;
  int ip3;
  int ip4;

private:
 std::ifstream params;
 std::string file_name;
 int output[23];
 std::string line;
};

#endif
