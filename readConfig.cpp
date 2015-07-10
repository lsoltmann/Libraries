/*
readConfig.cpp

 Description: Rudimentary configuration file reader for NavDAQ

 Revision History
 19 June 2015 - Created and debugged
 10 July 2015 - Added telemetry variables

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
		sscanf(line.c_str(),"%d",&output[1]);
		std::getline(params,line);
		std::getline(params,line);
		std::getline(params,line);
		std::getline(params,line);
                sscanf(line.c_str(),"%d %d %d %d %d %d %d %d %d %d",&output[2],&output[3],&output[4],&output[5],&output[6],&output[7],&output[8],&output[9],&output[10],&output[11]);
		std::getline(params,line);
                std::getline(params,line);
                std::getline(params,line);
		std::getline(params,line);
                sscanf(line.c_str(),"%d %d %d %d %d %d",&output[12],&output[13],&output[14],&output[15],&output[16],&output[17]);
		std::getline(params,line);
                std::getline(params,line);
                std::getline(params,line);
		sscanf(line.c_str(),"%d",&output[18]);
		std::getline(params,line);
                std::getline(params,line);
                std::getline(params,line);
		sscanf(line.c_str(),"%d",&output[19]);
		std::getline(params,line);
                std::getline(params,line);
                std::getline(params,line);
		sscanf(line.c_str(),"%d.%d.%d.%d:%d",&output[20],&output[21],&output[22],&output[23],&output[24]);

		dataSampleRate=output[0];
		sys_orientation=output[1];
		MS5805_active=output[2];
		MS5611_active=output[3];
  		PPMdecode_active=output[4];
  		AHRS_active=output[5];
  		GPS_active=output[6];
  		MS4515_active=output[7];
  		SSC005D_active=output[8];
  		ADC_active=output[9];
  		RPM_active=output[10];
  		IMU_active=output[11];
  		gps_priority=output[12];
  		ppm_priority=output[13];
  		MS5611_priority=output[14];
  		MS5805_priority=output[15];
  		ahrs_priority=output[16];
  		telem_priority=output[17];
  		OUTPUT_TO_SCREEN=output[18];
  		telem_active=output[19];
  		ip1=output[20];
  		ip2=output[21];
  		ip3=output[22];
  		ip4=output[23];
  		udpport=output[24];
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
     	cout << output[17] << "\n";
     	cout << output[18] << "\n";
    	cout << output[19] << "\n";
    	cout << output[20] << "\n";
    	cout << output[21] << "\n";
      	cout << output[22] << "\n";
      	cout << output[23] << "\n";
*/
	params.close();
	return open_error;
}
