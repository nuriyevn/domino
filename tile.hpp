

#ifndef TILE_HPP
#define TILE_HPP

class Tile
{
public:
    constexpr Tile(int left, int right)
        : left_(left),
          right_(right)
    {
    }

    constexpr int left() const
    {
        return left_;
    }

    constexpr int right() const
    {
        return right_;
    }

    constexpr int points() const
    {
        return left_ + right_;
    }

    constexpr Tile flipped() const
    {
        return Tile(right_, left_);
    }

    constexpr bool is_double() const
    {
        return left_ == right_;
    }

    constexpr bool contains(int value) const
    {
        return left_ == value ||
            right_ == value;
    }

private:
    int left_;

    int right_;
};
#endif