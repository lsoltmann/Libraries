/*
readConfig.cpp
 
 Description: Rudimentary configuration file reader for NavDAQ
 
 Revision History
 Rev A - 19 June 2015 - Created and debugged
 
 Author: Lars Soltmann
 */
 
 #include "readConfig.h"
 
 readConfig::readConfig(std::string name) : file_name(name) {
}

int readConfig::readfile(){
	open_error=0;
	params.open(file_name.c_str());
	if (params.is_open()) {
		std::getline(params,line);
		std::getline(params,line);
		std::getline(params,line);
		std::getline(params,line);
		sscanf(line.c_str(),"%d",&output[0]);
		std::getline(params,line);
		std::getline(params,line);
		std::getline(params,line);
		std::getline(params,line);
                sscanf(line.c_str(),"%d %d %d %d %d %d %d %d %d %d",&output[1],&output[2],&output[3],&output[4],&output[5],&output[6],&output[7],&output[8],&output[9],&output[10]);
		std::getline(params,line);
                std::getline(params,line);
                std::getline(params,line);
		std::getline(params,line);
                sscanf(line.c_str(),"%d %d %d %d %d",&output[11],&output[12],&output[13],&output[14],&output[15]);
		std::getline(params,line);
                std::getline(params,line);
                std::getline(params,line);
		sscanf(line.c_str(),"%d",&output[16]);
	
		dataSampleRate=output[0];
		MS5805_active=output[1];
		MS5611_active=output[2];
  		PPMdecode_active=output[3];
  		AHRS_active=output[4];
  		GPS_active=output[5];
  		MS4515_active=output[6];
  		SSC005D_active=output[7];
  		ADC_active=output[8];
  		RPM_active=output[9];
  		IMU_active=output[10];
  		gps_priority=output[11];
  		ppm_priority=output[12];
  		MS5611_priority=output[13];
  		MS5805_priority=output[14];
  		ahrs_priority=output[15];
  		OUTPUT_TO_SCREEN=output[16];
	}
	else{
		open_error++;
	}
/*	
	//Debug
	cout << output[0] << "\n";
	cout << output[1] << "\n";
	cout << output[2] << "\n";
	cout << output[3] << "\n";
	cout << output[4] << "\n";
    	cout << output[5] << "\n";
    	cout << output[6] << "\n";
    	cout << output[7] << "\n";
    	cout << output[8] << "\n";
    	cout << output[9] << "\n";
    	cout << output[10] << "\n";
    	cout << output[11] << "\n";
      	cout << output[12] << "\n";
      	cout << output[13] << "\n";
      	cout << output[14] << "\n";
     	cout << output[15] << "\n";
     	cout << output[16] << "\n";
*/
	params.close();
}
