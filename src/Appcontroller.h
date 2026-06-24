#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "EntryManager.h"
#include "MoodManager.h"
#include "QuoteManager.h"
#include "HabitManager.h"
#include <string>
using namespace std;

class AppController {
private:
    EntryManager entryManager;
    MoodManager moodManager;
    QuoteManager quoteManager;
    HabitManager habitManager;

public:
    AppController();

    EntryManager& getEntryManager();
    MoodManager& getMoodManager();
    QuoteManager& getQuoteManager();
    HabitManager& getHabitManager();

  
    string getTodaySummary(string todayDate);
};

#endif
