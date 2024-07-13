#include <random>
#include <string>
#include <vector>
#include <algorithm>

#include "generate.h"
#include "grid.h"
#include "consts.h"
#include "path.h"
#include "coord.h"

Grid generate_grid(){
    std::random_device rand_dev;
    std::mt19937 mt(rand_dev());

    std::uniform_int_distribution<int> starting_pos_dist(0, 25);
    std::uniform_int_distribution<int> neighbours_dist(0, 8);

    while(true){
        // blank grid
        Grid grid(BLANK_GRID);

        // fit required states into grid
        bool contains_required = true;
        for(const std::string& state : REQUIRED_STATES){
            int starting_pos = starting_pos_dist(mt);

            Path path = {{starting_pos}, (grid[starting_pos] != ' ' && grid[starting_pos] != state[0])};
            if(!path.used_blank) grid[starting_pos] = state[0]; 

            while(path.positions.size() < state.size()){
                char next_ch = state[path.positions.size()];
                std::vector<int> neighbours = find_neighbours(path.positions.back());
                std::shuffle(neighbours.begin(), neighbours.end(), mt);

                bool found_next_pos = false;
                for(const int& nb : neighbours){
                    if(grid[nb] == ' ' || grid[nb] == next_ch) grid[nb] = next_ch;
                    else if(!path.used_blank) path.used_blank = true;
                    else continue;

                    path.positions.push_back(nb);
                    found_next_pos = true;
                    break;
                }

                if(!found_next_pos){
                    contains_required = false;
                    break;
                }
            }

            if(path.positions.size() < state.size()) break;
        }

        if(!contains_required) continue;

        // check if contains any of the excluded statess
        bool contains_excluded = false;
        for(const std::string& state : EXCLUDED_STATES){
            if(!grid.contains_state(state)) continue;

            contains_excluded = true;
            break;
        }

        if(!contains_excluded) return grid;
    }
}


std::vector<GridScorePair> optimize(GridScorePair grid){
    std::vector<GridScorePair> optimized;
    
    for(int i = 0; i < 25; i++){
        GridScorePair best_grid = grid;

        for(const char& ch : LETTERS){
            if(grid.grid[i] == ch) continue;

            std::string s = grid.grid;
            s[i] = ch;
            int score = Grid(s).evaluate();

            if(score > best_grid.score) best_grid = {s, score};
        }

        if(best_grid.grid != grid.grid) optimized.push_back(best_grid);
    }


    std::ranges::sort(optimized, [](const GridScorePair& l, const GridScorePair& r){
        return l.score > r.score;
    });

    if(optimized.size() > NUM_TO_OPTIMIZE){
        optimized.erase(optimized.begin() + NUM_TO_OPTIMIZE, optimized.end());
    }

    return optimized;
}