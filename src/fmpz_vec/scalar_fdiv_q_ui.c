/*
    Copyright (C) 2010 William Hart
    Copyright (C) 2010 Sebastian Pancratz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "flint.h"
#include "fmpz.h"
#include "fmpz_vec.h"

void
_fmpz_vec_scalar_fdiv_q_ui(fmpz * vec1, const fmpz * vec2, slong len2, ulong c)
{
    slong i;
    for (i = 0; i < len2; i++)
        fmpz_fdiv_q_ui(vec1 + i, vec2 + i, c);
}
