#ifndef HISTORYCARD_H
#define HISTORYCARD_H

#include <QWidget>

namespace Ui {
class HistoryCard;
}

class HistoryCard : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryCard(QWidget *parent = nullptr);
    ~HistoryCard();

private:
    Ui::HistoryCard *ui;
};

#endif // HISTORYCARD_H
