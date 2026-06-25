#include "Habitlog.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

HabitLog::HabitLog() {
    habitId = 0;
    date = "";
    completed = false;
}

HabitLog::HabitLog(int habitId, string date, bool completed) {
    this->habitId = habitId;
    this->date = date;
    this->completed = completed;
}

int HabitLog::getHabitId() const {
    return habitId;
}

string HabitLog::getDate() const {
    return date;
}

bool HabitLog::getCompleted() const {
    return completed;
}

void HabitLog::setCompleted(bool value) {
    completed = value;
}

string HabitLog::toFileString() const {
    stringstream ss;
    ss << habitId << "|" << date << "|" << (completed ? 1 : 0);
    return ss.str();
}

HabitLog HabitLog::fromFileString(string line) {
    vector<string> parts;
    stringstream ss(line);
    string segment;

    while (getline(ss, segment, '|')) {
        parts.push_back(segment);
    }

    HabitLog log;
    if (parts.size() >= 3) {
        log.habitId = stoi(parts[0]);
        log.date = parts[1];
        log.completed = (stoi(parts[2]) == 1);
    }

    return log;
}

void HabitLog::display() const {
    cout << "Habit ID " << habitId << " on " << date << ": "
        << (completed ? "Done" : "Not done") << endl;
}