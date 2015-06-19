readconfig::readconfig(){
	ifstream params;
	params.open("testconfig.txt");
	if (params.is_open()) {
		getline(params,line);
		getline(params,line);
		getline(params,line);
		getline(params,line);
		sscanf(line.c_str(),"%d",&output[0]);
		getline(params,line);
		getline(params,line);
		getline(params,line);
		getline(params,line);
                sscanf(line.c_str(),"%d %d %d %d %d %d %d %d %d %d",&output[1],&output[2],&output[3],&output[4],&output[5],&output[6],&output[7],&output[8],&output[9],&output[10]);
		getline(params,line);
                getline(params,line);
                getline(params,line);
		getline(params,line);
                sscanf(line.c_str(),"%d %d %d %d %d",&output[11],&output[12],&output[13],&output[14],&output[15]);
		getline(params,line);
                getline(params,line);
                getline(params,line);
		sscanf(line.c_str(),"%d",&output[16]);
	}
	else{
		error_flag++;
	}
	
/*	    //Debug
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
	return 0;
}
