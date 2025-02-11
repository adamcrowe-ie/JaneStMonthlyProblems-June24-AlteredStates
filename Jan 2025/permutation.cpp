#include "permutation.h"

int permutation_to_int(Permutation& permutation){
    int digit = 1, result = 0;

    for(int i = 0; i < 9; ++i)
        result += permutation[8 - i] * digit, digit *= 10;

    return result;
}


bool is_permutation(int x){
    bool seen[10] = {};
    int num_seen = 0;

    if(x < 100'000'000)
        seen[0] = true, ++num_seen;

    while(x){
        int digit = x % 10;

        if(seen[digit]) return false;

        seen[digit] = true, ++num_seen, x /= 10;
    }

    return (num_seen == 9);
}