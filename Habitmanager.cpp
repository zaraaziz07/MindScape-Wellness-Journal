#include "Habitmanager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

HabitManager::HabitManager(string habitsFilePath, string logsFilePath) {
    this->habitsFilePath = habitsFilePath;
    this->logsFilePath = logsFilePath;
    nextHabitId = 1;

    loadHabitsFromFile();
    loadLogsFromFile();

    for (int i = 0; i < (int)habits.size(); i++) {
        if (habits[i].getId() >= nextHabitId) {
            nextHabitId = habits[i].getId() + 1;
        }
    }
}

int HabitManager::addHabit(string name, string icon) {
    Habit newHabit(nextHabitId, name, icon);
    habits.push_back(newHabit);
    int assignedId = nextHabitId;
    nextHabitId++;
    saveHabitsToFile();
    return assignedId;
}

bool HabitManager::removeHabit(int habitId) {
    Habit* h = getHabitById(habitId);
    if (h == nullptr) return false;
    h->setActive(false); 
    saveHabitsToFile();
    return true;
}

bool HabitManager::renameHabit(int habitId, string newName, string newIcon) {
    Habit* h = getHabitById(habitId);
    if (h == nullptr) return false;
    h->setName(newName);
    h->setIcon(newIcon);
    saveHabitsToFile();
    return true;
}

Habit* HabitManager::getHabitById(int habitId) {
    for (int i = 0; i < (int)habits.size(); i++) {
        if (habits[i].getId() == habitId) {
            return &habits[i];
        }
    }
    return nullptr;
}

vector<Habit> HabitManager::getAllActiveHabits() const {
    vector<Habit> result;
    for (int i = 0; i < (int)habits.size(); i++) {
        if (habits[i].getIsActive()) {
            result.push_back(habits[i]);
        }
    }
    return result;
}


bool HabitManager::toggleHabitForDate(int habitId, string date) {
    for (int i = 0; i < (int)logs.size(); i++) {
        if (logs[i].getHabitId() == habitId && logs[i].getDate() == date) {
            logs[i].setCompleted(!logs[i].getCompleted());
            saveLogsToFile();
            return true;
        }
    }

    
    HabitLog newLog(habitId, date, true);
    logs.push_back(newLog);
    saveLogsToFile();
    return true;
}

bool HabitManager::isHabitCompletedOnDate(int habitId, string date) const {
    for (int i = 0; i < (int)logs.size(); i++) {
        if (logs[i].getHabitId() == habitId && logs[i].getDate() == date) {
            return logs[i].getCompleted();
        }
    }
    return false; 
}

vector<HabitLog> HabitManager::getLogsForDate(string date) const {
    vector<HabitLog> result;
    for (int i = 0; i < (int)logs.size(); i++) {
        if (logs[i].getDate() == date) {
            result.push_back(logs[i]);
        }
    }
    return result;
}


int HabitManager::getCompletedCountForDate(string date) const {
    int count = 0;
    vector<Habit> active = getAllActiveHabits();
    for (int i = 0; i < (int)active.size(); i++) {
        if (isHabitCompletedOnDate(active[i].getId(), date)) {
            count++;
        }
    }
    return count;
}

int HabitManager::getTotalActiveHabitCount() const {
    return (int)getAllActiveHabits().size();
}



int HabitManager::dateToNumber(string date) const {
    string yearPart = date.substr(0, 4);
    string monthPart = date.substr(5, 2);
    string dayPart = date.substr(8, 2);
    return stoi(yearPart) * 10000 + stoi(monthPart) * 100 + stoi(dayPart);
}

bool HabitManager::isOneDayApart(string laterDate, string earlierDate) const {
    int laterYear = stoi(laterDate.substr(0, 4));
    int laterMonth = stoi(laterDate.substr(5, 2));
    int laterDay = stoi(laterDate.substr(8, 2));

    int earlierYear = stoi(earlierDate.substr(0, 4));
    int earlierMonth = stoi(earlierDate.substr(5, 2));
    int earlierDay = stoi(earlierDate.substr(8, 2));

    if (laterYear == earlierYear && laterMonth == earlierMonth) {
        return (laterDay - earlierDay) == 1;
    }

    if (laterDay == 1) {
        int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int earlierMonthIndex = earlierMonth - 1;
        int lastDayOfEarlierMonth = daysInMonth[earlierMonthIndex];

        if (earlierMonth == 2) {
            bool isLeap = (earlierYear % 4 == 0 && earlierYear % 100 != 0) || (earlierYear % 400 == 0);
            if (isLeap) lastDayOfEarlierMonth = 29;
        }

        if (earlierDay == lastDayOfEarlierMonth) {
            if (laterYear == earlierYear && laterMonth == earlierMonth + 1) return true;
            if (laterYear == earlierYear + 1 && earlierMonth == 12 && laterMonth == 1) return true;
        }
    }

    return false;
}


int HabitManager::getHabitStreak(int habitId, string todayDate) const {
   
    vector<string> completedDates;
    for (int i = 0; i < (int)logs.size(); i++) {
        if (logs[i].getHabitId() == habitId && logs[i].getCompleted()) {
            completedDates.push_back(logs[i].getDate());
        }
    }

    if (completedDates.empty()) return 0;

    sort(completedDates.begin(), completedDates.end(), [this](const string& a, const string& b) {
        return dateToNumber(a) > dateToNumber(b);
        });

    if (completedDates[0] != todayDate) return 0; 

    int streak = 1;
    for (int i = 0; i < (int)completedDates.size() - 1; i++) {
        if (isOneDayApart(completedDates[i], completedDates[i + 1])) {
            streak++;
        }
        else {
            break;
        }
    }
    return streak;
}



bool HabitManager::saveHabitsToFile() const {
    ofstream file(habitsFilePath);
    if (!file.is_open()) {
        cout << "Error: could not open file for saving: " << habitsFilePath << endl;
        return false;
    }
    for (int i = 0; i < (int)habits.size(); i++) {
        file << habits[i].toFileString() << endl;
    }
    file.close();
    return true;
}

bool HabitManager::loadHabitsFromFile() {
    ifstream file(habitsFilePath);
    if (!file.is_open()) {
        return false;
    }

    habits.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        habits.push_back(Habit::fromFileString(line));
    }
    file.close();
    return true;
}

bool HabitManager::saveLogsToFile() const {
    ofstream file(logsFilePath);
    if (!file.is_open()) {
        cout << "Error: could not open file for saving: " << logsFilePath << endl;
        return false;
    }
    for (int i = 0; i < (int)logs.size(); i++) {
        file << logs[i].toFileString() << endl;
    }
    file.close();
    return true;
}

bool HabitManager::loadLogsFromFile() {
    ifstream file(logsFilePath);
    if (!file.is_open()) {
        return false;
    }

    logs.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        logs.push_back(HabitLog::fromFileString(line));
    }
    file.close();
    return true;
}



void HabitManager::displayAllHabits() const {
    cout << "===== All Habits (" << habits.size() << ") =====" << endl;
    for (int i = 0; i < (int)habits.size(); i++) {
        habits[i].display();
    }
}

void HabitManager::displayLogsForDate(string date) const {
    cout << "===== Logs for " << date << " =====" << endl;
    vector<HabitLog> dayLogs = getLogsForDate(date);
    for (int i = 0; i < (int)dayLogs.size(); i++) {
        dayLogs[i].display();
    }
}