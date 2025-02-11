#ifndef SQUARE_H
#define SQUARE_H

struct Square{
    bool blank = true;
    int value;

    bool blocked_entries[10] = {};
};

#endif