#ifndef TILE_H
#define TILE_H

#include "fence.h"

#include <stdexcept>


enum class TileType{
    EmptyTile,
    FenceTile,
    Post
};


class Tile{
    private:
        int row;
        int col;

    public:
        TileType type;

        Tile(int _row, int _col) : row {_row}, col {_col}, type{TileType::EmptyTile} {}
        Tile(int _row, int _col, TileType _type) : row {_row}, col {_col}, type {_type} {}

        int get_row() const { return row; }
        int get_col() const { return col; }

        virtual int get_weight() const { throw std::logic_error("Tile does not have weight."); };

        virtual std::weak_ptr<Fence> get_fence_ptr() const { throw std::logic_error("Tile does not have fence pointer."); }
};


class FenceTile : public Tile{
    private:
        std::weak_ptr<Fence> fence_ptr;

    public :
        FenceTile(int _row, int _col, std::shared_ptr<Fence> _fence_ptr) : 
            Tile(_row, _col, TileType::FenceTile), fence_ptr{_fence_ptr} {}
        
        std::weak_ptr<Fence> get_fence_ptr() const override { return fence_ptr; }
};


#endif