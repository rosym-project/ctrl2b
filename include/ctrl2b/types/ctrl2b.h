// SPDX-License-Identifier: LGPL-3.0
#ifndef CTRL2B_TYPES_CTRL2B_H
#define CTRL2B_TYPES_CTRL2B_H

#ifdef __cplusplus
extern "C" {
#endif

struct ctrl2b_sum_nbx
{
    // Configuration
    int size;
    int nr_signals;
    const double *gain;     // [size * nr_signal]

    // Ports
    const double **in;      // [size][nr_signals]
    double *out;            // [size]
};


struct ctrl2b_sp_err_nbx
{
    // Configuration
    int size;

    // Ports
    const double *dsr;  // [size]
    const double *msr;  // [size]
    double *err;        // [size]
};


struct ctrl2b_integ_nbx
{
    // Configuration
    int size;
    const double *dt;   // [1]

    // Ports
    const double *err;  // [size]
    double *out;        // [size]

    // Internal state
    double *integ;      // [size]
};


struct ctrl2b_deriv_nbx
{
    // Configuration
    int size;
    const double *dt;   // [1]

    // Ports
    const double *err;  // [size]
    double *out;        // [size]

    // Internal state
    double *err_prev;   // [size]
};


struct ctrl2b_pid_blx_nbx
{
    // Configuration
    int size;
    const double *kp;   // [size]
    const double *ki;   // [size]
    const double *kd;   // [size]
    const double *dt;   // [1]

    // Ports
    const double *dsr;  // [size]
    const double *msr;  // [size]
    double *out;        // [size]

    // Internal state
    double *integ;      // [size]
    double *err_prev;   // [size]
};


struct ctrl2b_pid_comp_nbx
{
    // Composition
    struct ctrl2b_sp_err_nbx *err;
    struct ctrl2b_deriv_nbx *deriv;
    struct ctrl2b_integ_nbx *integ;
    struct ctrl2b_sum_nbx *sum;
};

#ifdef __cplusplus
}
#endif

#endif
