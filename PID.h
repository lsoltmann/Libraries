/*
 PID.h

 Description: Header for PID library

 Revision History
 Rev A - 26 April 2015 - Created and debugged
 Rev B - 27 May 2015 - Clean up

 Author: Lars Soltmann
 */

#ifndef PID_lib
#define PID_lib

#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

#define I_UL 1000
#define I_LL -1000

class CONTROL
    {
    public:
        CONTROL();
        ~CONTROL();
        float PID(float P, float I, float D, float target, float actual);
        void reset();
	float control_input;

    private:
        float _integral;
        float _derivative;
        float error;
        float error_sum;
        float error_previous;
        float t_previous;
        unsigned long t;
        float dt;
        struct timeval tv;
    };
#endif
