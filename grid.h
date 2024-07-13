#ifndef GRID_H
#define GRID_H

#include <string>

class Grid{
    private:
        std::string squares;
    public:
        Grid(std::string sqs) : squares(sqs) {};

        int evaluate();
        bool contains_state(std::string);

        inline std::string get_squares(){ return squares; }
        inline void set_squares(std::string s){ if(s.size() == 25) squares = s; }

        inline char& operator[] (int i) { return squares[i]; }
};

struct GridScorePair{
    std::string grid;
    int score;
};

#endif
