#ifndef HABITMANAGER_H
#define HABITMANAGER_H

#include <string>
#include <vector>
#include "Habit.h"
#include "HabitLog.h"
using namespace std;

class HabitManager {
private:
    vector<Habit> habits;
    vector<HabitLog> logs;
    string habitsFilePath;
    string logsFilePath;
    int nextHabitId;

public:
    HabitManager(string habitsFilePath = "data/habits.txt", string logsFilePath = "data/habit_logs.txt");

    int addHabit(string name, string icon);
    bool removeHabit(int habitId);
    bool renameHabit(int habitId, string newName, string newIcon);
    Habit* getHabitById(int habitId);
    vector<Habit> getAllActiveHabits() const;

    bool toggleHabitForDate(int habitId, string date);
    bool isHabitCompletedOnDate(int habitId, string date) const;
    vector<HabitLog> getLogsForDate(string date) const;

    int getCompletedCountForDate(string date) const;
    int getTotalActiveHabitCount() const;
    int getHabitStreak(int habitId, string todayDate) const;

    bool saveHabitsToFile() const;
    bool loadHabitsFromFile();
    bool saveLogsToFile() const;
    bool loadLogsFromFile();

    void displayAllHabits() const;
    void displayLogsForDate(string date) const;

private:
    int dateToNumber(string date) const;
    bool isOneDayApart(string laterDate, string earlierDate) const;
};

#endif
