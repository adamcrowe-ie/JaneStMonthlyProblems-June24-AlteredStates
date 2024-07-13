#ifndef GENERATE_H
#define GENERATE_H

#include <string>
#include <vector>

#include "grid.h"

Grid generate_grid();

std::string random_grid();

std::vector<GridScorePair> optimize(GridScorePair);

#endif