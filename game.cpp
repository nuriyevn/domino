#include "game.hpp"

#include <iostream>

void Game::initialize()
{
    std::cout << "Initializing domino game...\n";
    boneyard_.initialize();

    deal_tiles();
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

PlayerId Game::determine_starting_player() const
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
        return best1.left() >= best2.left()
            ? PlayerId::Player1
            : PlayerId::Player2;
    }

    if (has_double1)
    {
        return PlayerId::Player1;
    }

    if (has_double2)
    {
        return PlayerId::Player2;
    }

    int highest_point_player_1 = 0;

    for (const auto& tile : hand1)
    {
        highest_point_player_1 =
            std::max(
                highest_point_player_1,
                tile.points());
    }

    int highest_point_player_2 = 0;

    for (const auto& tile : hand2)
    {
        highest_point_player_2 =
            std::max(
                highest_point_player_2,
                tile.points());
    }

    return highest_point_player_1 >= highest_point_player_2
        ? PlayerId::Player1
        : PlayerId::Player2;
}