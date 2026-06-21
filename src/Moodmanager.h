#ifndef MOODMANAGER_H
#define MOODMANAGER_H

#include <string>
#include <vector>
#include "MoodEntry.h"
using namespace std;

class MoodManager {
private:
    vector<MoodEntry> moods;
    string filePath;
    int nextId;

public:
    MoodManager(string filePath = "data/moods.txt");

    int logMood(string date, int moodRating, string note);
    bool deleteMoodByDate(string date);
    MoodEntry* getMoodByDate(string date);
    bool hasMoodForDate(string date) const;

    vector<MoodEntry> getAllMoods() const;
    vector<MoodEntry> getMoodsInLastNDays(int n, string todayDate) const;

    double getAverageMood() const;
    int getMostFrequentMood() const;

    bool saveToFile() const;
    bool loadFromFile();

    void displayAll() const;

private:
    int dateToNumber(string date) const;
};

#endif