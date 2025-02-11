#include <string>
#include <iostream>
#include <random>
#include <algorithm>

#include "grid.h"
#include "generate.h"
#include "consts.h"


int main(){
    int count = 0;

    while(true){
        count += 1;
        Grid starting_grid = generate_grid();
        std::vector<GridScorePair> grids = {{starting_grid.get_squares(), starting_grid.evaluate()}};

        while(true){
            std::vector<GridScorePair> new_grids;

            for(const GridScorePair& g : grids){
                std::vector<GridScorePair> optimized = optimize(g);
                new_grids.insert(new_grids.end(), optimized.begin(), optimized.end());
            }

            if(new_grids.empty()){
                std::cout << count << "-" << grids[0].grid << "-" << grids[0].score << std::endl;
                break;
            }

            std::ranges::sort(new_grids, [](const GridScorePair& l, const GridScorePair& r){
                return l.score > r.score;
            });

            if(new_grids.size() > NUM_TO_OPTIMIZE){
                new_grids.erase(new_grids.begin() + NUM_TO_OPTIMIZE, new_grids.end());
            }

            grids = new_grids;
            for(auto& g : grids){
                if(g.score >= GOAL_SCORE) std::cout << "\nSolution Found\n" << g.grid << "-" << g.score << std::endl;
            }
            
        }
    }

    return 0;
}