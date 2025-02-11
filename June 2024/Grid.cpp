#include <string>
#include <queue>
#include <vector>

#include "grid.h"
#include "consts.h"
#include "path.h"
#include "coord.h"


int Grid::evaluate(){
    int score = 0;

    for(const std::string st : EXCLUDED_STATES)
        if(contains_state(st)) return -1;

    for(const std::string st : REQUIRED_STATES){
        if(!contains_state(st)) return -1;

        score += POPULATIONS.at(st);
    }

    for(const std::string st : OTHER_STATES)
        score += contains_state(st) ? POPULATIONS.at(st) : 0;
    
    return score;
}

bool Grid::contains_state(std::string state){
    std::priority_queue<Path, std::vector<Path>, PathCompByLength> paths;

    for(int i = 0; i < 25; i++) paths.push({{i}, (state[0] != squares[i])});

    while(!paths.empty()){
        Path path = paths.top();
        paths.pop();

        char next_ch = state[path.positions.size()];
        std::vector<int> neighbours = find_neighbours(path.positions.back());

        for(const int& nb : neighbours){
            if(next_ch != squares[nb] && path.used_blank) continue;

            if(path.positions.size() + 1 == state.size()) return true;

            std::vector<int> new_positions = path.positions;
            new_positions.push_back(nb);
            paths.push({new_positions, (path.used_blank || next_ch != squares[nb])});
        }
    } 

    return false;
}