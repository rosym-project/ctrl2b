// SPDX-License-Identifier: LGPL-3.0
#include <ctrl2b/functions/ctrl2b.h>

#include <stdio.h>

#define NR_JOINTS 2


int main(void)
{
    double set[NR_JOINTS] = { -1.0, 1.0 };
    double msr[NR_JOINTS] = { -0.1, 0.1 };

    double err[NR_JOINTS] = {  0.0, 0.0 };

    double integ[NR_JOINTS] = { 0.0, 0.0 };
    double integ_int[NR_JOINTS] = { 0.0, 0.0 };

    double deriv[NR_JOINTS] = { 0.0, 0.0 };
    double err_prev[NR_JOINTS] = { 0.0, 0.0 };

    double cycle_time = 0.1;
    double gain[3][NR_JOINTS] = {
            { 3.0, 3.0 },   // kp
            { 2.0, 2.0 },   // ki
            { 1.0, 1.0 }    // kd
    };
    const double **sum = (const double *[3]) { err, integ, deriv };
    double out[NR_JOINTS];

    struct ctrl2b_sp_err_nbx err_nbx = {
        // Configuration
        .size = NR_JOINTS,
        // Connections
        .dsr = set, .msr = msr, .err = err
    };

    struct ctrl2b_integ_nbx integ_nbx = {
        // Configuration
        .size = NR_JOINTS, .dt = &cycle_time,
        // Connections
        .err = err, .out = integ,
        // Internal state,
        .integ = integ_int
    };

    struct ctrl2b_deriv_nbx deriv_nbx = {
        // Configuration
        .size = NR_JOINTS, .dt = &cycle_time,
        // Connections
        .err = err, .out = deriv,
        // Internal state,
        .err_prev = err_prev
    };

    struct ctrl2b_sum_nbx sum_nbx = {
        // Configuration
        .size = NR_JOINTS, .nr_signals = 3, .gain = gain[0],
        // Connections
        .in = sum, .out = out
    };

    struct ctrl2b_pid_comp_nbx pid_nbx = {
        // Composition
        .err = &err_nbx,
        .integ = &integ_nbx,
        .deriv = &deriv_nbx,
        .sum = &sum_nbx
    };

    ctrl2b_pid_comp(&pid_nbx);
    printf("%f - %f\n", out[0], out[1]);

    return 0;
}
