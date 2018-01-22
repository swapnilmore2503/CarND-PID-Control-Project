#include <iostream>
#include <stdlib.h>
#include "PID.h"
#define intervallen 25

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
    
    interval = (int*) calloc(intervallen, sizeof(interval[0]));
    i = intervallen - 1;
    sum = 0;
}

void PID::UpdateError(double cte) {
}

double PID::TotalError() {
}

