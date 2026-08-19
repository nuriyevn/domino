

#ifndef TILE_HPP
#define TILE_HPP
#include <ostream>
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

    constexpr bool operator==(const Tile& other) const
    {
        return left_ == other.left_
            && right_ == other.right_;
    }
    
    constexpr int highest_value() const
    {
        return left_ > right_
            ? left_
            : right_;
    }

private:
    int left_;

    int right_;
};

std::ostream& operator<<(
    std::ostream& os,
    const Tile& tile);


    
#endif