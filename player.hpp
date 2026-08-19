#ifndef PLAYER_HPP
#define PLAYER_HPP


#include <vector>
#include "tile.hpp"
#include "board.hpp"
#include "move.hpp"
#include <stdexcept>
#include <iostream>


class Player
{
public:
    void addTile(const Tile& tile);
    bool removeTile(const Tile& tile);
    bool empty() const;

    int points() const;
    bool has_playable_tile(
        const Board& board) const;

    Move find_playable_move(
        const Board& board) const;
    const std::vector<Tile>& hand() const;
    void print_hand() const;

private:
    std::vector<Tile> hand_;
};




#endif