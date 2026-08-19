#include "board.hpp"

bool Board::can_place(const Move& move) const
{
    if (tiles_.empty())
    {
        return true;
    }

    int board_value =
        move.side == Side::Left
            ? tiles_.front().left()
            : tiles_.back().right();

    return move.tile.left() == board_value ||
           move.tile.right() == board_value;
}


bool Board::play(const Move& move)
{
    if (!can_place(move))
    {
        return false;
    }

    Tile tile = move.tile;

    if (tiles_.empty())
    {
        tiles_.push_back(tile);

        return true;
    }

    if (move.side == Side::Left)
    {
        int board_value = tiles_.front().left();

        if (tile.left() == board_value)
        {
            tile = tile.flipped();
        }

        tiles_.push_front(tile);
    }
    else
    {
        int board_value = tiles_.back().right();

        if (tile.right() == board_value)
        {
            tile = tile.flipped();
        }

        tiles_.push_back(tile);
    }

    return true;
}

void Board::print() const
{
    if (tiles_.empty())
    {
        std::cout
            << "Board: (empty)\n";

        return;
    }

    std::cout
        << "Board ("
        << left_value()
        << '-'
        << right_value()
        << "): ";

    for (const auto& tile : tiles_)
    {
        std::cout
            << tile
            << ' ';
    }

    std::cout
        << '\n';
}

int Board::left_value() const
{
    return tiles_.front().left();
}

int Board::right_value() const
{
    return tiles_.back().right();
}