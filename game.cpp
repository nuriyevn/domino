#include "game.hpp"

#include <iostream>

void Game::initialize()
{
    std::cout << "Initializing domino game...\n";
}

void Game::run()
{
    while (running_)
    {
        std::cout << "Game loop...\n";

        running_ = false;
    }
}

Game::Game(std::unique_ptr<Network> network)
    : network_(std::move(network))
{
}