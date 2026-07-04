#ifndef HABITCARD_H
#define HABITCARD_H

#include <QWidget>

namespace Ui {
class HabitCard;
}

class HabitCard : public QWidget
{
    Q_OBJECT

public:
    explicit HabitCard(int habitId, QString name, QString emoji,
                       bool completedToday, int streak,
                       QWidget *parent = nullptr);
    ~HabitCard();

    int getHabitId() const;
    void setCompleted(bool done);

signals:
    void toggled(int habitId, bool newState);

private slots:
    void on_btnCheck_clicked();

private:
    Ui::HabitCard *ui;
    int habitId;
    bool completed;
    void updateStyle();
};

#endif