/*
    Copyright (C) 2010 Sebastian Pancratz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "fmpz.h"
#include "fmpq_poly.h"

void fmpq_poly_set_ui(fmpq_poly_t poly, ulong x)
{
    fmpq_poly_fit_length(poly, 1);
    fmpz_set_ui(poly->coeffs, x);
    fmpz_one(poly->den);
    _fmpq_poly_set_length(poly, 1);
    _fmpq_poly_normalise(poly);
}

