/*
UBlox 7 & 8 GPS library for use with Navio/Navio+

Code by: Lars Soltmann
Code contribution by: EMLID
*/

#include "UbloxGPS.h"

Ublox::Ublox(std::string name) : spi_device_name(name) {
}


/* Enable / Disable various GPS messages

By default the only messages enabled are the following 6 NMEA messages
GLL,GGA,GSA,GSV,RMC,VTG
since we are using the UBX protocol instead of the NMEA protocol, these are just clogging up the buffer and have
been shown to cause significant time lag in the output. 


The follwing three messages are no longer used (POSLLH,VELNED,STATUS) but are left here anyway.
NAV-PVT contains the same data as the above mentioned messages with some additional useful information
and all with less data to transfer from the GPS, so win-win.
*/

int Ublox::enableNAV_POSLLH()
{
    unsigned char gps_nav_posllh[] = {0xb5, 0x62, 0x06, 0x01, 0x03, 0x00, 0x01, 0x02, 0x01, 0x0E, 0x47};
    int gps_nav_posllh_length = (sizeof(gps_nav_posllh)/sizeof(*gps_nav_posllh));
    unsigned char from_gps_data_nav[gps_nav_posllh_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_nav_posllh, from_gps_data_nav, gps_nav_posllh_length, 5000000);
}

int Ublox::enableNAV_VELNED()
{
    unsigned char gps_nav_velned[] = {0xb5, 0x62, 0x06, 0x01, 0x03, 0x00, 0x01, 0x12, 0x01, 0x1E, 0x67};
    int gps_nav_velned_length = (sizeof(gps_nav_velned)/sizeof(*gps_nav_velned));
    unsigned char from_gps_data_nav[gps_nav_velned_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_nav_velned, from_gps_data_nav, gps_nav_velned_length, 5000000);
}

int Ublox::enableNAV_STATUS()
{
    unsigned char gps_nav_status[] = {0xb5, 0x62, 0x06, 0x01, 0x03, 0x00, 0x01, 0x03, 0x01, 0x0F, 0x49};
    int gps_nav_status_length = (sizeof(gps_nav_status)/sizeof(*gps_nav_status));
    unsigned char from_gps_data_nav[gps_nav_status_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_nav_status, from_gps_data_nav, gps_nav_status_length, 5000000);
}

int Ublox::enableNAV_PVT()
{
    unsigned char gps_nav_status[] = {0xb5, 0x62, 0x06, 0x01, 0x03, 0x00, 0x01, 0x07, 0x01, 0x13, 0x51};
    int gps_nav_status_length = (sizeof(gps_nav_status)/sizeof(*gps_nav_status));
    unsigned char from_gps_data_nav[gps_nav_status_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_nav_status, from_gps_data_nav, gps_nav_status_length, 5000000);
}

int Ublox::setRATE()
{
    unsigned char gps_rate[] = {0xb5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xFA, 0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x96};
    int gps_rate_length = (sizeof(gps_rate)/sizeof(*gps_rate));
    unsigned char from_gps_data_nav[gps_rate_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_rate, from_gps_data_nav, gps_rate_length, 5000000);
}
/* Unfinished!
int Ublox::setNavEngine()
{
    unsigned char gps_rate[] = {0xb5, 0x62, 0x06, 0x24, 0x24, 0x00,...};
    int gps_rate_length = (sizeof(gps_rate)/sizeof(*gps_rate));
    unsigned char from_gps_data_nav[gps_rate_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_rate, from_gps_data_nav, gps_rate_length, 5000000);
}
*/
int Ublox::disableNMEA_GLL()
{
    unsigned char gps_nmea_gll[] = {0xb5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x2B};
    int gps_nmea_gll_length = (sizeof(gps_nmea_gll)/sizeof(*gps_nmea_gll));
    unsigned char from_gps_data_nmea[gps_nmea_gll_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_nmea_gll, from_gps_data_nmea, gps_nmea_gll_length, 5000000);
}

int Ublox::disableNMEA_GGA()
{
    unsigned char gps_nmea_gga[] = {0xb5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x24};
    int gps_nmea_gga_length = (sizeof(gps_nmea_gga)/sizeof(*gps_nmea_gga));
    unsigned char from_gps_data_nmea[gps_nmea_gga_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_nmea_gga, from_gps_data_nmea, gps_nmea_gga_length, 5000000);
}

int Ublox::disableNMEA_GSA()
{
    unsigned char gps_nmea_gsa[] = {0xb5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x32};
    int gps_nmea_gsa_length = (sizeof(gps_nmea_gsa)/sizeof(*gps_nmea_gsa));
    unsigned char from_gps_data_nmea[gps_nmea_gsa_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_nmea_gsa, from_gps_data_nmea, gps_nmea_gsa_length, 5000000);
}

int Ublox::disableNMEA_GSV()
{
    unsigned char gps_nmea_gsv[] = {0xb5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x39};
    int gps_nmea_gsv_length = (sizeof(gps_nmea_gsv)/sizeof(*gps_nmea_gsv));
    unsigned char from_gps_data_nmea[gps_nmea_gsv_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_nmea_gsv, from_gps_data_nmea, gps_nmea_gsv_length, 5000000);
}

int Ublox::disableNMEA_RMC()
{
    unsigned char gps_nmea_rmc[] = {0xb5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x40};
    int gps_nmea_rmc_length = (sizeof(gps_nmea_rmc)/sizeof(*gps_nmea_rmc));
    unsigned char from_gps_data_nmea[gps_nmea_rmc_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_nmea_rmc, from_gps_data_nmea, gps_nmea_rmc_length, 5000000);
}

int Ublox::disableNMEA_VTG()
{
    unsigned char gps_nmea_vtg[] = {0xb5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x05, 0x47};
    int gps_nmea_vtg_length = (sizeof(gps_nmea_vtg)/sizeof(*gps_nmea_vtg));
    unsigned char from_gps_data_nmea[gps_nmea_vtg_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_nmea_vtg, from_gps_data_nmea, gps_nmea_vtg_length, 5000000);
}

int Ublox::GNSS_Reset()
{
    unsigned char gps_gnss_rst[] = {0xb5, 0x62, 0x06, 0x04, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x10, 0x68};
    int gps_gnss_rst_length = (sizeof(gps_gnss_rst)/sizeof(*gps_gnss_rst));
    unsigned char from_gps_data_gnss[gps_gnss_rst_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_gnss_rst, from_gps_data_gnss, gps_gnss_rst_length, 5000000);
}

int Ublox::initialize()
{
    init_error=0;

    // Disable default NMEA messages
    if (disableNMEA_GLL()<0)
    {
	init_error++;
    }
    if (disableNMEA_GGA()<0)
    {
        init_error++;
    }
    if (disableNMEA_GSA()<0)
    {
        init_error++;
    }
    if (disableNMEA_GSV()<0)
    {
        init_error++;
    }
    if (disableNMEA_RMC()<0)
    {
        init_error++;
    }
    if (disableNMEA_VTG()<0)
    {
        init_error++;
    }

    // Enable UBX messages
/*
    if (enableNAV_POSLLH()<0)
    {
	init_error++;
    }
    if (enableNAV_VELNED()<0)
    {
        init_error++;
    }
    if (enableNAV_STATUS()<0)
    {
        init_error++;
    }
*/
    if (enableNAV_PVT()<0)
    {
        init_error++;
    }
    
    // Set navigation engine
    if (setNavEngine()<0)
    {
        init_error++;
    }
    
    // Set update rate
    if (setRATE()<0)
    {
        init_error++;
    }

    return init_error;
}


int Ublox::getMessages()
{
    int message_ID=0;
    unsigned char to_gps_data = 0x00, from_gps_data = 0x00;
    unsigned char data_array[100] = {0x00}; // 100 bytes is the size of the PVT message (92+8)
    int message_flag=0;
    int typeFlag=0;
    int spi_transfer_data_length=1;

    // Variable initialization
    double gps_lat=0;
    double gps_lon=0;
    float gps_h=0;
    float gps_hmsl=0;
    float gps_N=0;
    float gps_E=0;
    float gps_D=0;
    float gps_3D=0;
    float gps_2D=0;
    float gps_crs=0;
    int gps_stat=0;
    float gps_pdop=0;
    int gps_nsat=0;

    while (true)
    {
	for (int i = 0; i <= spi_transfer_data_length-1; i++)
	{
    		SPIdev::transfer(spi_device_name.c_str(), &to_gps_data, &from_gps_data, 1, 5000000);
    		data_array[i+4]=from_gps_data;
	}

	if (message_flag == 0 ){
		message_ID = messageType(from_gps_data, data_array);
		switch(message_ID){
		case 0x03:
        		spi_transfer_data_length = 20;
        		message_flag=1;
			break;
		case 0x02:
                        spi_transfer_data_length = 32;
                        message_flag=1;
			break;
		case 0x12:
                        spi_transfer_data_length = 40;
                        message_flag=1;
			break;
		case 0x07:
			spi_transfer_data_length = 96
			message_flag=1;
			break;
		}
	}
	else if (message_flag == 1)
	{
		decodeMessage(data_array);
	    	message_flag=0;
            	message_ID=0;
    		spi_transfer_data_length = 1;
		data_array [0] = 0x00;
		data_array [1] = 0x00;
		data_array [2] = 0x00;
		data_array [3] = 0x00;
		typeFlag=0;
        }

	if (message_flag == 0){
        	usleep(100);
    	}
    }

    return 0 ;
}

int Ublox::messageType(unsigned char from_gps_data, unsigned char data_array[100]){
	if (from_gps_data == 0xB5 && typeFlag == 0){
		typeFlag=1;
		data_array [0] = from_gps_data;
		message_ID=0;
	}
	else if (from_gps_data == 0x62 && typeFlag == 1){
		typeFlag=2;
		data_array [1] = from_gps_data;
		message_ID=0;
	}
	else if (typeFlag == 2){
		typeFlag=3;
		data_array [2] = from_gps_data;
		message_ID=0;
	}
        else if (typeFlag == 3){
                message_ID=from_gps_data;
                typeFlag=0;
		data_array [3] = message_ID;
        }
	else {
		typeFlag=0;
		message_ID=0;
	}

	return message_ID;
}


int Ublox::decodeMessage(unsigned char data_array[100]){
	switch(data_array[3]) {
        	case 0x02:
                        gps_lat=(double)(((data_array[17]) << 24) | ((data_array[16]) << 16) | ((data_array[15]) << 8) | (data_array[14]))/ (double)10000000; //deg
                        gps_lon=(double)(((data_array[13]) << 24) | ((data_array[12]) << 16) | ((data_array[11]) << 8) | (data_array[10]))/ (double)10000000;  //deg
                        gps_h=(float)(((data_array[21]) << 24) | ((data_array[20]) << 16) | ((data_array[19]) << 8) | (data_array[18]))*0.00328084;  //mm to ft
			gps_hmsl=(float)(((data_array[25]) << 24) | ((data_array[24]) << 16) | ((data_array[23]) << 8) | (data_array[22]))*0.00328084;  //mm to ft
			break;
                case 0x03:
			gps_itow=(float)(((data_array[9]) << 24) | ((data_array[8]) << 16) | ((data_array[7]) << 8) | (data_array[6]))/ (float)1000;  //sec
                        gps_stat=(int)data_array[10];
			break;
                case 0x12:
                        gps_N=(float)(((data_array[13]) << 24) | ((data_array[12]) << 16) | ((data_array[11]) << 8) | (data_array[10]))*0.0328084;  // cm/s to ft/s
                        gps_E=(float)(((data_array[17]) << 24) | ((data_array[16]) << 16) | ((data_array[15]) << 8) | (data_array[14]))*0.0328084;  // cm/s to ft/s
                        gps_D=(float)(((data_array[21]) << 24) | ((data_array[20]) << 16) | ((data_array[19]) << 8) | (data_array[18]))*0.0328084;  // cm/s to ft/s
                        gps_3D=(float)(((data_array[25]) << 24) | ((data_array[24]) << 16) | ((data_array[23]) << 8) | (data_array[22]))*0.0328084;  // cm/s to ft/s
                        gps_2D=(float)(((data_array[29]) << 24) | ((data_array[28]) << 16) | ((data_array[27]) << 8) | (data_array[26]))*0.0328084;  // cm/s to ft/s
                        gps_crs=(float)(((data_array[33]) << 24) | ((data_array[32]) << 16) | ((data_array[31]) << 8) | (data_array[30]))/ (float)100000;  //deg
			break;
		case 0x07: // check units!
			gps_lat=(double)(((data_array[37]) << 24) | ((data_array[36]) << 16) | ((data_array[35]) << 8) | (data_array[34]))/ (double)10000000; //deg
                        gps_lon=(double)(((data_array[33]) << 24) | ((data_array[32]) << 16) | ((data_array[31]) << 8) | (data_array[30]))/ (double)10000000;  //deg
                        gps_h=(float)(((data_array[41]) << 24) | ((data_array[40]) << 16) | ((data_array[39]) << 8) | (data_array[38]))*0.00328084;  //mm to ft
			gps_hmsl=(float)(((data_array[45]) << 24) | ((data_array[44]) << 16) | ((data_array[43]) << 8) | (data_array[42]))*0.00328084;  //mm to ft
			gps_stat=(int)data_array[26];
			gps_N=(float)(((data_array[57]) << 24) | ((data_array[56]) << 16) | ((data_array[55]) << 8) | (data_array[54]))*0.00328084;  // mm/s to ft/s
                        gps_E=(float)(((data_array[61]) << 24) | ((data_array[60]) << 16) | ((data_array[59]) << 8) | (data_array[58]))*0.00328084;  // mm/s to ft/s
                        gps_D=(float)(((data_array[65]) << 24) | ((data_array[64]) << 16) | ((data_array[63]) << 8) | (data_array[62]))*0.00328084;  // mm/s to ft/s
                        gps_2D=(float)(((data_array[69]) << 24) | ((data_array[68]) << 16) | ((data_array[67]) << 8) | (data_array[66]))*0.00328084;  // mm/s to ft/s
                        gps_3D=
                        gps_crs=(float)(((data_array[73]) << 24) | ((data_array[72]) << 16) | ((data_array[71]) << 8) | (data_array[70]))/ (float)100000;  //deg
                        gps_nsat=(int)data_array[29];
                        gps_pdop=(float)(((data_array[83]) << 8) | (data_array[82]))*0.01; // no units
                }
		return 0;
}
