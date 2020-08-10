/*
 * ConfInterval.h
 *
 *  Created on: 9 de ago de 2020
 *      Author: vini
 */

#ifndef CONFINTERVAL_H_
#define CONFINTERVAL_H_

#include <math.h>

#define CI_90 0
#define CI_95 1
#define CI_99 2

//double T_STUDENT[20][3];

class ConfInterval {
public:
    ConfInterval(double *trms, double *us, double *vs, double *tmf, int len) :
        tmrs(tmrs), us(us), vs(vs), tmf(tmf), len(len)
        { var_tmrs = var_us = var_vs = var_tmf = 0;
          des_tmrs = des_us = des_vs = des_tmf = 0;
          x_tmrs = x_us = x_vs = x_tmf = 0; }

    virtual ~ConfInterval();

    void calc_all();
    void calc_med();
    void calc_var();
    void calc_des();

    double get_repeticoes(int interval, double error);


private:
    double *tmrs, *us, *vs, *tmf;
    double var_tmrs, var_us, var_vs, var_tmf;
    double des_tmrs, des_us, des_vs, des_tmf;
    double x_tmrs, x_us, x_vs, x_tmf;
    int len;
};

#endif /* CONFINTERVAL_H_ */
