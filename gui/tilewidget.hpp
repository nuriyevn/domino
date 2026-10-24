#pragma once

#include <QWidget>
#include "../tile.hpp"

class TileWidget : public QWidget
{
public:
    TileWidget(
        const Tile& tile,
        bool face_up,
        QWidget* parent = nullptr);

protected:
    void paintEvent(
        QPaintEvent* event) override;

private:
    int left_;
    int right_;
    bool face_up_;
};