#include <vector>
#include <utility>

#include "coord.h"
#include "consts.h"


std::vector<int> find_neighbours(int position){
    std::vector<int> neighbours;
    int row = position / 5, col = position % 5;

    for(const std::pair<int, int> dir : DIRECTIONS){
        int new_row = row + dir.first, new_col = col + dir.second;

        if(new_row >= 0 && new_row < 5 && new_col >= 0 && new_col < 5)
            neighbours.push_back((new_row * 5) + new_col);
    }

    return neighbours;
}