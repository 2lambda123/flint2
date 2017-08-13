/*
    Copyright (C) 2016 William Hart

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include <gmp.h>
#include <stdlib.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_mpoly.h"

void fmpz_mpoly_set_monomial(fmpz_mpoly_t poly, 
                       slong n, const ulong * exps, const fmpz_mpoly_ctx_t ctx)
{
   slong i, bits, max_bits, N;
   ulong maxdeg = 0;
   int deg, rev;

   degrev_from_ord(deg, rev, ctx->ord);

   if (deg)
   {
      for (i = 0; i < ctx->n - 1; i++)
         maxdeg += exps[i];
   } else
   {
      for (i = 0; i < ctx->n; i++)
      {
         if (exps[i] > maxdeg)
            maxdeg = exps[i];
      }
   }

   max_bits = poly->bits;
   bits = FLINT_BIT_COUNT(maxdeg);
   
   while (bits >= max_bits)
      max_bits *= 2;

   /* reallocate the number of bits of the exponents of the polynomial */
   fmpz_mpoly_fit_bits(poly, max_bits, ctx);

   if (n > poly->length)
      flint_throw(FLINT_ERROR, "Invalid index in fmpz_mpoly_set_monomial");

   fmpz_mpoly_fit_length(poly, n + 1, ctx);

   N = (poly->bits*ctx->n - 1)/FLINT_BITS + 1;
   
   mpoly_set_monomial(poly->exps + n*N, exps, poly->bits, ctx->n, deg, rev);

   if (n == poly->length)
      _fmpz_mpoly_set_length(poly, n + 1, ctx);
}
