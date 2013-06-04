/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2011 Fredrik Johansson

******************************************************************************/

#include "arith.h"

void _arith_bernoulli_number_vec(fmpz * num, fmpz * den, len_t n)
{
    if (n < 700)
        _arith_bernoulli_number_vec_recursive(num, den, n);
    else if (n < 3900)
        _arith_bernoulli_number_vec_zeta(num, den, n);
    else
        _arith_bernoulli_number_vec_multi_mod(num, den, n);
}

void arith_bernoulli_number_vec(fmpq * x, len_t n)
{
    fmpz * num, * den;
    len_t i;

    if (n <= 0)
        return;

    num = _fmpz_vec_init(n * 2);
    den = num + n;

    _arith_bernoulli_number_vec(num, den, n);

    for (i = 0; i < n; i++)
    {
        fmpz_swap(num + i, fmpq_numref(x + i));
        fmpz_swap(den + i, fmpq_denref(x + i));
    }

    _fmpz_vec_clear(num, n * 2);
}

