#ifndef BOOKCARD_H
#define BOOKCARD_H

#include <QWidget>

namespace Ui {
class BookCard;
}

class BookCard : public QWidget
{
    Q_OBJECT

public:
    explicit BookCard(int bookIndex, QString title, QString author,
                      QString coverPath, QString pdfPath,
                      int totalPages, int currentPage,
                      QWidget *parent = nullptr);
    ~BookCard();

    void updateProgress(int currentPage);
    int getBookIndex() const;

signals:
    void progressUpdated(int bookIndex, int newPage);

private slots:
    void on_btnOpen_clicked();

private:
    Ui::BookCard *ui;
    int bookIndex;
    int totalPages;
    QString pdfPath;
};

#endif