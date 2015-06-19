/*
readConfig.h
 
 Description: Header for configuration reader library
 
 Revision History
 Rev A - 19 June 2015 - Created and debugged
 
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
  void readfile();
  int error_flag;
  int output[17]; 
  string line;
  int counter;
}
