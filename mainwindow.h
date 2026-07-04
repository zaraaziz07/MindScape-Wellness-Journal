#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QListWidgetItem>
#include <QScrollArea>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QDesktopServices>
#include <QUrl>
#include "Appcontroller.h"
#include "bookcard.h"
#include "habitcard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btnJournal_clicked();
    void on_btnMood_clicked();
    void on_btnQuote_clicked();
    void on_btnHabits_clicked();
    void on_btnHistory_clicked();
    void on_btnBooks_clicked();
    void on_btnInsights_clicked();
    void on_btnBackFromJournal_clicked();
    void on_btnBackFromMood_clicked();
    void on_btnBackFromHistory_clicked();
    void on_btnBackFromHabits_clicked();
    void on_btnBackFromQuote_clicked();
    void on_btnBackFromBooks_clicked();
    void on_btnSave_clicked();
    void on_btnAddSticker_clicked();
    void on_btnMoodLow_clicked();
    void on_btnMoodMeh_clicked();
    void on_btnMoodGood_clicked();
    void on_btnMoodGreat_clicked();
    void on_btnMoodAmazing_clicked();
    void on_btnSaveMood_clicked();
    void on_btnNewQuote_clicked();
    void on_btnFavouriteQuote_clicked();
    void on_btnAddHabitlist_clicked();
    void on_listWidgetHistory_itemClicked(QListWidgetItem *item);
    void updateStreakDisplay();

private:
    Ui::MainWindow *ui;
    AppController app;
    int selectedMoodRating;
    int currentQuoteId;
    bool habitListLoading;
    int selectedBookIndex;
    QGridLayout *booksGridLayout;

    void loadHabitsAsCards();
    void updateHabitProgress();
    void loadHistoryList();
    void loadBooksGrid();
    void saveBookProgress(int bookIndex, int currentPage);
    int loadBookProgress(int bookIndex);
};
#endif