#include "bookcard.h"
#include "ui_bookcard.h"
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QInputDialog>
#include <QFile>
#include <QDir>
#include <QDebug>

BookCard::BookCard(int bookIndex, QString title, QString author,
                   QString coverPath, QString pdfPath,
                   int totalPages, int currentPage,
                   QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookCard)
    , bookIndex(bookIndex)
    , totalPages(totalPages)
    , pdfPath(pdfPath)
{
    ui->setupUi(this);

    QPixmap cover(coverPath);
    if (!cover.isNull()) {
        ui->labelCover->setPixmap(cover.scaled(120, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        ui->labelCover->setText("📚");
        ui->labelCover->setAlignment(Qt::AlignCenter);
        ui->labelCover->setStyleSheet("font-size: 48px;");
    }

    ui->labelTitle->setText(title);
    ui->labelAuthor->setText(author);
    updateProgress(currentPage);

    setStyleSheet("QWidget { background: white; border-radius: 10px; border: 1px solid #E5D9BC; }");
    setFixedSize(170, 325);
}

BookCard::~BookCard()
{
    delete ui;
}

void BookCard::updateProgress(int currentPage)
{
    int percent = (totalPages > 0) ? (currentPage * 100 / totalPages) : 0;
    ui->progressBar->setValue(percent);
    ui->labelPages->setText("Page " + QString::number(currentPage) +
                            " of " + QString::number(totalPages));
}

int BookCard::getBookIndex() const
{
    return bookIndex;
}

void BookCard::on_btnOpen_clicked()
{
    bool ok;
    int currentPage = ui->progressBar->value() * totalPages / 100;
    int page = QInputDialog::getInt(this, "Update Progress",
                                    "Which page are you on?",
                                    currentPage, 0, totalPages, 1, &ok);
    if (ok) {
        updateProgress(page);
        emit progressUpdated(bookIndex, page);
    }

    qDebug() << "PDF path:" << pdfPath;
    qDebug() << "File exists:" << QFile::exists(pdfPath);
    qDebug() << "Current dir:" << QDir::currentPath();

    QDesktopServices::openUrl(QUrl::fromLocalFile(pdfPath));
}