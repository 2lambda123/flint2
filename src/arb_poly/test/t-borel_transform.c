/*
    Copyright (C) 2013 Fredrik Johansson

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "arb_poly.h"

int main(void)
{
    slong iter;
    flint_rand_t state;

    flint_printf("borel_transform....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 10000 * 0.1 * flint_test_multiplier(); iter++)
    {
        arb_poly_t a, b, c, d;
        slong n, prec;

        arb_poly_init(a);
        arb_poly_init(b);
        arb_poly_init(c);
        arb_poly_init(d);

        n = n_randint(state, 30);
        prec = n_randint(state, 200);

        arb_poly_randtest(a, state, n, prec, 10);
        arb_poly_randtest(b, state, n, prec, 10);
        arb_poly_randtest(c, state, n, prec, 10);

        arb_poly_borel_transform(b, a, prec);
        arb_poly_inv_borel_transform(c, b, prec);

        if (!arb_poly_contains(c, a))
        {
            flint_printf("FAIL (containment)\n\n");
            flint_abort();
        }

        arb_poly_set(d, a);
        arb_poly_borel_transform(d, d, prec);
        if (!arb_poly_equal(d, b))
        {
            flint_printf("FAIL (aliasing 1)\n\n");
            flint_abort();
        }

        arb_poly_set(d, b);
        arb_poly_inv_borel_transform(d, d, prec);
        if (!arb_poly_equal(d, c))
        {
            flint_printf("FAIL (aliasing 2)\n\n");
            flint_abort();
        }

        arb_poly_clear(a);
        arb_poly_clear(b);
        arb_poly_clear(c);
        arb_poly_clear(d);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return 0;
}

