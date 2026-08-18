#include "game.hpp"

#include <iostream>
#include <cassert>

void Game::initialize()
{
    std::cout << "Initializing domino game...\n";
    boneyard_.initialize();

    deal_tiles();

    OpeningMove opening =
        determine_opening_move();

    current_turn_ = opening.player;
    assert(
        board_.play(
            Move{
                opening.tile,
                Side::Right
            }));

    assert(
        get_player(current_turn_)
            .removeTile(
                opening.tile));

    next_turn();
 
}

void Game::run()
{
    while (running_)
    {
        Player& player =
            get_player(
                current_turn_);
        
        if (player.empty())
        {
            running_ = false;

            continue;
        }

        std::cout
            << "Player turn...\n";

        next_turn();
    }
}

Game::Game(std::unique_ptr<Network> network, PlayerId local_player)
    : network_(std::move(network)), local_player_(local_player)
{
}

Player& Game::get_player(PlayerId id)
{
    if (id == PlayerId::Player1)
    {
        return player1_;
    }

    return player2_;
}
void Game::deal_tiles()
{
    for (int i = 0; i < 7; ++i)
    {
        player1_.addTile(
            boneyard_.draw());

        player2_.addTile(
            boneyard_.draw());
    }
}


void Game::next_turn()
{
    if (current_turn_ ==
        PlayerId::Player1)
    {
        current_turn_ =
            PlayerId::Player2;
    }
    else
    {
        current_turn_ =
            PlayerId::Player1;
    }
}

OpeningMove Game::determine_opening_move() const
{
    const auto& hand1 = player1_.hand();

    const auto& hand2 = player2_.hand();

    Tile best1{0, 0};
    Tile best2{0, 0};

    bool has_double1 = false;
    bool has_double2 = false;

    for (const auto& tile : hand1)
    {
        if (tile.is_double())
        {
            if (!has_double1 ||
                tile.left() > best1.left())
            {
                best1 = tile;

                has_double1 = true;
            }
        }
    }

    for (const auto& tile : hand2)
    {
        if (tile.is_double())
        {
            if (!has_double2 ||
                tile.left() > best2.left())
            {
                best2 = tile;

                has_double2 = true;
            }
        }
    }

    if (has_double1 && has_double2)
    {
        if (best1.left() >= best2.left())
        {
            return {PlayerId::Player1, best1};
        }

        return {PlayerId::Player2, best2};
    }

    if (has_double1)
    {
        return {PlayerId::Player1, best1};
    }

    if (has_double2)
    {
        return {PlayerId::Player2, best2};
    }

    Tile highest1 = hand1.front();

    for (const auto& tile : hand1)
    {
        if (tile.points() > highest1.points())
        {
            highest1 = tile;
        }
    }

    Tile highest2 = hand2.front();

    for (const auto& tile : hand2)
    {
        if (tile.points() > highest2.points())
        {
            highest2 = tile;
        }
    }

    if (highest1.points() >= highest2.points())
    {
        return {PlayerId::Player1, highest1};
    }

    return {PlayerId::Player2, highest2};
}