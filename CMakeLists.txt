cmake_minimum_required(VERSION 3.20)

project(domino)
find_package(asio CONFIG REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(
    Qt6
    REQUIRED
    COMPONENTS
        Core
        Gui
        Widgets
)


set(CMAKE_CXX_STANDARD 20)
add_executable(
    domino

    main.cpp
    game.cpp
    network.cpp
    board.cpp
    player.cpp
    boneyard.cpp
    tile.cpp
)

add_executable(
    domino_gui
    gui/main.cpp
)


target_link_libraries(
    domino
    PRIVATE
    asio::asio
)

target_link_libraries(
    domino_gui
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)
