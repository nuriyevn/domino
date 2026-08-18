#pragma once
#include <memory>
#include  "network.hpp"
#include "player.hpp"
#include "boneyard.hpp"
#include "board.hpp"
#include "playerid.hpp"
#include "opening_move.hpp"

class Network;



class Game
{
private:
    OpeningMove determine_opening_move() const;

public:
    explicit Game(std::unique_ptr<Network> network, PlayerId local_player);

    void initialize();

    void run();
    Player& get_player(PlayerId id);
    void deal_tiles();
    void next_turn();
private:
    std::unique_ptr<Network> network_;
    bool running_ = true;
    PlayerId local_player_;
    Player player1_;
    Player player2_;
    Board board_;
    Boneyard boneyard_;
    PlayerId current_turn_ = PlayerId::Player1;

};