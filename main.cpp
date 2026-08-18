#include <iostream>
#include <string>
#include "game.hpp"
#include "network.hpp"
#include <asio.hpp>

enum class Mode
{
    Host,
    Client
};


void run_host()
{
    Server server;

    server.start(5000);

    server.send("Hello from the host!");

    std::cout << server.receive() << '\n';
}

void run_client(const std::string& ip)
{
    Client client;

    client.connect(ip, 5000);

    std::cout << client.receive() << '\n';

    client.send("Hello from the client!");
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