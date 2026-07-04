#ifndef DRAGGABLESTICKER_H
#define DRAGGABLESTICKER_H

#include <QLabel>
#include <QMouseEvent>

class DraggableSticker : public QLabel
{
    Q_OBJECT

public:
    explicit DraggableSticker(const QString &emoji, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint dragStartPosition;
};

#endif