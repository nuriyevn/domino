#include "tile.hpp"

std::ostream& operator<<(
    std::ostream& os,
    const Tile& tile)
{
    os
        << '['
        << tile.left()
        << '|'
        << tile.right()
        << ']';

    return os;
}