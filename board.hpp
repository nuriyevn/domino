

#ifndef BOARD_HPP
#define BOARD_HPP

#include <deque>
#include "move.hpp"

class Board
{
public:
    bool can_place(const Move& move) const;

    bool play(const Move& move);

private:
    std::deque<Tile> tiles_;
};

#endif
