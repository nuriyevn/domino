#ifndef MOVE_HPP
#define MOVE_HPP

#include "side.hpp"
#include "tile.hpp"

struct Move
{
    Tile tile;

    Side side;
};
#endif