/*=============================================================================

    This file is part of Antic.

    Antic is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version. See <http://www.gnu.org/licenses/>.

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012 William Hart

******************************************************************************/

#include "qfb.h"

int main(void)
{
    int result;
    flint_rand_t state;
    slong i;

    printf("reduce....");
    fflush(stdout);

    flint_randinit(state);

    for (i = 1; i < 100000; i++)
    {
        fmpz_t D;
        qfb_t r;

        fmpz_init(D);
        qfb_init(r);

        do
        {
           fmpz_randtest_unsigned(r->a, state, 100);
           if (fmpz_is_zero(r->a))
              fmpz_set_ui(r->a, 1);

           fmpz_randtest(r->b, state, 100);
           fmpz_randtest(r->c, state, 100);

           qfb_discriminant(D, r);
        } while (fmpz_sgn(D) >= 0);

        qfb_reduce(r, r, D);

        result = (qfb_is_reduced(r));
        if (!result)
        {
           printf("FAIL:\n");
           qfb_print(r); printf("\n");
           flint_abort();
        }

        fmpz_clear(D);
        qfb_clear(r);
    }

    flint_randclear(state);
    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}
