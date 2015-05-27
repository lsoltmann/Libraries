/*
Kalman1D.cpp

Description: 1D kalman filter
    System model: x(i+1)=x(i);


Revision History
Rev A - 09 May 2015 - Created and debugged

Author: Lars Soltmann
*/

#include "Kalman1D.h"

KF1D::KF1D(){}

K1FD::~KF1D(){}

void K1FD::initialize(double x_init){
    x=x_init;
    p=0;
}

double K1FD::currentState(double meas, double x, double q, double r){
    p=p+q;
    k=p/(p+r);
    x=x+k*(meas-x);
    p=(1-k)*p;
    
    return x;
}
