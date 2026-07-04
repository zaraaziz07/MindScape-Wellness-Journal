#include "habitcard.h"
#include "ui_habitcard.h"

HabitCard::HabitCard(int habitId, QString name, QString emoji,
                     bool completedToday, int streak,
                     QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HabitCard)
    , habitId(habitId)
    , completed(completedToday)
{
    ui->setupUi(this);
    ui->labelEmoji->setText(emoji);
    ui->labelName->setText(name);
    ui->labelStreak->setText(QString::number(streak) + " day streak");
    updateStyle();
    setFixedHeight(70);
}

HabitCard::~HabitCard()
{
    delete ui;
}

int HabitCard::getHabitId() const
{
    return habitId;
}

void HabitCard::setCompleted(bool done)
{
    completed = done;
    updateStyle();
}

void HabitCard::on_btnCheck_clicked()
{
    completed = !completed;
    updateStyle();
    emit toggled(habitId, completed);
}

void HabitCard::updateStyle()
{
    if (completed) {
        ui->btnCheck->setText("✓");
        ui->btnCheck->setStyleSheet(
            "QPushButton {"
            "background-color: #E8649A;"
            "color: white;"
            "border-radius: 15px;"
            "font-size: 14px;"
            "font-weight: bold;"
            "border: none;"
            "}"
            );
        setStyleSheet(
            "HabitCard {"
            "background-color: #FFF0F5;"
            "border: 1.5px solid #F7C5D5;"
            "border-radius: 14px;"
            "}"
            );
    } else {
        ui->btnCheck->setText("");
        ui->btnCheck->setStyleSheet(
            "QPushButton {"
            "background-color: white;"
            "border-radius: 15px;"
            "border: 2px solid #F7C5D5;"
            "}"
            );
        setStyleSheet(
            "HabitCard {"
            "background-color: white;"
            "border: 1.5px solid #F0D0DC;"
            "border-radius: 14px;"
            "}"
            );
    }
}