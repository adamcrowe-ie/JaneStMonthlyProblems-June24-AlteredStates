#ifndef CONFIG_H
#define CONFIG_H


const int BIGGEST_POSS_ROW = 987'654'321;
const int SMALLEST_POSS_ROW = 12'345'678;

constexpr int BIGGEST_POSS_GCD = BIGGEST_POSS_ROW / 9;

const int NUM_STARTING_ENTRIES = 8;

const int STARTING_ENTRIES[NUM_STARTING_ENTRIES][3] = {
    {0, 7, 2},
    {1, 8, 5},
    {2, 1, 2},
    {3, 2, 0},
    {5, 3, 2},
    {6, 4, 0},
    {7, 5, 2},
    {8, 6, 5}
};

const int STARTING_PERMUTATION[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

const int MATCHING_PERMUTATIONS_RESERVE_AMOUNT = 100'000;

constexpr int LOG_INTERVAL = 3 * 1'000;

#endif