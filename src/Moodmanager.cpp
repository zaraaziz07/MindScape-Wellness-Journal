#include "MoodManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

MoodManager::MoodManager(string filePath) {
    this->filePath = filePath;
    nextId = 1;
    loadFromFile();

    for (int i = 0; i < (int)moods.size(); i++) {
        if (moods[i].getId() >= nextId) {
            nextId = moods[i].getId() + 1;
        }
    }
}

int MoodManager::logMood(string date, int moodRating, string note) {
    MoodEntry* existing = getMoodByDate(date);
    if (existing != nullptr) {
        existing->setMoodRating(moodRating);
        existing->setNote(note);
        saveToFile();
        return existing->getId();
    }

    MoodEntry newMood(nextId, date, moodRating, note);
    moods.push_back(newMood);

    int assignedId = nextId;
    nextId++;

    saveToFile();
    return assignedId;
}

bool MoodManager::deleteMoodByDate(string date) {
    for (int i = 0; i < (int)moods.size(); i++) {
        if (moods[i].getDate() == date) {
            moods.erase(moods.begin() + i);
            saveToFile();
            return true;
        }
    }
    return false;
}

MoodEntry* MoodManager::getMoodByDate(string date) {
    for (int i = 0; i < (int)moods.size(); i++) {
        if (moods[i].getDate() == date) {
            return &moods[i];
        }
    }
    return nullptr;
}

bool MoodManager::hasMoodForDate(string date) const {
    for (int i = 0; i < (int)moods.size(); i++) {
        if (moods[i].getDate() == date) {
            return true;
        }
    }
    return false;
}

vector<MoodEntry> MoodManager::getAllMoods() const {
    return moods;
}

int MoodManager::dateToNumber(string date) const {
    string yearPart = date.substr(0, 4);
    string monthPart = date.substr(5, 2);
    string dayPart = date.substr(8, 2);

    return stoi(yearPart) * 10000 +
        stoi(monthPart) * 100 +
        stoi(dayPart);
}

vector<MoodEntry> MoodManager::getMoodsInLastNDays(int n, string todayDate) const {
    int todayNum = dateToNumber(todayDate);
    int cutoffNum = todayNum - n + 1;

    vector<MoodEntry> result;

    for (int i = 0; i < (int)moods.size(); i++) {
        int moodNum = dateToNumber(moods[i].getDate());

        if (moodNum >= cutoffNum && moodNum <= todayNum) {
            result.push_back(moods[i]);
        }
    }

    sort(result.begin(), result.end());

    return result;
}

double MoodManager::getAverageMood() const {
    if (moods.empty()) return 0.0;

    int total = 0;

    for (int i = 0; i < (int)moods.size(); i++) {
        total += moods[i].getMoodRating();
    }

    return (double)total / moods.size();
}

int MoodManager::getMostFrequentMood() const {
    if (moods.empty()) return 0;

    int counts[6] = { 0, 0, 0, 0, 0, 0 };

    for (int i = 0; i < (int)moods.size(); i++) {
        int rating = moods[i].getMoodRating();

        if (rating >= 1 && rating <= 5) {
            counts[rating]++;
        }
    }

    int mostFrequent = 1;

    for (int rating = 2; rating <= 5; rating++) {
        if (counts[rating] > counts[mostFrequent]) {
            mostFrequent = rating;
        }
    }

    return mostFrequent;
}

bool MoodManager::saveToFile() const {
    ofstream file(filePath);

    if (!file.is_open()) {
        cout << "Error: could not open file for saving: "
            << filePath << endl;
        return false;
    }

    for (int i = 0; i < (int)moods.size(); i++) {
        file << moods[i].toFileString() << endl;
    }

    file.close();
    return true;
}

bool MoodManager::loadFromFile() {
    ifstream file(filePath);

    if (!file.is_open()) {
        return false;
    }

    moods.clear();

    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        moods.push_back(
            MoodEntry::fromFileString(line)
        );
    }

    file.close();
    return true;
}

void MoodManager::displayAll() const {
    cout << "===== All Mood Entries ("
        << moods.size()
        << ") =====" << endl;

    for (int i = 0; i < (int)moods.size(); i++) {
        moods[i].display();
    }
}