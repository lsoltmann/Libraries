/*
Kalman1D.h

Description: Header file for 1D kalman filter

Revision History
Rev A - 09 May 2015 - Created and debugged

Author: Lars Soltmann
*/

#ifndef ____Kalman1D__
#define ____Kalman1D__

class KF1D{
public:
    KF1D();
    ~KF1D();
    void initialize(double x_init);
    double currentState(double meas, double x, double q, double r);
    
private:
    double x_init;
    double x;
    double p;
    double q;
    double r;
    double meas;
};


#endif
