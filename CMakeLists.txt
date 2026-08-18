cmake_minimum_required(VERSION 3.20)

project(domino)
find_package(asio CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
add_executable(
    domino

    main.cpp
    game.cpp
    network.cpp
    board.cpp
)

target_link_libraries(
    domino
    PRIVATE
    asio::asio
)