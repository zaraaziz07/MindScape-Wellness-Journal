#include "historycard.h"
#include "ui_historycard.h"

HistoryCard::HistoryCard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HistoryCard)
{
    ui->setupUi(this);
}

HistoryCard::~HistoryCard()
{
    delete ui;
}
