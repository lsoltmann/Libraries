/*
 PID.cpp
 
 Description: PID control functions
 
 
 Revision History
 Rev A - 26 April 2015 - Created and debugged
 
 Author: Lars Soltmann
 */

#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

#include "PID.h"

CONTROL::CONTROL(){
    p_error_sum=&error_sum;
    p_error_previous=&error_previous;
    p_t_previous=&t_previous;
    *p_error_sum=0;
    *p_error_previous=0;
    *p_t_previous=0;
    
};

CONTROL::~CONTROL(){
};

void CONTROL::reset(){
    *p_error_sum=0;
    *p_error_previous=0;
    *p_t_previous=0;
};

float CONTROL::PID(float P, float I, float D, float target, float actual){
    // Get current time to find differential time element
    gettimeofday(&tv,NULL);
    t = 1000000 * tv.tv_sec + tv.tv_usec;
    dt=t-*p_t_previous;

    // Calculate current error
    error=target-actual;

    // Estimate derivative of error
    _derivative=(error-*p_error_previous)/dt;

    // Estimate integral of error
    *p_error_sum+=error;
	if (*p_error_sum > I_UL) {
        	*p_error_sum=I_UL;
    	}
    	if (*p_error_sum < I_LL) {
        	*p_error_sum=I_LL;
    	}
    _integral=(*p_error_sum)*dt;

    // Apply integrator limits
/*    if (_integral > I_UL)
    {
	_integral=I_UL;
    }
    if (_integral < I_LL)
    {
  	_integral=I_LL;
    }
*/
    // Calculate control input
    control_input=P*error+D*_derivative+I*_integral;

    // Apply controller limits
/*    if (control_input > CI_UL) {
        control_input=CI_UL;
    }
    else if (control_input < CI_LL) {
        control_input=CI_LL;
    }
*/
    // Safe time and error values for next loop;
    *p_t_previous=t;

    return control_input;
};





