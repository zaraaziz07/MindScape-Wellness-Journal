#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QDir>
#include <QDate>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QDesktopServices>
#include <QUrl>
#include <QGridLayout>
#include "stickerpicker.h"
#include "draggablesticker.h"
#include "bookcard.h"
#include "habitcard.h"
#include <vector>

using namespace std;

const int BOOK_COUNT = 9;
const QString BOOK_TITLES[BOOK_COUNT] = {
    "The Alchemist",
    "Man's Search for Meaning",
    "Don't Be Sad",
    "Atomic Habits",
    "The Power of Now",
    "The Art of Happiness",
    "Ikigai",
    "Inner Engineering",
    "You Can Heal Your Life"
};
const QString BOOK_AUTHORS[BOOK_COUNT] = {
    "Paulo Coelho",
    "Viktor Frankl",
    "Dr. Aaidh al-Qarni",
    "James Clear",
    "Eckhart Tolle",
    "Dalai Lama",
    "Hector Garcia & Francesc Miralles",
    "Sadhguru",
    "Louise Hay"
};
const QString BOOK_FILES[BOOK_COUNT] = {
    "the_alchemist.pdf",
    "mans_search_for_meaning.pdf",
    "dont_be_sad.pdf",
    "atomic_habits.pdf",
    "the_power_of_now.pdf",
    "the_art_of_happiness.pdf",
    "ikigai.pdf",
    "inner_engineering.pdf",
    "you_can_heal_your_life.pdf"
};
const QString BOOK_COVERS[BOOK_COUNT] = {
    "the_alchemist.jpg",
    "mans_search.jpg",
    "dont_be_sad.jpg",
    "atomic_habits.jpg",
    "power_of_now.jpg",
    "art_of_happiness.jpg",
    "ikigai.jpg",
    "inner_engineering.jpg",
    "you_can_heal.jpg"
};
const int BOOK_PAGES[BOOK_COUNT] = {
    136, 69, 476, 256, 216, 180, 123, 170, 272
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , selectedMoodRating(0)
    , currentQuoteId(0)
    , habitListLoading(false),selectedBookIndex(-1)
    , booksGridLayout(nullptr)
{
    ui->setupUi(this);

       ui->stackedWidget->setCurrentIndex(3);
    if (app.getHabitManager().getTotalActiveHabitCount() == 0) {
        app.getHabitManager().addHabit("Drink Water", "💧");
        app.getHabitManager().addHabit("Sleep 7+ hours", "🌙");
        app.getHabitManager().addHabit("Walk or Exercise", "🏃");
        app.getHabitManager().addHabit("Read", "📖");
        app.getHabitManager().addHabit("Evening Dhikr", "🌿");
    }
    updateStreakDisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnJournal_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btnMood_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_btnQuote_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    on_btnNewQuote_clicked();
}

void MainWindow::on_btnHabits_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
   loadHabitsAsCards();
}

void MainWindow::on_btnHistory_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    loadHistoryList();
}

void MainWindow::on_btnBooks_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    loadBooksGrid();
}
void MainWindow::on_btnBackFromQuote_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_btnBackFromMood_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_btnBackFromBooks_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_btnBackFromJournal_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    //updateStreakDisplay();
}

void MainWindow::on_btnBackFromHistory_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_btnBackFromHabits_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_btnSave_clicked()
{
    QString title = ui->lineEditTitle->text();
    QString contentHtml = ui->textEditContent->toHtml();
    QString plainCheck = ui->textEditContent->toPlainText().trimmed();

    if (title.trimmed().isEmpty() && plainCheck.isEmpty()) {
        return;
    }

    QString todayQt = QDate::currentDate().toString("yyyy-MM-dd");
    std::string date = todayQt.toStdString();
    int moodRating = 5;

    int newId = app.getEntryManager().addEntry(date, title.toStdString(), contentHtml.toStdString(), moodRating);

    JournalEntry* savedEntry = app.getEntryManager().getEntryById(newId);
    if (savedEntry != nullptr) {
        if (ui->btnTagGrateful->isChecked()) savedEntry->addTag("grateful");
        if (ui->btnTagStudy->isChecked()) savedEntry->addTag("study");
        if (ui->btnTagPeaceful->isChecked()) savedEntry->addTag("peaceful");
        if (ui->btnTagFamily->isChecked()) savedEntry->addTag("family");
        if (ui->btnTagHealth->isChecked()) savedEntry->addTag("health");

        app.getEntryManager().saveToFile();
    }

    ui->lineEditTitle->clear();
    ui->textEditContent->clear();
    ui->btnTagGrateful->setChecked(false);
    ui->btnTagStudy->setChecked(false);
    ui->btnTagPeaceful->setChecked(false);
    ui->btnTagFamily->setChecked(false);
    ui->btnTagHealth->setChecked(false);
}
void MainWindow::on_btnAddSticker_clicked()
{
    StickerPicker picker(this);
    if (picker.exec() == QDialog::Accepted) {
        QString stickerId = picker.getSelectedSticker();
        QString emoji = "";

        if (stickerId == "sun") emoji = "🌞";
        else if (stickerId == "rainbow") emoji = "🌈";
        else if (stickerId == "moon") emoji = "🌙";
        else if (stickerId == "flower") emoji = "🌸";
        else if (stickerId == "coffee") emoji = "☕";
        else if (stickerId == "leaf") emoji = "🍃";
        else if (stickerId == "sparkle") emoji = "✨";
        else if (stickerId == "butterfly") emoji = "🦋";

        DraggableSticker *sticker = new DraggableSticker(emoji, ui->pageJournal);
        sticker->move(40, 40);
        sticker->show();
        sticker->raise();
    }
}


void MainWindow::on_btnMoodLow_clicked()
{
    ui->btnMoodLow->setChecked(true);
    ui->btnMoodMeh->setChecked(false);
    ui->btnMoodGood->setChecked(false);
    ui->btnMoodGreat->setChecked(false);
    ui->btnMoodAmazing->setChecked(false);
    selectedMoodRating = 1;
}

void MainWindow::on_btnMoodMeh_clicked()
{
    ui->btnMoodLow->setChecked(false);
    ui->btnMoodMeh->setChecked(true);
    ui->btnMoodGood->setChecked(false);
    ui->btnMoodGreat->setChecked(false);
    ui->btnMoodAmazing->setChecked(false);
    selectedMoodRating = 2;
}

void MainWindow::on_btnMoodGood_clicked()
{
    ui->btnMoodLow->setChecked(false);
    ui->btnMoodMeh->setChecked(false);
    ui->btnMoodGood->setChecked(true);
    ui->btnMoodGreat->setChecked(false);
    ui->btnMoodAmazing->setChecked(false);
    selectedMoodRating = 3;
}

void MainWindow::on_btnMoodGreat_clicked()
{
    ui->btnMoodLow->setChecked(false);
    ui->btnMoodMeh->setChecked(false);
    ui->btnMoodGood->setChecked(false);
    ui->btnMoodGreat->setChecked(true);
    ui->btnMoodAmazing->setChecked(false);
    selectedMoodRating = 4;
}

void MainWindow::on_btnMoodAmazing_clicked()
{
    ui->btnMoodLow->setChecked(false);
    ui->btnMoodMeh->setChecked(false);
    ui->btnMoodGood->setChecked(false);
    ui->btnMoodGreat->setChecked(false);
    ui->btnMoodAmazing->setChecked(true);
    selectedMoodRating = 5;
}

void MainWindow::on_btnSaveMood_clicked()
{
    if (selectedMoodRating == 0) {
        ui->labelMoodStatus->setText("Please pick a mood first");
        return;
    }

    QString todayQt = QDate::currentDate().toString("yyyy-MM-dd");
    std::string date = todayQt.toStdString();
    std::string note = ui->lineEditMoodNote->text().toStdString();

    app.getMoodManager().logMood(date, selectedMoodRating, note);

    ui->labelMoodStatus->setText("Mood saved for today!");
    ui->lineEditMoodNote->clear();
}

void MainWindow::on_btnNewQuote_clicked()
{
    Quote q = app.getQuoteManager().getRandomQuote();

    ui->labelQuoteText->setText(QString::fromStdString(q.getText()));
    ui->labelQuoteAuthor->setText(QString::fromStdString("- " + q.getAuthor()));

    currentQuoteId = q.getId();
    ui->btnFavouriteQuote->setChecked(q.getIsFavorite());
}

void MainWindow::on_btnFavouriteQuote_clicked()
{
    if (currentQuoteId == 0) {
        return;
    }

    if (ui->btnFavouriteQuote->isChecked()) {
        app.getQuoteManager().markFavorite(currentQuoteId);
    } else {
        app.getQuoteManager().unmarkFavorite(currentQuoteId);
    }
}

void MainWindow::loadHabitsAsCards()
{
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setSpacing(10);
    layout->setContentsMargins(16, 16, 16, 16);

    QString todayQt = QDate::currentDate().toString("yyyy-MM-dd");
    std::string today = todayQt.toStdString();

    vector<Habit> habits = app.getHabitManager().getAllActiveHabits();
    for (int i = 0; i < (int)habits.size(); i++) {
        bool done = app.getHabitManager().isHabitCompletedOnDate(habits[i].getId(), today);
        int streak = app.getHabitManager().getHabitStreak(
            habits[i].getId(), todayQt.toStdString()
            );

        QString emoji = QString::fromStdString(habits[i].getIcon());
        if (emoji.isEmpty()) emoji = "✨";

        HabitCard *card = new HabitCard(
            habits[i].getId(),
            QString::fromStdString(habits[i].getName()),
            emoji, done, streak, container
            );

        connect(card, &HabitCard::toggled, this, [this](int habitId, bool newState) {
            QString todayQt = QDate::currentDate().toString("yyyy-MM-dd");
            std::string today = todayQt.toStdString();
            bool currentlyDone = app.getHabitManager().isHabitCompletedOnDate(habitId, today);
            if (currentlyDone != newState) {
                app.getHabitManager().toggleHabitForDate(habitId, today);
            }
            updateHabitProgress();
        });

        layout->addWidget(card);
    }

    layout->addStretch();
    ui->scrollAreaHabits->setWidget(container);
    ui->scrollAreaHabits->setWidgetResizable(true);
    updateHabitProgress();
}

void MainWindow::updateHabitProgress()
{
    QString todayQt = QDate::currentDate().toString("yyyy-MM-dd");
    std::string today = todayQt.toStdString();
    int completed = app.getHabitManager().getCompletedCountForDate(today);
    int total = app.getHabitManager().getTotalActiveHabitCount();
    ui->labelHabitProgress->setText(
        QString::number(completed) + "/" + QString::number(total) + " completed today"
        );
}

void MainWindow::on_btnAddHabitlist_clicked()
{
    QString habitName = ui->lineEditNewHabit->text().trimmed();
    if (habitName.isEmpty()) return;

    app.getHabitManager().addHabit(habitName.toStdString(), "✨");
    ui->lineEditNewHabit->clear();
    loadHabitsAsCards();
}


void MainWindow::loadHistoryList()
{
    ui->listWidgetHistory->clear();

    vector<JournalEntry> entries = app.getEntryManager().getAllEntries();

    // show most recent first
    for (int i = (int)entries.size() - 1; i >= 0; i--) {
        QString date = QString::fromStdString(entries[i].getDate());
        QString title = QString::fromStdString(entries[i].getTitle());
        QString display = date + "  —  " + (title.isEmpty() ? "(no title)" : title);

        QListWidgetItem *item = new QListWidgetItem(display);
        item->setData(Qt::UserRole, entries[i].getId());
        ui->listWidgetHistory->addItem(item);
    }
}

void MainWindow::on_listWidgetHistory_itemClicked(QListWidgetItem *item)
{
    int entryId = item->data(Qt::UserRole).toInt();
    JournalEntry* entry = app.getEntryManager().getEntryById(entryId);

    if (entry != nullptr) {
        QString preview = QString::fromStdString(entry->getPlainTextPreview(200));
        QString tags = "";
        vector<string> t = entry->getTags();
        for (int i = 0; i < (int)t.size(); i++) {
            tags += "#" + QString::fromStdString(t[i]) + " ";
        }
       // ui->labelEntryPreview->setText(preview + (tags.isEmpty() ? "" : "\n\nTags: " + tags));
    }
}

void MainWindow::loadBooksGrid()
{

    QWidget *container = ui->scrollAreaBooks->widget();
    if (!container) {
        container = new QWidget();
        ui->scrollAreaBooks->setWidget(container);
    }

    QLayout *old = container->layout();
    if (old) {
        QLayoutItem *layoutItem;
        while ((layoutItem = old->takeAt(0)) != nullptr) {
            delete layoutItem->widget();
            delete layoutItem;
        }
        delete old;
    }

    booksGridLayout = new QGridLayout(container);
    booksGridLayout->setSpacing(16);
    booksGridLayout->setContentsMargins(16, 16, 16, 16);

    QString basePath = QDir::currentPath() + "/data/books/";

    for (int i = 0; i < BOOK_COUNT; i++) {
        int savedPage = loadBookProgress(i);
        QString coverPath = basePath + "covers/" + BOOK_COVERS[i];
        QString pdfPath = basePath + BOOK_FILES[i];

        BookCard *card = new BookCard(i, BOOK_TITLES[i], BOOK_AUTHORS[i],
                                      coverPath, pdfPath,
                                      BOOK_PAGES[i], savedPage, container);

        connect(card, &BookCard::progressUpdated,
                this, [this](int bookIndex, int newPage) {
                    saveBookProgress(bookIndex, newPage);
                });

        int row = i / 3;
        int col = i % 3;
        booksGridLayout->addWidget(card, row, col);
    }

    container->setLayout(booksGridLayout);
    ui->scrollAreaBooks->setWidgetResizable(true);
}

int MainWindow::loadBookProgress(int bookIndex)
{
    int currentPage = 0;
    QFile file(QDir::currentPath() + "/data/book_progress.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");
            if (parts.size() == 2 && parts[0].toInt() == bookIndex) {
                currentPage = parts[1].toInt();
                break;
            }
        }
        file.close();
    }
    return currentPage;
}

void MainWindow::saveBookProgress(int bookIndex, int currentPage)
{
    QMap<int, int> progressMap;
    QFile file(QDir::currentPath() + "/data/book_progress.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");
            if (parts.size() == 2) {
                progressMap[parts[0].toInt()] = parts[1].toInt();
            }
        }
        file.close();
    }

    progressMap[bookIndex] = currentPage;

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (auto it = progressMap.begin(); it != progressMap.end(); ++it) {
            out << it.key() << "|" << it.value() << "\n";
        }
        file.close();
    }
}

void MainWindow::updateStreakDisplay()
{

    int streak = app.getEntryManager().getCurrentStreak();
    ui->labelStreakNumber->setText(QString::number(streak) + " day streak");


    QLabel* dayLabels[7] = {
        ui->labelDayMon, ui->labelDayTue, ui->labelDayWed,
        ui->labelDayThu, ui->labelDayFri, ui->labelDaySat, ui->labelDaySun
    };

    // icon labels
    QLabel* iconLabels[7] = {
        ui->labelIconMon, ui->labelIconTue, ui->labelIconWed,
        ui->labelIconThu, ui->labelIconFri, ui->labelIconSat, ui->labelIconSun
    };

    // figure out which day of week today is (Qt: Mon=1, Sun=7)
    int todayDow = QDate::currentDate().dayOfWeek();

    for (int i = 0; i < 7; i++) {
        // i=0 is Monday, i=6 is Sunday
        int daysAgo = todayDow - 1 - i; // how many days ago was this column

        dayLabels[i]->setAlignment(Qt::AlignCenter);
        iconLabels[i]->setAlignment(Qt::AlignCenter);
        iconLabels[i]->setStyleSheet("background: transparent;");

        if (daysAgo < 0) {
            // future day this week — show empty star
            iconLabels[i]->setText("☆");
            iconLabels[i]->setStyleSheet("color: #D0B0BB; font-size: 16px; background: transparent;");
        } else if (daysAgo == 0) {
            // today — show filled star in pink
            iconLabels[i]->setText("⭐");
            iconLabels[i]->setStyleSheet("font-size: 16px; background: transparent;");
        } else {
            // past day — check if we had an entry that day
            QDate pastDate = QDate::currentDate().addDays(-daysAgo);
            std::string dateStr = pastDate.toString("yyyy-MM-dd").toStdString();
            bool hadEntry = !app.getEntryManager().getEntriesByDate(dateStr).empty();

            if (hadEntry) {
                iconLabels[i]->setText("❤️");
                iconLabels[i]->setStyleSheet("font-size: 16px; background: transparent;");
            } else {
                iconLabels[i]->setText("☆");
                iconLabels[i]->setStyleSheet("color: #D0B0BB; font-size: 16px; background: transparent;");
            }
        }
    }
}



