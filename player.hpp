#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "tile.hpp"

class Player
{
public:
    void addTile(const Tile& tile);

    void removeTile(std::size_t index);

    bool empty() const;

    constexpr int points() const
    {
        int total = 0;

        for (const auto& tile : hand_)
        {
            total += tile.points();
        }

        return total;
    }

private:
    std::vector<Tile> hand_;
};

#endif