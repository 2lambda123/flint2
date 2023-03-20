/*
    Copyright (C) 2020 Fredrik Johansson

    This file is part of Calcium.

    Calcium is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "ca_mat.h"

truth_t
ca_mat_check_equal(const ca_mat_t A, const ca_mat_t B, ca_ctx_t ctx)
{
    slong i, j;
    truth_t res, eq;

    flint_printf("inside ca_mat_check_equal\n");
    fflush(stdout);

    if ((ca_mat_nrows(A) != ca_mat_nrows(B)) ||
        (ca_mat_ncols(A) != ca_mat_ncols(B)))
    {
        return T_FALSE;
    }

    res = T_TRUE;

    for (i = 0; i < ca_mat_nrows(A); i++)
    {
        for (j = 0; j < ca_mat_ncols(A); j++)
        {
            flint_printf("i = " WORD_FMT "d, j = " WORD_FMT "\n", i, j);
            fflush(stdout);

            eq = ca_check_equal(ca_mat_entry(A, i, j), ca_mat_entry(B, i, j), ctx);

            flint_printf("after small check\n");
            fflush(stdout);

            if (eq == T_FALSE)
                return T_FALSE;
            if (eq == T_UNKNOWN)
                res = T_UNKNOWN;
        }
    }

    return res;
}
