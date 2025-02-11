#include "grid.h"
#include "config.h"

#include <stdexcept>
#include <algorithm>
#include <queue>
#include <utility>
#include <iostream>


Grid::Grid(){
    for(int row = 0; row < 9; ++row)
        matching_permutations[row].reserve(MATCHING_PERMUTATIONS_RESERVE_AMOUNT);

    for(int i = 0; i < NUM_STARTING_ENTRIES; ++i)
        set_value(STARTING_ENTRIES[i][0], STARTING_ENTRIES[i][1], STARTING_ENTRIES[i][2]);
}


Grid::Grid(const Grid& grid){
    for(int row = 0; row < 9; ++row)
    for(int col = 0; col < 9; ++col)
        squares[row][col] = std::move(grid.at(row, col));
}


auto Grid::set_value(int row, int col, int new_value) -> bool {
    if(new_value < 0 || new_value > 9)
        throw std::invalid_argument("New value is out of bounds.");

    if(row < 0 || row >= 9 || col < 0 || col >= 9)
        throw std::invalid_argument("Position is out of bounds.");

    if(!squares[row][col].blank)
        return squares[row][col].value == new_value;

    if(squares[row][col].blocked_entries[new_value])
        return false;

    for(int i = 0; i < 9; ++i){
        squares[i][col].blocked_entries[new_value] = true;
        squares[row][i].blocked_entries[new_value] = true;
        squares[((row / 3) * 3) + (i / 3)][((col / 3) * 3) + (i % 3)].blocked_entries[new_value] = true;
    }

    squares[row][col].value = new_value;
    squares[row][col].blank = false;
    return true;
}


auto Grid::match_permutation(Permutation& permutation) -> void {
    for(int row = 0; row < 9; ++row)
        if(matches_row(permutation, row))
            matching_permutations[row].insert( permutation_to_int(permutation) );
}


auto Grid::matches_row(Permutation& permutation, int row) -> bool {
    for(int col = 0; col < 9; ++col){
        if(squares[row][col].blank){
            if(squares[row][col].blocked_entries[permutation[col]])
                return false;
        }
            
        else if(squares[row][col].value != permutation[col])
            return false;
    }

    return true;
}


auto Grid::find_multiples(int gcd, bool exhaustive_search) -> std::array<std::unordered_set<int>, 9> {
    std::array<std::unordered_set<int>, 9> multiples;

    for(
        int i = std::max(SMALLEST_POSS_ROW / gcd, 1);
        gcd * i <= BIGGEST_POSS_ROW;
        ++i
    ){
        int multiple = gcd * i;
        if(!is_permutation(multiple)) continue;

        for(int row = 0; row < 9; ++row){
            if(!exhaustive_search && !multiples[row].empty()) continue;

            if(matching_permutations[row].contains(multiple))
                multiples[row].insert(multiple);
        }
            
    }

    return multiples;
}


auto Grid::primitive_gcd_test(int gcd) -> bool {
    std::array<std::unordered_set<int>, 9> multiples = find_multiples(gcd, false);

    for(int row = 0; row < 9; ++row)
        if(multiples[row].empty())
            return false;

    return true;
}


auto Grid::gcd_test(int gcd) -> bool {
    std::array<std::unordered_set<int>, 9> multiples = find_multiples(gcd, true);

    std::queue<std::pair<Grid, int>> possible_grids;
    possible_grids.push({Grid(), 0});

    while(!possible_grids.empty()){
        const auto& [previous_grid, row] = possible_grids.front();
        possible_grids.pop();

        for(int permutation : multiples[row]){
            Grid grid(previous_grid);
            int col = 8;

            while(col >= 0){
                int digit = permutation % 10;

                if(!grid.set_value(row, col, digit)) break;

                --col, permutation /= 10;
            }

            if(col < 0){
                if(row == 8){
                    grid.print();
                    return true;
                }

                possible_grids.push({grid, row + 1});
            }
        }
    }

    return false;
}


auto Grid::print() -> void {
    for(int row = 0; row < 9; ++row){
        if(row % 3 == 0) std::cout << "\n"; 
        
        for(int col = 0; col < 9; ++ col){
            if(squares[row][col].blank) std::cout << "_ ";
            else std::cout << squares[row][col].value << " ";

            if(col % 3 == 2) std::cout << " ";
        }

        std::cout << "\n";
    }
}