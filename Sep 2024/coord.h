#ifndef COORD_H
#define COORD_H

#include "config.h"

inline bool in_bounds(int row, int col){
    if(row < 0 || row >= NUM_ROWS) return false;
    if(col < 0 || col >= NUM_COLS) return false;
    if(row + col < LOWER_SUM || row + col > UPPER_SUM) return false;

    return true;
}

inline int distance_to_edge(int starting_row, int starting_col){
    int distance = HEXAGON_LENGTH;

    for(const auto& [y, x] : DIRECTIONS){
        int row = starting_row, col = starting_col, count = 0;

        while(in_bounds(row, col))
            row += y, col += x, ++count;

        if(count < distance)
            distance = count;
    }

    return distance;
}

#endif