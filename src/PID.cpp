#include <iostream>
#include <stdlib.h>
#include "PID.h"

#define intervallen 20

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    PID::Kp = Kp;
    PID::Ki = Ki;
    PID::Kd = Kd;
    p_error = 0;
    i_error = 0;
    d_error = 0;
    pre_cte = 0;
    interval = (int*) calloc(intervallen, sizeof(interval[0])) ;
    i = intervallen - 1 ;
    sum = 0 ;
}

void PID::UpdateError(double cte, double dt) {
    d_error = (cte - pre_cte) / dt;
    p_error = cte;
    i_error = total_i(cte * dt);
    pre_cte = cte;
    
}

// Adaptive PID control tuning parameters
// Reference: http://www.ece.eng.wayne.edu/~flin/Conference/AI-PID.pdf
// Higher the speed lower the Kp to reduce overshoot and higher the damping factor Kd
double PID::TotalError(double speed) {
    double a = 0.0032;
    double b = 0.0002;
    return (Kp - a * speed) * p_error + Ki * i_error + (Kd + b * speed) * d_error;
    //return -Kp * p_error - Ki * i_error - Kd * d_error;
}

// Calculate integral only over a small time interval to avoid cumulative integral bias
// Reference: https://stackoverflow.com/questions/25024012/running-sum-of-the-last-n-integers-in-an-array
double PID::total_i(double error){
    i = (i+1) % intervallen ;
    sum = sum - interval[i] + error ;
    return sum;
}

// Saturate Steer Value between [-1, 1]
double PID::saturate(double steer){
    if (steer > 1) {
        steer = 1;
    }
    else if (steer < -1) {
        steer = -1;
    }
    return steer;
}
