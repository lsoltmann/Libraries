/*
UBlox 7 & 8 GPS library

Lars Soltmann
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include "/home/pi/Navio/C++/Navio/SPIdev.h"

class Ublox {
public:
    Ublox(std::string name = "/dev/spidev0.0");
    int initialize();
    int messageType(unsigned char from_gps_data, unsigned char data_array[]);
    int getMessages();
    int decodeMessage(unsigned char data_array[]);

    double gps_lat;
    double gps_lon;
    float gps_itow;
    float gps_h;
    float gps_hmsl;
    float gps_N;
    float gps_E;
    float gps_D;
    float gps_3D;
    float gps_2D;
    float gps_crs;
    int gps_stat;

private:
    std::string spi_device_name;
    unsigned char from_gps_data;
    unsigned char to_gps_data;
    unsigned char data_array;
    int disableNMEA_GLL();
    int disableNMEA_GGA();
    int disableNMEA_GSA();
    int disableNMEA_GSV();
    int disableNMEA_RMC();
    int disableNMEA_VTG();
    int enableNAV_POSLLH();
    int enableNAV_STATUS();
    int enableNAV_VELNED();
    int enableNAV_PVT();
    int setNavEngine();
    int setRATE();
    int GNSS_Reset();
    int message_ID;
    int message_flag;
    int typeFlag;
    int spi_transfer_data_length;
    int init_error;
};
