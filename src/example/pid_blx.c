// SPDX-License-Identifier: LGPL-3.0
#include <ctrl2b/functions/ctrl2b.h>

#include <stdio.h>

#define NR_JOINTS 2


int main(void)
{
    double cycle_time = 0.1;
    double set[NR_JOINTS] = { -1.0, 1.0 };
    double msr[NR_JOINTS] = { -0.1, 0.1 };
    double out[NR_JOINTS];

    struct ctrl2b_pid_blx_nbx pid_nbx = {
        // Configuration
        .size = NR_JOINTS,
        .dt = &cycle_time,
        .kp = (double [NR_JOINTS]) { 3.0, 3.0 },
        .ki = (double [NR_JOINTS]) { 2.0, 2.0 },
        .kd = (double [NR_JOINTS]) { 1.0, 1.0 },
        // Connections
        .dsr = set,
        .msr = msr,
        .out = out,
        // Internal state
        .integ = (double [NR_JOINTS]) { 0.0, 0.0 },
        .err_prev = (double [NR_JOINTS]) { 0.0, 0.0 }
    };

    ctrl2b_pid_blx(&pid_nbx);
    printf("%f - %f\n", out[0], out[1]);

    return 0;
}
