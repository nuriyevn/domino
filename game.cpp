#include "game.hpp"

#include <iostream>
#include <cassert>

void Game::initialize()
{
    std::cout << "Initializing domino game...\n";
    boneyard_.initialize();
    std::cout << "Boneyard initialized with tiles:\n";
    boneyard_.print();

    deal_tiles();
    std::cout << "Player 1 hand:\n";
    player1_.print_hand();
    std::cout << "Player 2 hand:\n";
    player2_.print_hand();
    std::cout.flush();

    std::cout << "Boneyard tiles after dealing:\n";
    boneyard_.print(); 

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

        board_.print();
        std::cout << "Player 1 hand:\n";
        player1_.print_hand();
        std::cout << "Player 2 hand:\n";
        player2_.print_hand();
        std::cout.flush();
        Player& player =
            get_player(current_turn_);

        if (player.empty())
        {
            running_ = false;

            break;
        }

        if (!player.has_playable_tile(board_))
        {
            while (!boneyard_.empty() &&
                   !player.has_playable_tile(board_))
            {
                const Tile drawn_tile = boneyard_.draw();
                player.addTile(drawn_tile);

                std::cout << "Player "
                          << (current_turn_ ==
                              PlayerId::Player1
                                  ? "1"
                                  : "2")
                          << " draws " << drawn_tile << " from the boneyard.\n";
            }

            if (!player.has_playable_tile(board_))
            {
                next_turn();

                continue;
            }
        }

        Move move = player.find_playable_move(board_);
        std::cout << "Player "
                  << (current_turn_ ==
                      PlayerId::Player1
                          ? "1"
                          : "2")
                  << " plays "
                  << move.tile
                  << " on the "
                  << (move.side ==
                      Side::Left
                          ? "left"
                          : "right")
                  << ".\n";
        assert(board_.play(move));

        assert(player.removeTile(move.tile));

        if (player.empty())
        {
            finish_round(current_turn_);

            break;
        }

        next_turn();
    }
}

Game::Game(std::unique_ptr<Network> network, PlayerId local_player)
    : network_(std::move(network)), local_player_(local_player)
{
}

Game::Game(
    PlayerId local_player)
    : local_player_(local_player)
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

Move Game::get_move_from_player(
    Player& player)
{
    while (true)
    {
        player.print_hand();

        std::size_t tile_index;

        std::cout
            << "Choose a tile: ";

        std::cin >> tile_index;

        int side;

        std::cout
            << "Choose a side "
            << "(0 = left, 1 = right): ";

        std::cin >> side;

        Move move{
            player.hand().at(tile_index),
            side == 0
                ? Side::Left
                : Side::Right
        };

        if (board_.can_place(move))
        {
            return move;
        }

        std::cout
            << "Illegal move.\n";
    }
}

void Game::finish_round(PlayerId winner)
{
    PlayerId loser =
        winner == PlayerId::Player1
            ? PlayerId::Player2
            : PlayerId::Player1;

    int score =
        get_player(loser).points();

    std::cout
        << "Player "
        << (winner == PlayerId::Player1
                ? "1"
                : "2")
        << " wins the round!\n";

    std::cout
        << "Points earned: "
        << score
        << '\n';

    running_ = false;
}
