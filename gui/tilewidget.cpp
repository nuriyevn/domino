#include "tilewidget.hpp"

#include <QPainter>

TileWidget::TileWidget(
    const Tile& tile,
    bool face_up,
    QWidget* parent)
    : QWidget(parent),
      left_(tile.left()),
      right_(tile.right()),
      face_up_(face_up)
{
    setFixedSize(80, 40);
}

void TileWidget::paintEvent(
    QPaintEvent*)
{
    QPainter painter(this);

    painter.setRenderHint(
        QPainter::Antialiasing);

    painter.drawRoundedRect(
        rect().adjusted(1, 1, -1, -1),
        5,
        5);

    if (!face_up_)
    {
        painter.drawText(
            rect(),
            Qt::AlignCenter,
            "?");

        return;
    }

    const int middle =
        width() / 2;

    painter.drawLine(
        middle,
        0,
        middle,
        height());

    painter.drawText(
        QRect(
            0,
            0,
            middle,
            height()),
        Qt::AlignCenter,
        QString::number(left_));

    painter.drawText(
        QRect(
            middle,
            0,
            middle,
            height()),
        Qt::AlignCenter,
        QString::number(right_));
}