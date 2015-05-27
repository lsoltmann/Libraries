//
//  Kalman1D.h
//  
//
//  Created by Lars Soltmann on 5/9/15.
//
//

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
