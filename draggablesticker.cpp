#include "draggablesticker.h"

DraggableSticker::DraggableSticker(const QString &emoji, QWidget *parent)
    : QLabel(parent)
{
    setText(emoji);
    setStyleSheet("font-size: 28px;");
    resize(40, 40);
    setAlignment(Qt::AlignCenter);
    setCursor(Qt::OpenHandCursor);
}

void DraggableSticker::mousePressEvent(QMouseEvent *event)
{
    dragStartPosition = event->pos();
}

void DraggableSticker::mouseMoveEvent(QMouseEvent *event)
{
    QPoint delta = event->pos() - dragStartPosition;
    move(pos() + delta);
}