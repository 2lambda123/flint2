/*
    Copyright (C) 2013 Mike Hansen

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include <string.h>
#include "ulong_extras.h"
#include "fq_zech.h"

void
fq_zech_mul(fq_zech_t rop, const fq_zech_t op1, const fq_zech_t op2,
            const fq_zech_ctx_t ctx)
{
    if (op1->value == ctx->qm1 || op2->value == ctx->qm1)
    {
        rop->value = ctx->qm1;
        return;
    }
    rop->value = n_addmod(op1->value, op2->value, ctx->qm1);
}
