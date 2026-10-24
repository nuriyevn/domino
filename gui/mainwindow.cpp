#include "mainwindow.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include "tilewidget.hpp"
#include <QGridLayout>


void MainWindow::update_view()
{
    while (QLayoutItem* item =
               opponent_layout_->takeAt(0))
    {
        delete item->widget();
        delete item;
    }

    while (QLayoutItem* item =
               board_layout_->takeAt(0))
    {
        delete item->widget();
        delete item;
    }

    while (QLayoutItem* item =
               player_layout_->takeAt(0))
    {
        delete item->widget();
        delete item;
    }

    const auto& opponent_hand =
        game_.get_player(
            PlayerId::Player2)
            .hand();

    for (const Tile& tile :
         opponent_hand)
    {
        opponent_layout_->addWidget(
            new TileWidget(
                tile,
                false));
    }

    const auto& board_tiles =
        game_.board().tiles();

    for (std::size_t i = 0;
         i < board_tiles.size();
         ++i)
    {
        board_layout_->addWidget(
            new TileWidget(
                board_tiles[i],
                true),
            0,
            static_cast<int>(i));
    }

    const auto& player_hand =
        game_.get_player(
            game_.local_player())
            .hand();

    for (const Tile& tile :
         player_hand)
    {
        player_layout_->addWidget(
            new TileWidget(
                tile,
                true));
    }
}

MainWindow::MainWindow(
    QWidget *parent)
    : QMainWindow(parent), game_(PlayerId::Player1)
{
    game_.initialize();

    setWindowTitle("Domino");

    resize(1000, 700);

    central_widget_ =
        new QWidget(this);

    setCentralWidget(
        central_widget_);

    main_layout_ =
        new QVBoxLayout(
            central_widget_);

    opponent_label_ =
        new QLabel(
            "Opponent hand");
    
    opponent_hand_widget_ =
        new QWidget;
    
    opponent_layout_ =
        new QHBoxLayout(
            opponent_hand_widget_);

    const auto& opponent_hand = game_.get_player(
        PlayerId::Player2)
        .hand();

    for (const Tile& tile :
        opponent_hand)
    {
        opponent_layout_->addWidget(
            new TileWidget(
                tile,
                false));
    }

    auto *board_title =
        new QLabel(
            "Domino board");

    board_widget_ =
        new QWidget();

    board_layout_ =
        new QGridLayout(
            board_widget_);


    const auto& board_tiles =
    game_.board().tiles();

    for (std::size_t i = 0;
        i < board_tiles.size();
        ++i)
    {
        board_layout_->addWidget(
            new TileWidget(
                board_tiles[i],
                true),
            0,
            static_cast<int>(i));
    }

 
    player_label_ =
        new QLabel(
            "Your hand");
    player_hand_widget_ =
    new QWidget;
    
    player_layout_ =
        new QHBoxLayout(
            player_hand_widget_);

    const auto& player_hand =
        game_.get_player(
            game_.local_player())
            .hand();

    for (const Tile& tile :
        player_hand)
    {
        player_layout_->addWidget(
            new TileWidget(
                tile,
                true));
    }

    status_label_ =
        new QLabel(
            "Player 1's turn");

    main_layout_->addWidget(
        opponent_label_);
    
    main_layout_->addWidget(
        opponent_hand_widget_);

    main_layout_->addWidget(
        board_title);

    main_layout_->addWidget(
        board_widget_,
        1);

    main_layout_->addWidget(
        player_label_);
    main_layout_->addWidget(
    player_hand_widget_);

    main_layout_->addWidget(
        status_label_);

    timer_ =
    new QTimer(this);

    connect(
        timer_,
        &QTimer::timeout,
        this,
        [this]()
        {
            game_.play_turn();

            update_view();
        });

    timer_->start(1000);

}
