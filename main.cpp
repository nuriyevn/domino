#include <iostream>
#include <string>
#include "game.hpp"
#include "network.hpp"
#include <asio.hpp>

// How was the application launched
enum class Mode
{
    Host,
    Client
};




void run_host()
{
    auto network = std::make_unique<Server>();

    network->start(5000);

    Game game(
        std::move(network),
        PlayerId::Player1);

    game.initialize();

    game.run();
}


void run_client(const std::string& ip)
{
    auto network = std::make_unique<Client>();

    network->connect(ip, 5000);

    Game game(
        std::move(network),
        PlayerId::Player2);

    game.initialize();

    game.run();
}


int main(int argc, char* argv[])
{

    asio::io_context io;

    if (argc < 2)
    {
        std::cout
            << "Usage:\n"
            << "  domino host\n"
            << "  domino join <ip>\n";

        return 1;
    }

    std::string mode = argv[1];

    if (mode == "host")
    {
        run_host();
    }
    else if (mode == "join")
    {
        if (argc < 3)
        {
            std::cerr << "Missing IP address.\n";

            return 1;
        }

        run_client(argv[2]);
    }

    return 0;
}