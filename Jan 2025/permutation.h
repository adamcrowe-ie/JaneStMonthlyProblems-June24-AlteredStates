#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <array>
#include <algorithm>


using Permutation = std::array<int, 10>;


inline bool next_permutation(Permutation& permutation){
    return std::next_permutation(permutation.begin(), permutation.end());
}

int permutation_to_int(Permutation& permutation);

bool is_permutation(int x);

#endif