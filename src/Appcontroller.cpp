#include "Appcontroller.h"
#include <sstream>
using namespace std;

AppController::AppController()
    : entryManager(), moodManager(), quoteManager(), habitManager() {
}

EntryManager& AppController::getEntryManager() {
    return entryManager;
}

MoodManager& AppController::getMoodManager() {
    return moodManager;
}

QuoteManager& AppController::getQuoteManager() {
    return quoteManager;
}

HabitManager& AppController::getHabitManager() {
    return habitManager;
}


string AppController::getTodaySummary(string todayDate) {
    stringstream ss;

    ss << "Journal streak: " << entryManager.getCurrentStreak() << " day(s)\n";

    if (moodManager.hasMoodForDate(todayDate)) {
        ss << "Today's mood: " << moodManager.getMoodByDate(todayDate)->getMoodLabel() << "\n";
    }
    else {
        ss << "Today's mood: not logged yet\n";
    }

    ss << "Habits completed today: " << habitManager.getCompletedCountForDate(todayDate)
        << "/" << habitManager.getTotalActiveHabitCount() << "\n";

    ss << "Total journal entries: " << entryManager.getTotalEntries();

    return ss.str();
}