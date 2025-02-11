#ifndef GRID_H
#define GRID_H

#include "square.h"

#include <vector>

class Grid{
    private:
        std::vector<std::vector<Square>> grid;

        void find_adjacents();

    public:
        Grid();

        inline Square& at(int row, int col){ return grid[row][col]; }
};

#endif