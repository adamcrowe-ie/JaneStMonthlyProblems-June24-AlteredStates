#include "grid.h"
#include "polynomial.h"

#include <set>
#include <utility>
#include <random>
#include <array>

#include <iostream>

using Coord = std::pair<int, int>;
using Trip = std::vector<Square*>;
using Solution = std::array<int, 3>;


std::random_device rand_dev;
std::mt19937 mt(rand_dev());
std::uniform_real_distribution<double> dist(0.0, 1.0);


int generate_random_int(int upper_bound){
    double random_number = dist(mt);

    return static_cast<int>(std::floor(random_number * upper_bound));
}


Trip generate_trip(Grid& grid, bool start_at_top){
    Trip trip;

    for(;;){
        int row = start_at_top ? 0 : LENGTH - 1,
            col = 0;
            
        std::set<std::pair<int, int>> visited;
        trip.clear();
        
        while(!visited.contains({row, col})){
            visited.insert({row, col});

            Square& square = grid.at(row, col);
            trip.push_back(&square);

            int choice = generate_random_int(square.get_num_adjacents());
            Square* next = square.get_adjacent(choice);

            row = next -> get_row();
            col = next -> get_col();

            if(col == LENGTH - 1)
            if((start_at_top && row == LENGTH - 1) || (!start_at_top && row == 0)){
                trip.push_back(next);
                goto found_trip;
            }
        }
    }

    found_trip:
    return trip;
}


Polynomial calculate_trip_score(Trip& trip){
    Polynomial score;
    int last_square_type = 0;   // trips always start on A

    for(const Square* square_ptr : trip){
        int type = square_ptr -> get_type();
        PolynomialTerm next_term = {1, (type == 0 ? 1 : 0), (type == 1 ? 1 : 0), (type == 2 ? 1 : 0)};

        if(type == last_square_type) score.add_term(next_term);
        else score.multiply_term(next_term);

        last_square_type = type;
    }

    score.remove_zeroes();
    return score;
}


Tuple find_solution(Polynomial scores[2], int upper_limit){
    Tuple optimal_solution = {-1, -1, -1};
    int optimal_sum = upper_limit;

    for(int A = 0; A < upper_limit; ++A)
    for(int B = 0; A + B < upper_limit; ++B)
    for(int C = 0; A + B + C < upper_limit; ++C)
    {
        if(scores[0].evaluate({A, B, C}) == GOAL)
        if(scores[1].evaluate({A, B, C}) == GOAL)
        if(A + B + C < optimal_sum)
            optimal_solution = {A, B, C}, optimal_sum = A + B + C;
    }

    return optimal_solution;
}


void print_trip(Trip trip){
    int n = trip.size();

    for(int i = 0; i < n; ++i){
        std::cout << char(trip[i] -> get_col() + 'a') << (6 - trip[i] -> get_row());

        if(i != n - 1) std::cout << ", ";
        else std::cout << "\n";
    }
}


int main(){
    Grid grid;

    int optimal_score = 50;

    for(;;){
        Trip trips[2] = {
            generate_trip(grid, true), generate_trip(grid, false)
        };

        Polynomial scores[2] = {
            calculate_trip_score(trips[0]), calculate_trip_score(trips[1])
        };

        Tuple solution = find_solution(scores, optimal_score);

        if(solution.A == -1) continue;
        if(solution.A + solution.B + solution.C >= optimal_score) continue;

        optimal_score = solution.A + solution.B + solution.C;
        std::cout << "\nA + B + C = " << optimal_score << "\n";

        std::cout << "A: " << solution.A << " ";
        std::cout << "B: " << solution.B << " ";
        std::cout << "C: " << solution.C << "\n";

        std::cout << "\nFirst Trip: \n";
        print_trip(trips[0]);

        std::cout << "\nSecond Trip: \n";
        print_trip(trips[1]);
    }
}