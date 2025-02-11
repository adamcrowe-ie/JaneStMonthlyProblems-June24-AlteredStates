#include "grid.h"

Grid::Grid(){
    grid.resize(LENGTH);

    for(int i = 0; i < NUM_SQUARES; ++i)
        grid[i / LENGTH].push_back({i / LENGTH, i % LENGTH});
    
    find_adjacents();
}


void Grid::find_adjacents(){
    for(int i = 0; i < NUM_SQUARES; ++i){
        for(auto direction : DIRECTIONS){
            int row = (i / LENGTH) + direction[0], 
                col = (i % LENGTH) + direction[1];

            if(row < 0 || row >= LENGTH || col < 0 || col >= LENGTH)
                continue;

            grid[i / LENGTH][i % LENGTH].add_adjacent(&grid[row][col]);
        }
    }
}