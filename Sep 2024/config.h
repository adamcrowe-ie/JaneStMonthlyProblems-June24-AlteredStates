#ifndef CONFIG_H
#define CONFIG_H


// 14 posts
// 124 fences
// 133 empty tiles

const int HEXAGON_LENGTH = 10;

constexpr int NUM_ROWS = 2 * HEXAGON_LENGTH - 1;
constexpr int NUM_COLS = 2 * HEXAGON_LENGTH - 1;

constexpr int LOWER_SUM = HEXAGON_LENGTH - 1;
constexpr int UPPER_SUM = 3 * (HEXAGON_LENGTH - 1);

constexpr int NUM_POSTS = 14;
constexpr int NUM_DIRECTIONS = 6;

const int POSTS[14][3] = {
    {1, 13, 7}, // Green
    {3, 15, 3}, // Green
    {5, 16, 6}, // Yellow
    {6, 3, 1}, // Blue
    {7, 9, 8}, // Blue
    {8, 11, 4}, // Yellow
    {9, 4, 6}, // Purple
    {9, 14, 3}, // Yellow
    {10, 7, 38}, // Purple
    {11, 9, 6}, // Orange
    {12, 15, 11}, // Orange
    {13, 2, 6}, // Purple
    {15, 3, 19}, // Red
    {17, 5, 6} // Red
};

const int FENCES[14][6] = {
    {0, 0, 0, 4, 3, 0}, // Green 7
    {0, 0, 0, 0, 3, 0}, // Green 3
    {0, 0, 1, 1, 1, 3}, // Yellow 6
    {0, 0, 0, 0, 1, 0}, // Blue 1
    {0, 5, 1, 1, 1, 0}, // Blue 8
    {0, 0, 1, 1, 1, 1}, // Yellow 4
    {2, 2, 1, 1, 0, 0}, // Purple 6 (I)
    {0, 0, 1, 2, 0, 0}, // Yellow 3
    {6, 8, 6, 7, 3, 8}, // Purple 38, interior
    {3, 0, 0, 1, 1, 1}, // Orange 6
    {0, 3, 1, 1, 6, 0}, // Orange 11
    {0, 0, 2, 2, 1, 1}, // Purple 6 (II)
    {3, 3, 4, 3, 3, 3}, // Red 19, interior
    {1, 1, 1, 1, 1, 1} // Red 6
};

const int DIRECTIONS[6][2] = {
    {0, 1},
    {-1, 1},
    {-1, 0},
    {0, -1},
    {1, -1},
    {1, 0}
};


#endif

// 11 has to be {0, 3, 0, 2, 6, 0} which means 38 has to be {8, ...}

// {0, 0, 0, 0, 0, 0}, // Green 7
// {0, 0, 0, 0, 0, 0}, // Green 3
// {0, 0, 0, 0, 0, 0}, // Yellow 6
// {0, 0, 0, 0, 0, 0}, // Blue 1
// {0, 0, 0, 0, 0, 0}, // Blue 8
// {0, 0, 0, 0, 0, 0}, // Yellow 4
// {0, 0, 0, 0, 0, 0}, // Purple 6 (I)
// {0, 0, 0, 0, 0, 0}, // Yellow 3
// {8, 9, 7, 6, 3, 4}, // Purple 38, interior
// {0, 0, 0, 0, 0, 0}, // Orange 6
// {0, 3, 0, 2, 6, 0}, // Orange 11
// {0, 0, 0, 0, 0, 0}, // Purple 6 (II)
// {6, 3, 4, 2, 2, 2}, // Red 19, interior
// {0, 0, 0, 0, 0, 0} // Red 6

// 38 is not interior