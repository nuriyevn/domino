#ifndef PLAYER_HPP
#define PLAYER_HPP


#include <vector>
#include "tile.hpp"

class Player
{
public:
    void addTile(const Tile& tile);
    bool removeTile(const Tile& tile);
    bool empty() const;

    int points() const;

    const std::vector<Tile>& hand() const;

private:
    std::vector<Tile> hand_;
};




#endif