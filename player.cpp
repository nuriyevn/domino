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