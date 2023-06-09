/*
    Copyright (C) 2014 William Hart

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#define FQ_ZECH_INLINES_C

#include "fmpz.h"
#include "fq_nmod.h"
#include "fq_zech.h"

void __fq_zech_ctx_prime(fmpz_t p, fq_zech_ctx_t ctx)
{
   fmpz_set(p, fq_zech_ctx_prime(ctx));
}
