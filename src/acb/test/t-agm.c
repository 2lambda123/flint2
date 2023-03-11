/*
    Copyright (C) 2020 Fredrik Johansson

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "acb.h"

#define NUM_TESTS 256
const double agm_testdata[NUM_TESTS][6] = {
    {-1, -1, -1, -1, -1.00000000000000, -1.00000000000000},
    {-1, -1, -1, 0, -1.04916052873278, -0.478155746088161},
    {-1, -1, -1, 1, -1.19814023473559, 0.000000000000000},
    {-1, -1, -1, 2, -1.35980258211696, 0.412918513270561},
    {-1, -1, 0, -1, -0.478155746088161, -1.04916052873278},
    {-1, -1, 0, 0, 0.000000000000000, 0.000000000000000},
    {-1, -1, 0, 1, -0.778004078788958, 0.188411067988680},
    {-1, -1, 0, 2, -0.966415146777638, 0.589593010800278},
    {-1, -1, 1, -1, 0.000000000000000, -1.19814023473559},
    {-1, -1, 1, 0, 0.188411067988680, -0.778004078788958},
    {-1, -1, 1, 1, 0.000000000000000, 0.000000000000000},
    {-1, -1, 1, 2, -0.574659643809835, 0.810208383866421},
    {-1, -1, 2, -1, 0.412918513270561, -1.35980258211696},
    {-1, -1, 2, 0, 0.589593010800278, -0.966415146777638},
    {-1, -1, 2, 1, 0.810208383866421, -0.574659643809835},
    {-1, -1, 2, 2, 1.08423239187061, -0.238299975053003},
    {-1, 0, -1, -1, -1.04916052873278, -0.478155746088161},
    {-1, 0, -1, 0, -1.00000000000000, 0.000000000000000},
    {-1, 0, -1, 1, -1.04916052873278, 0.478155746088161},
    {-1, 0, -1, 2, -1.13815978557677, 0.897764105638205},
    {-1, 0, 0, -1, -0.599070117367796, -0.599070117367796},
    {-1, 0, 0, 0, 0.000000000000000, 0.000000000000000},
    {-1, 0, 0, 1, -0.599070117367796, 0.599070117367796},
    {-1, 0, 0, 2, -0.742646422399778, 1.01005159361958},
    {-1, 0, 1, -1, -0.188411067988680, -0.778004078788958},
    {-1, 0, 1, 0, 0.000000000000000, 0.000000000000000},
    {-1, 0, 1, 1, -0.188411067988680, 0.778004078788958},
    {-1, 0, 1, 2, -0.363823969691055, 1.15631976909117},
    {-1, 0, 2, -1, 0.178866979357132, -0.985872907297986},
    {-1, 0, 2, 0, 0.422966208408802, 0.661266183461805},
    {-1, 0, 2, 1, 0.178866979357132, 0.985872907297986},
    {-1, 0, 2, 2, -0.0126420344317752, 1.32391495927282},
    {-1, 1, -1, -1, -1.19814023473559, 0.000000000000000},
    {-1, 1, -1, 0, -1.04916052873278, 0.478155746088161},
    {-1, 1, -1, 1, -1.00000000000000, 1.00000000000000},
    {-1, 1, -1, 2, -1.02005412633766, 1.47134936286465},
    {-1, 1, 0, -1, -0.778004078788958, -0.188411067988680},
    {-1, 1, 0, 0, 0.000000000000000, 0.000000000000000},
    {-1, 1, 0, 1, -0.478155746088161, 1.04916052873278},
    {-1, 1, 0, 2, -0.571004782644619, 1.52731627482094},
    {-1, 1, 1, -1, 0.000000000000000, 0.000000000000000},
    {-1, 1, 1, 0, 0.188411067988680, 0.778004078788958},
    {-1, 1, 1, 1, 0.000000000000000, 1.19814023473559},
    {-1, 1, 1, 2, -0.136827548397369, 1.62780548487271},
    {-1, 1, 2, -1, 0.810208383866421, 0.574659643809835},
    {-1, 1, 2, 0, 0.589593010800278, 0.966415146777638},
    {-1, 1, 2, 1, 0.412918513270561, 1.35980258211696},
    {-1, 1, 2, 2, 0.267405171219803, 1.75269801601936},
    {-1, 2, -1, -1, -1.35980258211696, 0.412918513270561},
    {-1, 2, -1, 0, -1.13815978557677, 0.897764105638205},
    {-1, 2, -1, 1, -1.02005412633766, 1.47134936286465},
    {-1, 2, -1, 2, -1.00000000000000, 2.00000000000000},
    {-1, 2, 0, -1, -0.985872907297986, 0.178866979357132},
    {-1, 2, 0, 0, 0.000000000000000, 0.000000000000000},
    {-1, 2, 0, 1, -0.420983902077155, 1.47839688785392},
    {-1, 2, 0, 2, -0.493004461502931, 2.02900451838781},
    {-1, 2, 1, -1, 0.574659643809835, 0.810208383866421},
    {-1, 2, 1, 0, 0.363823969691055, 1.15631976909117},
    {-1, 2, 1, 1, 0.136827548397369, 1.62780548487271},
    {-1, 2, 1, 2, 0.000000000000000, 2.11638793788003},
    {-1, 2, 2, -1, 0.963366302386887, 0.963366302386887},
    {-1, 2, 2, 0, 0.777111977967075, 1.37110999239961},
    {-1, 2, 2, 1, 0.599070117367796, 1.79721035210339},
    {-1, 2, 2, 2, 0.455159607692816, 2.23571522629432},
    {0, -1, -1, -1, -0.478155746088161, -1.04916052873278},
    {0, -1, -1, 0, -0.599070117367796, -0.599070117367796},
    {0, -1, -1, 1, -0.778004078788958, -0.188411067988680},
    {0, -1, -1, 2, -0.985872907297986, 0.178866979357132},
    {0, -1, 0, -1, 0.000000000000000, -1.00000000000000},
    {0, -1, 0, 0, 0.000000000000000, 0.000000000000000},
    {0, -1, 0, 1, 0.000000000000000, 0.000000000000000},
    {0, -1, 0, 2, 0.661266183461805, 0.422966208408802},
    {0, -1, 1, -1, 0.478155746088161, -1.04916052873278},
    {0, -1, 1, 0, 0.599070117367796, -0.599070117367796},
    {0, -1, 1, 1, 0.778004078788958, -0.188411067988680},
    {0, -1, 1, 2, 0.985872907297986, 0.178866979357132},
    {0, -1, 2, -1, 0.897764105638205, -1.13815978557677},
    {0, -1, 2, 0, 1.01005159361958, -0.742646422399778},
    {0, -1, 2, 1, 1.15631976909117, -0.363823969691055},
    {0, -1, 2, 2, 1.32391495927282, -0.0126420344317752},
    {0, 0, -1, -1, 0.000000000000000, 0.000000000000000},
    {0, 0, -1, 0, 0.000000000000000, 0.000000000000000},
    {0, 0, -1, 1, 0.000000000000000, 0.000000000000000},
    {0, 0, -1, 2, 0.000000000000000, 0.000000000000000},
    {0, 0, 0, -1, 0.000000000000000, 0.000000000000000},
    {0, 0, 0, 0, 0.000000000000000, 0.000000000000000},
    {0, 0, 0, 1, 0.000000000000000, 0.000000000000000},
    {0, 0, 0, 2, 0.000000000000000, 0.000000000000000},
    {0, 0, 1, -1, 0.000000000000000, 0.000000000000000},
    {0, 0, 1, 0, 0.000000000000000, 0.000000000000000},
    {0, 0, 1, 1, 0.000000000000000, 0.000000000000000},
    {0, 0, 1, 2, 0.000000000000000, 0.000000000000000},
    {0, 0, 2, -1, 0.000000000000000, 0.000000000000000},
    {0, 0, 2, 0, 0.000000000000000, 0.000000000000000},
    {0, 0, 2, 1, 0.000000000000000, 0.000000000000000},
    {0, 0, 2, 2, 0.000000000000000, 0.000000000000000},
    {0, 1, -1, -1, -0.778004078788958, 0.188411067988680},
    {0, 1, -1, 0, -0.599070117367796, 0.599070117367796},
    {0, 1, -1, 1, -0.478155746088161, 1.04916052873278},
    {0, 1, -1, 2, -0.420983902077155, 1.47839688785392},
    {0, 1, 0, -1, 0.000000000000000, 0.000000000000000},
    {0, 1, 0, 0, 0.000000000000000, 0.000000000000000},
    {0, 1, 0, 1, 0.000000000000000, 1.00000000000000},
    {0, 1, 0, 2, 0.000000000000000, 1.45679103104691},
    {0, 1, 1, -1, 0.778004078788958, 0.188411067988680},
    {0, 1, 1, 0, 0.599070117367796, 0.599070117367796},
    {0, 1, 1, 1, 0.478155746088161, 1.04916052873278},
    {0, 1, 1, 2, 0.420983902077155, 1.47839688785392},
    {0, 1, 2, -1, 1.15631976909117, 0.363823969691055},
    {0, 1, 2, 0, 1.01005159361958, 0.742646422399778},
    {0, 1, 2, 1, 0.897764105638205, 1.13815978557677},
    {0, 1, 2, 2, 0.820905313474926, 1.53147158277780},
    {0, 2, -1, -1, -0.966415146777638, 0.589593010800278},
    {0, 2, -1, 0, -0.742646422399778, 1.01005159361958},
    {0, 2, -1, 1, -0.571004782644619, 1.52731627482094},
    {0, 2, -1, 2, -0.493004461502931, 2.02900451838781},
    {0, 2, 0, -1, 0.661266183461805, 0.422966208408802},
    {0, 2, 0, 0, 0.000000000000000, 0.000000000000000},
    {0, 2, 0, 1, 0.000000000000000, 1.45679103104691},
    {0, 2, 0, 2, 0.000000000000000, 2.00000000000000},
    {0, 2, 1, -1, 0.966415146777638, 0.589593010800278},
    {0, 2, 1, 0, 0.742646422399778, 1.01005159361958},
    {0, 2, 1, 1, 0.571004782644619, 1.52731627482094},
    {0, 2, 1, 2, 0.493004461502931, 2.02900451838781},
    {0, 2, 2, -1, 1.37110999239961, 0.777111977967075},
    {0, 2, 2, 0, 1.19814023473559, 1.19814023473559},
    {0, 2, 2, 1, 1.05542091981433, 1.64623191253177},
    {0, 2, 2, 2, 0.956311492176322, 2.09832105746556},
    {1, -1, -1, -1, 0.000000000000000, -1.19814023473559},
    {1, -1, -1, 0, -0.188411067988680, -0.778004078788958},
    {1, -1, -1, 1, 0.000000000000000, 0.000000000000000},
    {1, -1, -1, 2, 0.574659643809835, 0.810208383866421},
    {1, -1, 0, -1, 0.478155746088161, -1.04916052873278},
    {1, -1, 0, 0, 0.000000000000000, 0.000000000000000},
    {1, -1, 0, 1, 0.778004078788958, 0.188411067988680},
    {1, -1, 0, 2, 0.966415146777638, 0.589593010800278},
    {1, -1, 1, -1, 1.00000000000000, -1.00000000000000},
    {1, -1, 1, 0, 1.04916052873278, -0.478155746088161},
    {1, -1, 1, 1, 1.19814023473559, 0.000000000000000},
    {1, -1, 1, 2, 1.35980258211696, 0.412918513270561},
    {1, -1, 2, -1, 1.47134936286465, -1.02005412633766},
    {1, -1, 2, 0, 1.52731627482094, -0.571004782644619},
    {1, -1, 2, 1, 1.62780548487271, -0.136827548397369},
    {1, -1, 2, 2, 1.75269801601936, 0.267405171219803},
    {1, 0, -1, -1, 0.188411067988680, -0.778004078788958},
    {1, 0, -1, 0, 0.000000000000000, 0.000000000000000},
    {1, 0, -1, 1, 0.188411067988680, 0.778004078788958},
    {1, 0, -1, 2, 0.363823969691055, 1.15631976909117},
    {1, 0, 0, -1, 0.599070117367796, -0.599070117367796},
    {1, 0, 0, 0, 0.000000000000000, 0.000000000000000},
    {1, 0, 0, 1, 0.599070117367796, 0.599070117367796},
    {1, 0, 0, 2, 0.742646422399778, 1.01005159361958},
    {1, 0, 1, -1, 1.04916052873278, -0.478155746088161},
    {1, 0, 1, 0, 1.00000000000000, 0.000000000000000},
    {1, 0, 1, 1, 1.04916052873278, 0.478155746088161},
    {1, 0, 1, 2, 1.13815978557677, 0.897764105638205},
    {1, 0, 2, -1, 1.47839688785392, -0.420983902077155},
    {1, 0, 2, 0, 1.45679103104691, 0.000000000000000},
    {1, 0, 2, 1, 1.47839688785392, 0.420983902077155},
    {1, 0, 2, 2, 1.53147158277780, 0.820905313474926},
    {1, 1, -1, -1, 0.000000000000000, 0.000000000000000},
    {1, 1, -1, 0, -0.188411067988680, 0.778004078788958},
    {1, 1, -1, 1, 0.000000000000000, 1.19814023473559},
    {1, 1, -1, 2, 0.136827548397369, 1.62780548487271},
    {1, 1, 0, -1, 0.778004078788958, -0.188411067988680},
    {1, 1, 0, 0, 0.000000000000000, 0.000000000000000},
    {1, 1, 0, 1, 0.478155746088161, 1.04916052873278},
    {1, 1, 0, 2, 0.571004782644619, 1.52731627482094},
    {1, 1, 1, -1, 1.19814023473559, 0.000000000000000},
    {1, 1, 1, 0, 1.04916052873278, 0.478155746088161},
    {1, 1, 1, 1, 1.00000000000000, 1.00000000000000},
    {1, 1, 1, 2, 1.02005412633766, 1.47134936286465},
    {1, 1, 2, -1, 1.62780548487271, 0.136827548397369},
    {1, 1, 2, 0, 1.52731627482094, 0.571004782644619},
    {1, 1, 2, 1, 1.47134936286465, 1.02005412633766},
    {1, 1, 2, 2, 1.45679103104691, 1.45679103104691},
    {1, 2, -1, -1, -0.574659643809835, 0.810208383866421},
    {1, 2, -1, 0, -0.363823969691055, 1.15631976909117},
    {1, 2, -1, 1, -0.136827548397369, 1.62780548487271},
    {1, 2, -1, 2, 0.000000000000000, 2.11638793788003},
    {1, 2, 0, -1, 0.985872907297986, 0.178866979357132},
    {1, 2, 0, 0, 0.000000000000000, 0.000000000000000},
    {1, 2, 0, 1, 0.420983902077155, 1.47839688785392},
    {1, 2, 0, 2, 0.493004461502931, 2.02900451838781},
    {1, 2, 1, -1, 1.35980258211696, 0.412918513270561},
    {1, 2, 1, 0, 1.13815978557677, 0.897764105638205},
    {1, 2, 1, 1, 1.02005412633766, 1.47134936286465},
    {1, 2, 1, 2, 1.00000000000000, 2.00000000000000},
    {1, 2, 2, -1, 1.79721035210339, 0.599070117367796},
    {1, 2, 2, 0, 1.64623191253177, 1.05542091981433},
    {1, 2, 2, 1, 1.54030226799894, 1.54030226799894},
    {1, 2, 2, 2, 1.48529284479956, 2.02010318723916},
    {2, -1, -1, -1, 0.412918513270561, -1.35980258211696},
    {2, -1, -1, 0, 0.178866979357132, -0.985872907297986},
    {2, -1, -1, 1, 0.810208383866421, 0.574659643809835},
    {2, -1, -1, 2, 0.963366302386887, 0.963366302386887},
    {2, -1, 0, -1, 0.897764105638205, -1.13815978557677},
    {2, -1, 0, 0, 0.000000000000000, 0.000000000000000},
    {2, -1, 0, 1, 1.15631976909117, 0.363823969691055},
    {2, -1, 0, 2, 1.37110999239961, 0.777111977967075},
    {2, -1, 1, -1, 1.47134936286465, -1.02005412633766},
    {2, -1, 1, 0, 1.47839688785392, -0.420983902077155},
    {2, -1, 1, 1, 1.62780548487271, 0.136827548397369},
    {2, -1, 1, 2, 1.79721035210339, 0.599070117367796},
    {2, -1, 2, -1, 2.00000000000000, -1.00000000000000},
    {2, -1, 2, 0, 2.02900451838781, -0.493004461502931},
    {2, -1, 2, 1, 2.11638793788003, 0.000000000000000},
    {2, -1, 2, 2, 2.23571522629432, 0.455159607692816},
    {2, 0, -1, -1, 0.589593010800278, -0.966415146777638},
    {2, 0, -1, 0, 0.422966208408802, 0.661266183461805},
    {2, 0, -1, 1, 0.589593010800278, 0.966415146777638},
    {2, 0, -1, 2, 0.777111977967075, 1.37110999239961},
    {2, 0, 0, -1, 1.01005159361958, -0.742646422399778},
    {2, 0, 0, 0, 0.000000000000000, 0.000000000000000},
    {2, 0, 0, 1, 1.01005159361958, 0.742646422399778},
    {2, 0, 0, 2, 1.19814023473559, 1.19814023473559},
    {2, 0, 1, -1, 1.52731627482094, -0.571004782644619},
    {2, 0, 1, 0, 1.45679103104691, 0.000000000000000},
    {2, 0, 1, 1, 1.52731627482094, 0.571004782644619},
    {2, 0, 1, 2, 1.64623191253177, 1.05542091981433},
    {2, 0, 2, -1, 2.02900451838781, -0.493004461502931},
    {2, 0, 2, 0, 2.00000000000000, 0.000000000000000},
    {2, 0, 2, 1, 2.02900451838781, 0.493004461502931},
    {2, 0, 2, 2, 2.09832105746556, 0.956311492176322},
    {2, 1, -1, -1, 0.810208383866421, -0.574659643809835},
    {2, 1, -1, 0, 0.178866979357132, 0.985872907297986},
    {2, 1, -1, 1, 0.412918513270561, 1.35980258211696},
    {2, 1, -1, 2, 0.599070117367796, 1.79721035210339},
    {2, 1, 0, -1, 1.15631976909117, -0.363823969691055},
    {2, 1, 0, 0, 0.000000000000000, 0.000000000000000},
    {2, 1, 0, 1, 0.897764105638205, 1.13815978557677},
    {2, 1, 0, 2, 1.05542091981433, 1.64623191253177},
    {2, 1, 1, -1, 1.62780548487271, -0.136827548397369},
    {2, 1, 1, 0, 1.47839688785392, 0.420983902077155},
    {2, 1, 1, 1, 1.47134936286465, 1.02005412633766},
    {2, 1, 1, 2, 1.54030226799894, 1.54030226799894},
    {2, 1, 2, -1, 2.11638793788003, 0.000000000000000},
    {2, 1, 2, 0, 2.02900451838781, 0.493004461502931},
    {2, 1, 2, 1, 2.00000000000000, 1.00000000000000},
    {2, 1, 2, 2, 2.02010318723916, 1.48529284479956},
    {2, 2, -1, -1, 1.08423239187061, -0.238299975053003},
    {2, 2, -1, 0, -0.0126420344317752, 1.32391495927282},
    {2, 2, -1, 1, 0.267405171219803, 1.75269801601936},
    {2, 2, -1, 2, 0.455159607692816, 2.23571522629432},
    {2, 2, 0, -1, 1.32391495927282, -0.0126420344317752},
    {2, 2, 0, 0, 0.000000000000000, 0.000000000000000},
    {2, 2, 0, 1, 0.820905313474926, 1.53147158277780},
    {2, 2, 0, 2, 0.956311492176322, 2.09832105746556},
    {2, 2, 1, -1, 1.75269801601936, 0.267405171219803},
    {2, 2, 1, 0, 1.53147158277780, 0.820905313474926},
    {2, 2, 1, 1, 1.45679103104691, 1.45679103104691},
    {2, 2, 1, 2, 1.48529284479956, 2.02010318723916},
    {2, 2, 2, -1, 2.23571522629432, 0.455159607692816},
    {2, 2, 2, 0, 2.09832105746556, 0.956311492176322},
    {2, 2, 2, 1, 2.02010318723916, 1.48529284479956},
    {2, 2, 2, 2, 2.00000000000000, 2.00000000000000},
};

int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("agm....");
    fflush(stdout);

    flint_randinit(state);


    /* test particular values against table */
    {
        acb_t x, y, r, s;

        acb_init(x);
        acb_init(y);
        acb_init(r);
        acb_init(s);

        for (iter = 0; iter < NUM_TESTS; iter++)
        {
            acb_set_d_d(x, agm_testdata[iter][0], agm_testdata[iter][1]);
            acb_set_d_d(y, agm_testdata[iter][2], agm_testdata[iter][3]);
            acb_set_d_d(s, agm_testdata[iter][4], agm_testdata[iter][5]);
            mag_set_d(arb_radref(acb_realref(s)), 1e-13);
            mag_set_d(arb_radref(acb_imagref(s)), 1e-13);

            acb_agm(r, x, y, 64);

            if (!acb_overlaps(r, s))
            {
                flint_printf("FAIL\n\n");
                flint_printf("x = "); acb_printd(x, 15); flint_printf("\n\n");
                flint_printf("y = "); acb_printd(y, 15); flint_printf("\n\n");
                flint_printf("r = "); acb_printd(r, 15); flint_printf("\n\n");
                flint_printf("s = "); acb_printd(s, 15); flint_printf("\n\n");
                flint_abort();
            }
    }

        acb_clear(x);
        acb_clear(y);
        acb_clear(r);
        acb_clear(s);
    }

    /* self-consistency test */
    for (iter = 0; iter < 1000 * 0.1 * flint_test_multiplier(); iter++)
    {
        acb_t m1, m2;
        acb_t x1, x2, y1, y2, t;
        slong prec1, prec2;

        prec1 = 2 + n_randint(state, 200);
        prec2 = 2 + n_randint(state, 200);

        acb_init(x1);
        acb_init(x2);
        acb_init(y1);
        acb_init(y2);
        acb_init(m1);
        acb_init(m2);
        acb_init(t);

        acb_randtest(x1, state, prec1, 1 + n_randint(state, 100));
        acb_randtest(y1, state, prec1, 1 + n_randint(state, 100));
        acb_randtest(m1, state, prec1, 1 + n_randint(state, 100));
        acb_randtest(m2, state, prec1, 1 + n_randint(state, 100));

        if (n_randint(state, 2))
        {
            acb_randtest(t, state, prec2, 1 + n_randint(state, 200));
            acb_mul(y1, x1, t, prec1);
        }

        if (n_randint(state, 2))
            acb_swap(x1, y1);

        if (n_randint(state, 2))
        {
            acb_set(x2, x1);
        }
        else
        {
            acb_randtest(t, state, prec2, 1 + n_randint(state, 200));
            acb_add(x2, x1, t, prec2);
            acb_sub(x2, x2, t, prec2);
        }

        if (n_randint(state, 2))
        {
            acb_set(y2, y1);
        }
        else
        {
            acb_randtest(t, state, prec2, 1 + n_randint(state, 200));
            acb_add(y2, y1, t, prec2);
            acb_sub(y2, y2, t, prec2);
        }

        acb_agm(m1, x1, y1, prec1);
        acb_agm(m2, x2, y2, prec2);

        if (!acb_overlaps(m1, m2))
        {
            flint_printf("FAIL (overlap)\n\n");
            flint_printf("iter = %wd, prec1 = %wd, prec2 = %wd\n\n", iter, prec1, prec2);

            flint_printf("x1 = "); acb_printd(x1, 30); flint_printf("\n\n");
            flint_printf("y1 = "); acb_printd(y1, 30); flint_printf("\n\n");
            flint_printf("x2 = "); acb_printd(x2, 30); flint_printf("\n\n");
            flint_printf("y2 = "); acb_printd(y2, 30); flint_printf("\n\n");
            flint_printf("m1 = "); acb_printd(m1, 30); flint_printf("\n\n");
            flint_printf("m2 = "); acb_printd(m2, 30); flint_printf("\n\n");
            flint_abort();
        }

        acb_div(t, x1, y1, prec1);
        if (acb_is_finite(t) && (!acb_is_real(t) || !arb_is_negative(acb_realref(t))))
        {
            if (n_randint(state, 2))
            {
                acb_div(t, x1, y1, prec1);
                acb_agm1(t, t, prec1);
                acb_mul(t, t, y1, prec1);
            }   
            else
            {
                acb_div(t, y1, x1, prec1);
                acb_agm1(t, t, prec1);
                acb_mul(t, t, x1, prec1);
            }

            if (!acb_overlaps(t, m1))
            {
                flint_printf("FAIL (overlap 2)\n\n");
                flint_printf("iter = %wd, prec1 = %wd, prec2 = %wd\n\n", iter, prec1, prec2);

                flint_printf("x1 = "); acb_printd(x1, 30); flint_printf("\n\n");
                flint_printf("y1 = "); acb_printd(y1, 30); flint_printf("\n\n");
                flint_printf("m1 = "); acb_printd(m1, 30); flint_printf("\n\n");
                flint_printf("t = "); acb_printd(t, 30); flint_printf("\n\n");
                flint_abort();
            }
        }

        acb_clear(x1);
        acb_clear(x2);
        acb_clear(y1);
        acb_clear(y2);
        acb_clear(m1);
        acb_clear(m2);
        acb_clear(t);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return 0;
}

