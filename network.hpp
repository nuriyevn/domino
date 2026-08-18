#pragma once

#include <memory>
#include <string>

class Network
{
public:
    virtual ~Network() = default;

    virtual bool send(const std::string& message) = 0;

    virtual std::string receive() = 0;
};

class Server : public Network
{
public:
    Server();
    ~Server();

    bool start(unsigned short port);

    bool send(const std::string& message) override;

    std::string receive() override;

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

class Client : public Network
{
public:
    Client();
    ~Client();

    bool connect(
        const std::string& ip,
        unsigned short port);

    bool send(const std::string& message) override;

    std::string receive() override;

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};