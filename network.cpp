#include "network.hpp"

#include <asio.hpp>

#include <array>
#include <iostream>
#include <memory>
using asio::ip::tcp;

class Server::Impl
{
public:
    asio::io_context io;

    std::unique_ptr<tcp::acceptor> acceptor;

    std::unique_ptr<tcp::socket> socket;
};

class Client::Impl
{
public:
    asio::io_context io;

    std::unique_ptr<tcp::socket> socket;
};

Server::Server()
    : impl_(std::make_unique<Impl>())
{
}

Server::~Server() = default;

bool Server::start(unsigned short port)
{
    try
    {
        impl_->acceptor = std::make_unique<tcp::acceptor>(
            impl_->io,
            tcp::endpoint(tcp::v4(), port));

        impl_->socket =
            std::make_unique<tcp::socket>(impl_->io);

        std::cout << "Waiting for a client...\n";

        impl_->acceptor->accept(*impl_->socket);

        std::cout << "Client connected.\n";

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';

        return false;
    }
}

bool Server::send(const std::string& message)
{
    try
    {
        asio::write(
            *impl_->socket,
            asio::buffer(message));

        return true;
    }
    catch (...)
    {
        return false;
    }
}

std::string Server::receive()
{
    std::array<char, 1024> buffer{};

    std::size_t bytes =
        impl_->socket->read_some(
            asio::buffer(buffer));

    return std::string(
        buffer.data(),
        bytes);
}

Client::Client()
    : impl_(std::make_unique<Impl>())
{
}

Client::~Client() = default;

bool Client::connect(
    const std::string& ip,
    unsigned short port)
{
    try
    {
        impl_->socket =
            std::make_unique<tcp::socket>(
                impl_->io);

        impl_->socket->connect(
            tcp::endpoint(
                asio::ip::make_address(ip),
                port));

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';

        return false;
    }
}

bool Client::send(const std::string& message)
{
    try
    {
        asio::write(
            *impl_->socket,
            asio::buffer(message));

        return true;
    }
    catch (...)
    {
        return false;
    }
}
std::string Client::receive()
{
    std::array<char, 1024> buffer{};

    std::size_t bytes =
        impl_->socket->read_some(
            asio::buffer(buffer));

    return std::string(
        buffer.data(),
        bytes);
}