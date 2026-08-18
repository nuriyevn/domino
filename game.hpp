#pragma once
#include <memory>
#include  "network.hpp"
class Network;


class Game
{
public:
    explicit Game(std::unique_ptr<Network> network);

    void initialize();

    void run();

private:
    std::unique_ptr<Network> network_;

    bool running_ = true;
};