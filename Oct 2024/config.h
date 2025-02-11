#ifndef CONFIG_H
#define CONFIG_H

constexpr int LENGTH = 6;
constexpr int NUM_SQUARES = LENGTH * LENGTH;

const int SQUARE_TYPES[LENGTH][LENGTH] = {
    {0, 1, 1, 2, 2, 2},
    {0, 1, 1, 2, 2, 2},
    {0, 0, 1, 1, 2, 2},
    {0, 0, 1, 1, 2, 2},
    {0, 0, 0, 1, 1, 2},
    {0, 0, 0, 1, 1, 2}
};

const int DIRECTIONS[8][2] = {
    {1, 2},
    {-1, 2},
    {-2, 1},
    {-2, -1},
    {-1, -2},
    {1, -2},
    {2, -1},
    {2, 1}
};

constexpr int GOAL = 2024;
constexpr int SUM_LIMIT = 50;

#endif