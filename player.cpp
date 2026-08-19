#include "player.hpp"


void Player::addTile(const Tile& tile)
{
    hand_.push_back(tile);
}

bool Player::removeTile(const Tile& tile)
{
    auto it =
        std::find(
            hand_.begin(),
            hand_.end(),
            tile);

    if (it == hand_.end())
    {
        return false;
    }

    hand_.erase(it);

    return true;
}

bool Player::empty() const
{
    return hand_.empty();
}

int Player::points() const
{
    int total = 0;

    for (const auto& tile : hand_)
    {
        total += tile.points();
    }

    return total;
}

const std::vector<Tile>& Player::hand() const
{
    return hand_;
}

bool Player::has_playable_tile(
    const Board& board) const
{
    for (const auto& tile : hand_)
    {
        if (board.can_place(
                Move{tile, Side::Left}))
        {
            return true;
        }

        if (board.can_place(
                Move{tile, Side::Right}))
        {
            return true;
        }
    }

    return false;
}

Move Player::find_playable_move(
    const Board& board) const
{
    for (const auto& tile : hand_)
    {
        Move left_move{
            tile,
            Side::Left
        };

        if (board.can_place(left_move))
        {
            return left_move;
        }

        Move right_move{
            tile,
            Side::Right
        };

        if (board.can_place(right_move))
        {
            return right_move;
        }
    }

    throw std::runtime_error(
        "No playable move.");
}


void Player::print_hand() const
{
    for (std::size_t i = 0;
         i < hand_.size();
         ++i)
    {
        std::cout
            << i
            << ": "
            << hand_[i]
            << '\n';
    }
}