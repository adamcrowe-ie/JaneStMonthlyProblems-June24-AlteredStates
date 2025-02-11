#ifndef GRID_H
#define GRID_H

#include "post.h"

#include <vector>
#include <memory>

template<typename T>
using vec = std::vector<T>;

class Grid{
    public:
        vec<vec<std::shared_ptr<Tile>>> tiles;

        vec<std::shared_ptr<Post>> posts;
        vec<std::shared_ptr<Fence>> fences;

        Grid();

        void print();
};

#endif