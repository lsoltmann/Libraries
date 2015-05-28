/*
 PID.cpp

 Description: PID control functions

 Revision History
 Rev A - 26 April 2015 - Created and debugged
 Rev B - 27 May 2015 - clean up

 Author: Lars Soltmann
 */

#include "PID.h"

CONTROL::CONTROL(){
    error_sum=0;
    error_previous=0;
    t_previous=0;
};

CONTROL::~CONTROL(){
};

void CONTROL::reset(){
    error_sum=0;
    error_previous=0;
    t_previous=0;
};

double CONTROL::PID(float P, float I, float D, float target, float actual){
    // Get current time to find differential time element
    gettimeofday(&tv,NULL);
    t = 1000000 * tv.tv_sec + tv.tv_usec;
    dt=(t-t_previous)/1000000.0;

    // Calculate current error
    error=target-actual;

    // Estimate derivative of error
    _derivative=(error-error_previous)/dt;

    // Estimate integral of error
    error_sum+=error;

    // Apply integrator limits through error limiting
    if (error_sum > I_UL) {
    	error_sum=I_UL;
    }
    if (error_sum < I_LL) {
       	error_sum=I_LL;
    }
    _integral=(error_sum)*dt;

    // Calculate control input
    control_input=P*error+D*_derivative+I*_integral;

    // Safe time and error values for next loop;
    t_previous=t;
    error_previous=error;

    return control_input;
};





