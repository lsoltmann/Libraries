/*
 UbloxGPS.cpp
 
 Description: Driver for UBlox NEO-7M and NEO-M8N
 
 
 Revision History
 Rev A - 27 May 2015 - Created and debugged
 
 Author: Lars Soltmann
 Code contribution: EMLID
 */

#include "UbloxGPS.h"

Ublox::Ublox(std::string name) : spi_device_name(name) {
}


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

int Ublox::setRATE()
{
    unsigned char gps_rate[] = {0xb5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xFA, 0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x96};
    int gps_rate_length = (sizeof(gps_rate)/sizeof(*gps_rate));
    unsigned char from_gps_data_nav[gps_rate_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_rate, from_gps_data_nav, gps_rate_length, 5000000);
}

int Ublox::enableNAV_STATUS()
{
    unsigned char gps_nav_status[] = {0xb5, 0x62, 0x06, 0x01, 0x03, 0x00, 0x01, 0x03, 0x01, 0x0F, 0x49};
    int gps_nav_status_length = (sizeof(gps_nav_status)/sizeof(*gps_nav_status));
    unsigned char from_gps_data_nav[gps_nav_status_length];

    return SPIdev::transfer(spi_device_name.c_str(), gps_nav_status, from_gps_data_nav, gps_nav_status_length, 5000000);
}


int Ublox::initialize()
{
    // Enable messages / settings
    init_error=0;

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
    unsigned char data_array[44] = {0x00};
    int message_flag=0;
    int typeFlag=0;
    int spi_transfer_data_length=1;

    // Variable initialization
    double gps_lat=0;
    double gps_lon=0;
    float gps_h=0;
    float gps_N=0;
    float gps_E=0;
    float gps_D=0;
    float gps_3D=0;
    float gps_2D=0;
    float gps_crs=0;
    int gps_stat=0;

    while (true)
    {
	for (int i = 0; i <= spi_transfer_data_length-1; i++)
	{
    		SPIdev::transfer(spi_device_name.c_str(), &to_gps_data, &from_gps_data, 1, 5000000);
    		data_array[i+4]=from_gps_data;
	}
/*
printf("array 0 = %X\n",data_array[0]);
printf("array 1 = %X\n",data_array[1]);
printf("array 2 = %X\n",data_array[2]);
printf("array 3 = %X\n",data_array[3]);
printf("array 4 = %X\n",data_array[4]);
printf("array 5 = %X\n",data_array[5]);
printf("array 6 = %X\n",data_array[6]);
printf("array 7 = %X\n",data_array[7]);
printf("array 8 = %X\n",data_array[8]);
printf("array 9 = %X\n",data_array[9]);
printf("array 10 = %X\n",data_array[10]);
printf("array 11 = %X\n",data_array[11]);
printf("array 12 = %X\n",data_array[12]);
printf("array 13 = %X\n",data_array[13]);
printf("array 14 = %X\n",data_array[14]);
printf("array 15 = %X\n",data_array[15]);
printf("array 16 = %X\n",data_array[16]);
printf("array 17 = %X\n",data_array[17]);
printf("array 18 = %X\n",data_array[18]);
printf("array 19 = %X\n",data_array[19]);
printf("array 20 = %X\n",data_array[20]);
printf("array 21 = %X\n",data_array[21]);
printf("array 22 = %X\n",data_array[22]);
printf("array 23 = %X\n",data_array[23]);
printf("array 24 = %X\n",data_array[24]);
printf("array 25 = %X\n",data_array[25]);
printf("array 26 = %X\n",data_array[26]);
printf("array 27 = %X\n",data_array[27]);
printf("array 28 = %X\n",data_array[28]);
printf("array 29 = %X\n",data_array[29]);
printf("array 30 = %X\n",data_array[30]);
printf("array 31 = %X\n",data_array[31]);
printf("array 32 = %X\n",data_array[32]);
printf("array 33 = %X\n",data_array[33]);
printf("array 34 = %X\n",data_array[34]);
printf("array 35 = %X\n",data_array[35]);
printf("array 36 = %X\n",data_array[36]);
printf("array 37 = %X\n",data_array[37]);
printf("array 38 = %X\n",data_array[38]);
printf("array 39 = %X\n",data_array[39]);
printf("array 40 = %X\n",data_array[40]);
printf("array 41 = %X\n",data_array[41]);
printf("array 42 = %X\n",data_array[42]);
printf("array 43 = %X\n\n",data_array[43]);
*/
	if (message_flag == 0 ){
		message_ID = messageType(from_gps_data, data_array);
//		printf("Message ID = %X\n",message_ID);
		switch(message_ID){
		case 0x03:
        		spi_transfer_data_length = 20;
        		message_flag=1;
//			printf("Message 3\n");
			break;
		case 0x02:
                        spi_transfer_data_length = 32;
                        message_flag=1;
//			printf("Message 2\n");
			break;
		case 0x12:
                        spi_transfer_data_length = 40;
                        message_flag=1;
//			printf("Message 12\n");
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

int Ublox::messageType(unsigned char from_gps_data, unsigned char data_array[44]){
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


int Ublox::decodeMessage(unsigned char data_array[44]){
	switch(data_array[3]) {
        	case 0x02:
                        gps_lat=(((data_array[17]) << 24) | ((data_array[16]) << 16) | ((data_array[15]) << 8) | (data_array[14]))/10000000;
                        gps_lon=(((data_array[13]) << 24) | ((data_array[12]) << 16) | ((data_array[11]) << 8) | (data_array[10]))/10000000;
                        gps_h=(((data_array[21]) << 24) | ((data_array[20]) << 16) | ((data_array[19]) << 8) | (data_array[18]))/1000;
			gps_hmsl=(((data_array[25]) << 24) | ((data_array[24]) << 16) | ((data_array[23]) << 8) | (data_array[22]))/1000;
			break;
                case 0x03:
			gps_itow=(((data_array[9]) << 24) | ((data_array[8]) << 16) | ((data_array[7]) << 8) | (data_array[6]))/1000;
                        gps_stat=(int)data_array[10];
			break;
                case 0x12:
                        gps_N=(((data_array[13]) << 24) | ((data_array[12]) << 16) | ((data_array[11]) << 8) | (data_array[10]));
                        gps_E=(((data_array[17]) << 24) | ((data_array[16]) << 16) | ((data_array[15]) << 8) | (data_array[14]));
                        gps_D=(((data_array[21]) << 24) | ((data_array[20]) << 16) | ((data_array[19]) << 8) | (data_array[18]));
                        gps_3D=(((data_array[25]) << 24) | ((data_array[24]) << 16) | ((data_array[23]) << 8) | (data_array[22]));
                        gps_2D=(((data_array[29]) << 24) | ((data_array[28]) << 16) | ((data_array[27]) << 8) | (data_array[26]));
                        gps_crs=(((data_array[33]) << 24) | ((data_array[32]) << 16) | ((data_array[31]) << 8) | (data_array[30]))/100000;
			break;
                }
// Debug
/*    printf("itow: %lf\n",gps_itow);
    printf("lat: %lf\n",gps_lat);
    printf("lon: %lf\n",gps_lon);
    printf("h: %lf\n",gps_h);
    printf("hmsl: %lf\n",gps_hmsl);
    printf("N: %lf\n",gps_N);
    printf("E: %lf\n",gps_E);
    printf("D: %lf\n",gps_D);
    printf("3D: %lf\n",gps_3D);
    printf("2D: %lf\n",gps_2D);
    printf("crs: %lf\n",gps_crs);
    printf("stat: %d\n\n",gps_stat);
*/
		return 0;
}
