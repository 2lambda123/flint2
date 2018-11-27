/*
    Copyright (C) 2017 Daniel Schultz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "nmod_mpoly.h"

void nmod_mpoly_set_ui(nmod_mpoly_t A, ulong c, const nmod_mpoly_ctx_t ctx)
{
    slong N;

    N = mpoly_words_per_exp(A->bits, ctx->minfo);

    if (c >= ctx->ffinfo->mod.n)
    {
        NMOD_RED(c, c, ctx->ffinfo->mod);
    }

    if (c == UWORD(0))
    {
        _nmod_mpoly_set_length(A, 0, ctx);
        return;
    }

    nmod_mpoly_fit_length(A, 1, ctx);
    A->coeffs[0] = c;
    mpoly_monomial_zero(A->exps, N);
    _nmod_mpoly_set_length(A, 1, ctx);
}
