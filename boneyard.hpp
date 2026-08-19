#ifndef BONEYARD_HPP
#define BONEYARD_HPP

#include <vector>
#include "tile.hpp"

class Boneyard
{
public:
    void initialize();

    Tile draw();

    bool empty() const;
    
    void print() const; // TODO for debug only

private:
    std::vector<Tile> tiles_;
};
#endif