#ifndef SQUARE_H
#define SQUARE_H

#include "config.h"

#include <vector>

class Square{
    private:
        int row;
        int col;
        int type;

        std::vector<Square*> adjacents;

    public:
        Square(int _row, int _col) : row{_row}, col{_col}, type{SQUARE_TYPES[row][col]} {}

        inline void add_adjacent(Square* adjacent){ adjacents.push_back(adjacent); }
        inline int get_num_adjacents() const { return adjacents.size(); }
        inline Square* get_adjacent(int index){ return adjacents[index]; }

        inline int get_row() const { return row; }
        inline int get_col() const { return col; }
        inline int get_type() const { return type; }
};

#endif