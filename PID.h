/*
 PID.h
 
 Description: Header for PID library
 
 
 Revision History
 Rev A - 26 April 2015 - Created and debugged
 
 Author: Lars Soltmann
 */

#ifndef PID_lib
#define PID_lib


#define I_UL 1000
#define I_LL -1000
//#define CI_UL 2.000 // servo pwm_ms max
//#define CI_LL 1.000 // servo pwm_ms min

class CONTROL
    {
    public:
        CONTROL();
        ~CONTROL();
        float PID(float P, float I, float D, float target, float actual);
        void reset();
        
    private:
        float _integral;
        float _derivative;
        float error;
        float *p_error_sum;
        float error_sum;
        float *p_error_previous;
        float error_previous;
        float *p_t_previous;
        float t_previous;
        unsigned long t;
        float dt;
        struct timeval tv;
        float control_input;
    };
#endif
