/*
    Copyright (C) 2010 William Hart
    Copyright (C) 2014 Abhinav Baid

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "mpf_vec.h"
#include "gmpcompat.h"

void
_mpf_vec_zero(mpf * vec, slong len)
{
    slong i;
    for (i = 0; i < len; i++)
        flint_mpf_set_ui(vec + i, 0);
}
