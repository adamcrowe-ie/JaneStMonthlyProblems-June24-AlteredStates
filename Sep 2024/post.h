#ifndef POST_H
#define POST_H

#include "tile.h"
#include "coord.h"

#include <vector>
#include <memory>

class Post : public Tile{
    private:
        std::vector<std::shared_ptr<Fence>> fences;

    public:
        int weight;

        Post(int _row, int _col, int _weight) : 
            Tile(_row, _col, TileType::Post), weight {_weight} {}

        int get_weight() const override { return weight; }

        void add_fence(std::shared_ptr<Fence> fence){ fences.push_back(fence); }
};

#endif