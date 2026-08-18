#include "boneyard.hpp"
#include <stdexcept>
#include <algorithm>
#include <random>

void Boneyard::initialize()
{
    tiles_.clear();

    for (int left = 0; left <= 6; ++left)
    {
        for (int right = left; right <= 6; ++right)
        {
            tiles_.emplace_back(
                left,
                right);
        }
    }

    std::random_device random_device;

    std::mt19937 generator(
        random_device());

    std::shuffle(
        tiles_.begin(),
        tiles_.end(),
        generator);
}

bool Boneyard::empty() const
{
    return tiles_.empty();
}

Tile Boneyard::draw()
{
    if (empty())
    {
        throw std::runtime_error(
            "The boneyard is empty.");
    }

    Tile tile = tiles_.back();

    tiles_.pop_back();

    return tile;
}