#ifndef PATH_H
#define PATH_H

#include <vector>

struct Path{
    std::vector<int> positions;
    bool used_blank;
};

class PathCompByLength{
    public:
        bool operator() (const Path& l, const Path& r){
            return l.positions.size() < r.positions.size();
        }
};

#endif