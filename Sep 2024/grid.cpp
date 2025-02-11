#include "grid.h"
#include "config.h"
#include "coord.h"

#include <iostream>
#include <string>
#include <algorithm>


Grid::Grid(){
    for(int i = 0; i < NUM_ROWS; ++i){
        std::vector<std::shared_ptr<Tile>> row;

        for(int j = 0; j < NUM_COLS; ++j){
            if(i + j < LOWER_SUM || i + j > UPPER_SUM){
                row.push_back(nullptr);
                continue;
            }
            
            Tile tile(i, j);
            row.push_back(std::make_shared<Tile>(std::move(tile)));
        }

        tiles.push_back(std::move(row));
    }

    for(int i = 0; i < NUM_POSTS; ++i){
        auto& [row, col, weight] = POSTS[i];
        Post post(row, col, weight);

        posts.push_back(std::make_shared<Post>(std::move(post)));
        tiles[row][col] = posts.back();

        for(int j = 0; j < NUM_DIRECTIONS; ++j){
            const auto& [y, x] = DIRECTIONS[j];

            Fence fence(y, x, posts.back());
            fences.push_back(std::make_shared<Fence>(std::move(fence)));

            int length = 0, fence_row = row + y, fence_col = col + x;
            const int max_length = FENCES[i][j];

            while(in_bounds(fence_row, fence_col) && length < max_length){
                if(tiles[fence_row][fence_col] -> type != TileType::EmptyTile)
                    break;

                FenceTile fence_tile(fence_row, fence_col, fences.back());
                tiles[fence_row][fence_col] = std::make_shared<FenceTile>(std::move(fence_tile));

                fence_row += y, fence_col += x, ++length;
            }

            fences.back() -> length = length;
            posts.back() -> weight -= length;
            if(posts.back() -> weight < 0)
                throw std::invalid_argument("Too many fences");

            posts.back() -> add_fence(fences.back());
        }
    }
}


void Grid::print(){
    for(const std::vector<std::shared_ptr<Tile>>& row : tiles){
        std::string output;
        int padding = 0;

        for(const std::shared_ptr<Tile>& tile_ptr : row){
            if(!tile_ptr){
                ++padding;
                continue;
            }

            switch(tile_ptr -> type){
                case TileType::EmptyTile:
                    output += ". ";
                    break;

                case TileType::FenceTile: {
                    std::shared_ptr<Fence> fence_ptr = (tile_ptr -> get_fence_ptr()).lock();

                    auto [y, x] = fence_ptr -> get_direction();

                    if(!x) output += R"(\ )";
                    else if(!y) output += "- ";
                    else output += "/ ";

                    break;
                }
                case TileType::Post: {
                    int weight = tile_ptr -> get_weight();
                    
                    if(weight < 10){
                        output += std::to_string(weight);
                        output += " ";
                    }
                    else
                        output += "X ";

                    break;
                }
            }
        }

        std::cout << std::string(padding, ' ') << output << "\n";
    }

    std::cout << "\n";
}