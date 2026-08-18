#ifndef OPENING_MOVE_HPP
#define OPENING_MOVE_HPP


#include "player.hpp"
#include "tile.hpp"
#include "playerid.hpp"

struct OpeningMove
{
    PlayerId player;

    Tile tile;
};

#endif