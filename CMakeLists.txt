cmake_minimum_required(VERSION 3.20)

project(domino)

set(CMAKE_CXX_STANDARD 20)

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

target_link_libraries(
    domino
    PRIVATE
    asio::asio
)

qt_add_executable(
    domino_gui
    gui/main.cpp
    gui/mainwindow.cpp
)

target_link_libraries(
    domino_gui
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
add_custom_command(
    TARGET domino_gui
    POST_BUILD

    COMMAND
        ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:domino_gui>/platforms

    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/Qt6/plugins/platforms/qwindows.dll
        $<TARGET_FILE_DIR:domino_gui>/platforms/

    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/debug/Qt6/plugins/platforms/qwindowsd.dll
        $<TARGET_FILE_DIR:domino_gui>/platforms/
)