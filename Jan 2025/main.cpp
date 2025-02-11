#include "grid.h"

#include <chrono>
#include <iostream>


void match_all_permutations(Grid& grid){
    Permutation permutation = std::to_array(STARTING_PERMUTATION);
    
    do grid.match_permutation(permutation);
    while(next_permutation(permutation)); 
}


uint64_t current_time_in_ms(){
    using namespace std::chrono;

    return duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    ).count();
}


void find_gcd(Grid& grid){
    uint64_t start_time = current_time_in_ms();
    int log_count = 0;

    for(int gcd = BIGGEST_POSS_GCD; gcd > 0; gcd -= 2){
        if(gcd % 5 == 0) continue;

        if(current_time_in_ms() - start_time > log_count * LOG_INTERVAL){
            std::cout << "Tested as far as " << gcd << "\n";
            ++log_count;
        }

        if(!grid.primitive_gcd_test(gcd)) continue;
        std::cout << "Passed primitve GCD test " << gcd << "\n";

        if(!grid.gcd_test(gcd)) continue;
        
        std::cout << "\nSOLUTION FOUND\n" << "Largest GCD: " << gcd;
        break;
    }
}


int main(){
    Grid grid;

    std::cout << "Mathcing all permutations to possible rows... ";
    match_all_permutations(grid);
    std::cout << "All permutations matched.\n\n";
    

    std::cout << "Testing all possible gcds:\n\n";
    find_gcd(grid);
}