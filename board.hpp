

#ifndef BOARD_HPP
#define BOARD_HPP

#include <deque>
#include "move.hpp"
#include <iostream>

class Board
{
public:
    bool can_place(const Move& move) const;

    bool play(const Move& move);

    void print() const;
    int left_value() const;

    int right_value() const;

private:
    std::deque<Tile> tiles_;
};

#endif
