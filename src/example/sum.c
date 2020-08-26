// SPDX-License-Identifier: LGPL-3.0
#include <ctrl2b/functions/ctrl2b.h>

#include <stdio.h>

#define NR_JOINTS 2
#define NR_SIGNALS 3


int main(void)
{
    double gain[NR_SIGNALS][NR_JOINTS] = {
        { 1.0, 1.0 },
        { 1.0, 1.0 },
        { 1.0, 1.0 }
    };
    const double **in = (const double *[NR_SIGNALS]) {
        (double [NR_JOINTS]) { 1.0, 2.0 },
        (double [NR_JOINTS]) { 3.0, 4.0 },
        (double [NR_JOINTS]) { 5.0, 6.0 }
    };
    double out[NR_JOINTS];

    struct ctrl2b_sum_nbx sum_nbx = {
        // Configuration
        .size = NR_JOINTS,
        .nr_signals = NR_SIGNALS,
        .gain = gain[0],

        // Connections
        .in = in,
        .out = out
    };

    ctrl2b_sum(&sum_nbx);
    printf("%f - %f\n", out[0], out[1]);

    return 0;
}
