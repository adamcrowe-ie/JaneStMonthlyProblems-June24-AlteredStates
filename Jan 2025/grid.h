#ifndef GRID_H
#define GRID_H

#include "config.h"
#include "square.h"
#include "permutation.h"

#include <array>
#include <unordered_set>


class Grid{
    std::array<std::array<Square, 9>, 9> squares;
    std::array<std::unordered_set<int>, 9> matching_permutations;

    public:
        Grid();
        Grid(const Grid& grid);

        Square at(int row, int col) const { return squares[row][col]; }

        bool set_value(int row, int col, int new_value);

        void match_permutation(Permutation& permutation);
        bool matches_row(Permutation& permutation, int row);

        std::array<std::unordered_set<int>, 9> find_multiples(int gcd, bool exhaustive_search);

        bool primitive_gcd_test(int gcd);
        bool gcd_test(int gcd);

        void print();
};

#endif