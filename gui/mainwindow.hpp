#pragma once

#include <QMainWindow>
#include "../game.hpp"
#include "../playerid.hpp"
#include <QGridLayout>
class QLabel;
class QWidget;
class QHBoxLayout;
class QVBoxLayout;
#include <QTimer>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(
        QWidget* parent = nullptr);

private:
    void update_view();
    QWidget* central_widget_;
    QVBoxLayout* main_layout_;



    QWidget* opponent_hand_widget_;
    QWidget* board_widget_;
    QWidget* player_hand_widget_;


    QLabel* opponent_label_;
    QLabel* board_title_;
    QLabel* player_label_;
    QLabel* status_label_;

    QHBoxLayout* opponent_layout_;
    QGridLayout* board_layout_;
    QHBoxLayout* player_layout_;

    Game game_;
    QTimer* timer_;
};