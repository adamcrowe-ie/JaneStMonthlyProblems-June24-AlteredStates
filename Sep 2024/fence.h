#ifndef FENCE_H
#define FENCE_H

#include <utility>
#include <memory>

class Post;
class Grid;

class Fence{
    private:
        int direction_y;
        int direction_x;

        std::weak_ptr<Post> post_ptr;

    public:
        int length = 0;

        Fence(int _direction_y, int _direction_x, std::shared_ptr<Post> _post_ptr) : 
            direction_y {_direction_y}, direction_x {_direction_x}, post_ptr {_post_ptr} {}

        std::weak_ptr<Post> get_post_ptr() const { return post_ptr; }
        std::pair<int, int> get_direction() const { return {direction_y, direction_x}; }
};

#endif