/*
 * ConfInterval.cpp
 *
 *  Created on: 9 de ago de 2020
 *      Author: vini
 */

#include "ConfInterval.h"

double T_STUDENT[20][3] = {
        {6.3138, 12.706, 63.657},
        {2.92, 4.3127, 9.9248},
        {2.3534, 3.1825, 5.8409},
        {2.1318, 2.7764, 4.6041},

        {2.0150, 2.5706, 4.0321},
        {1.9432, 2.4469, 3.7074},
        {1.8946, 2.3646, 3.4995},
        {1.8595, 2.3060, 3.3554},
        {1.8331, 2.2622, 3.2498},

        {1.8125, 2.2281, 3.1693},
        {1.7959, 2.2010, 3.1058},
        {1.7823, 2.1788, 3.9545},
        {1.7709, 2.1604, 3.0123},
        {1.7613, 2.1448, 2.9768},

        {1.7530, 2.1315, 2.9467},
        {1.7459, 2.1199, 2.9208},
        {1.7396, 2.1098, 2.8982},
        {1.7341, 2.1009, 2.8784},
        {1.7291, 2.0930, 2.8609},

        {1.7247, 2.0860, 2.8453},
};


ConfInterval::~ConfInterval() {
    // TODO Auto-generated destructor stub
}

void ConfInterval::calc_med() {
    int i;

    for(i=0;i<len;i++) {
        x_tmrs += tmrs[i];
        x_us += us[i];
        x_vs += vs[i];
        x_tmf += tmf[i];
    }

    x_tmrs = x_tmrs/len;
    x_us = x_us/len;
    x_vs = x_vs/len;
    x_tmf = x_tmf/len;
}

void ConfInterval::calc_var() {
    int i;

    for(i=0;i<len;i++){
        var_tmrs += pow(tmrs[i] - x_tmrs, 2.0);
        var_us += pow(us[i] - x_us, 2.0);
        var_vs += pow(vs[i] - x_vs, 2.0);
        var_tmf += pow(tmf[i] - x_tmf, 2.0);
    }

    var_tmrs = var_tmrs / (len-1);
    var_us = var_us / (len-1);
    var_vs = var_vs / (len-1);
    var_tmf = var_tmf / (len-1);
}

void ConfInterval::calc_des() {
    des_tmrs = sqrt(var_tmrs);
    des_us = sqrt(var_us);
    des_vs = sqrt(var_vs);
    des_tmf = sqrt(var_tmf);
}

double ConfInterval::get_repeticoes(int interval, double error) {
    if (len < 2)
        return 0;

    return pow((100*T_STUDENT[len-2][interval]*des_tmf)/(error*x_tmf), 2.0);
}

void ConfInterval::calc_all(){
    calc_med();
    calc_var();
    calc_des();
}




