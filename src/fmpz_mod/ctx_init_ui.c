/*
    Copyright (C) 2019 Daniel Schultz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "fmpz.h"
#include "fmpz_mod.h"

void fmpz_mod_ctx_init_ui(fmpz_mod_ctx_t ctx, ulong n)
{
    fmpz_t n_;
    fmpz_init_set_ui(n_, n);
    fmpz_mod_ctx_init(ctx, n_);
    fmpz_clear(n_);
}
