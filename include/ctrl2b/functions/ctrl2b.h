// SPDX-License-Identifier: LGPL-3.0
#ifndef CTRL2B_FUNCTIONS_CTRL2B_H
#define CTRL2B_FUNCTIONS_CTRL2B_H

#include <ctrl2b/types/ctrl2b.h>


#ifdef __cplusplus
extern "C" {
#endif

void ctrl2b_sum(struct ctrl2b_sum_nbx *b);

void ctrl2b_sp_err(struct ctrl2b_sp_err_nbx *b);

void ctrl2b_integ(struct ctrl2b_integ_nbx *b);

void ctrl2b_deriv(struct ctrl2b_deriv_nbx *b);

void ctrl2b_pid_blx(struct ctrl2b_pid_blx_nbx *b);

void ctrl2b_pid_comp(struct ctrl2b_pid_comp_nbx *b);

#ifdef __cplusplus
}
#endif

#endif
