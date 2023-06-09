/*
    Copyright (C) 2020 Daniel Schultz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "fq_zech.h"
#include "fq_zech_mpoly.h"

void fq_zech_mpoly_ctx_change_modulus(fq_zech_mpoly_ctx_t ctx, slong deg)
{
    fmpz_t P;
    fmpz_init_set_ui(P, fq_zech_ctx_mod(ctx->fqctx).n);
    fq_zech_ctx_clear(ctx->fqctx);
    fq_zech_ctx_init(ctx->fqctx, P, deg, "#");
    fmpz_clear(P);
}
