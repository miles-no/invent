#ifndef SELFEVO_H
#define SELFEVO_H

#include <numeric>

#include "../YmirNoGl/ymir.h"
void testIncreasingMutations();

set<int> listEmbarrasingPoints(superProtein* ligand, set<int> alreadyBlocked = set<int>(), bool silent = true);
void testEmbarrassing();

#endif // SELFEVO_H
