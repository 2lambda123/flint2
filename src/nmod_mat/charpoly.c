/*
    Copyright (C) 2021 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "ulong_extras.h"
#include "nmod_poly.h"
#include "nmod_mat.h"

void nmod_mat_charpoly(nmod_poly_t cp, const nmod_mat_t mat)
{
    if (mat->r <= 8 || !n_is_prime(mat->mod.n))
        nmod_mat_charpoly_berkowitz(cp, mat);
    else
        nmod_mat_charpoly_danilevsky(cp, mat);
}
