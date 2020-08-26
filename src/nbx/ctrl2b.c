// SPDX-License-Identifier: LGPL-3.0
#include <ctrl2b/functions/ctrl2b.h>

#include <assert.h>


void ctrl2b_sum(struct ctrl2b_sum_nbx *b)
{
    assert(b);
    assert(b->gain);
    assert(b->in);
    assert(b->out);

    for (int i = 0; i < b->size; i++) {
        b->out[i] = 0.0;

        for (int j = 0; j < b->nr_signals; j++) {
            assert(b->in[j]);

            int index = j * b->size + i;
            b->out[i] += b->gain[index] * b->in[j][i];
        }
    }
}


void ctrl2b_sp_err(struct ctrl2b_sp_err_nbx *b)
{
    assert(b);
    assert(b->dsr);
    assert(b->msr);
    assert(b->err);

    for (int i = 0; i < b->size; i++) {
        b->err[i] = b->dsr[i] - b->msr[i];
    }
}


void ctrl2b_pid_blx(struct ctrl2b_pid_blx_nbx *b)
{
    assert(b);
    assert(b->dt);
    assert(b->kp);
    assert(b->ki);
    assert(b->kd);
    assert(b->dsr);
    assert(b->msr);
    assert(b->out);
    assert(b->integ);
    assert(b->err_prev);

    double dt = *b->dt;
    assert(dt != 0.0);

    for (int i = 0; i < b->size; i++) {
        double err = b->dsr[i] - b->msr[i];
        double prop  = err;
        double integ = b->integ[i] + err * dt;
        double deriv = (err - b->err_prev[i]) / dt;

        b->out[i] = b->kp[i] * prop + b->ki[i] * integ + b->kd[i] * deriv;

        b->integ[i] = integ;
        b->err_prev[i] = err;
    }
}


void ctrl2b_pid_comp(struct ctrl2b_pid_comp_nbx *b)
{
    assert(b);
    assert(b->err);
    assert(b->integ);
    assert(b->deriv);
    assert(b->err->size == b->integ->size);
    assert(b->integ->size == b->deriv->size);
    assert(b->deriv->size == b->sum->size);

    ctrl2b_sp_err(b->err);
    ctrl2b_integ(b->integ);
    ctrl2b_deriv(b->deriv);
    ctrl2b_sum(b->sum);
}


void ctrl2b_integ(struct ctrl2b_integ_nbx *b)
{
    assert(b);
    assert(b->dt);
    assert(b->err);
    assert(b->out);
    assert(b->integ);

    double dt = *b->dt;
    assert(dt != 0.0);

    for (int i = 0; i < b->size; i++) {
        b->integ[i] += b->err[i] * dt;
        b->out[i] = b->integ[i];
    }
}


void ctrl2b_deriv(struct ctrl2b_deriv_nbx *b)
{
    assert(b);
    assert(b->dt);
    assert(b->err);
    assert(b->out);
    assert(b->err_prev);

    double dt = *b->dt;
    assert(dt != 0.0);

    for (int i = 0; i < b->size; i++) {
        b->out[i] = (b->err[i] - b->err_prev[i]) / dt;

        b->err_prev[i] = b->err[i];
    }
}

