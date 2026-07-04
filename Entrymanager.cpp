#include "Entrymanager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;



EntryManager::EntryManager(string filePath) {
    this->filePath = filePath;
    nextId = 1;
    loadFromFile(); 

    for (int i = 0; i < (int)entries.size(); i++) {
        if (entries[i].getId() >= nextId) {
            nextId = entries[i].getId() + 1;
        }
    }
}



int EntryManager::addEntry(string date, string title, string contentHtml, int moodRating) {
    JournalEntry newEntry(nextId, date, title, contentHtml, moodRating);
    entries.push_back(newEntry);
    int assignedId = nextId;
    nextId++;
    saveToFile();
    return assignedId; 
}

bool EntryManager::deleteEntry(int id) {
    for (int i = 0; i < (int)entries.size(); i++) {
        if (entries[i].getId() == id) {
            entries.erase(entries.begin() + i);
            saveToFile();
            return true;
        }
    }
    return false;
}

bool EntryManager::updateEntry(int id, string newTitle, string newContentHtml, int newMood) {
    JournalEntry* entry = getEntryById(id);
    if (entry == nullptr) return false;

    entry->setTitle(newTitle);
    entry->setContentHtml(newContentHtml);
    entry->setMoodRating(newMood);
    saveToFile();
    return true;
}

JournalEntry* EntryManager::getEntryById(int id) {
    for (int i = 0; i < (int)entries.size(); i++) {
        if (entries[i].getId() == id) {
            return &entries[i];
        }
    }
    return nullptr;
}



vector<JournalEntry> EntryManager::getAllEntries() const {
    return entries;
}

vector<JournalEntry> EntryManager::getEntriesByDate(string date) const {
    vector<JournalEntry> result;
    for (int i = 0; i < (int)entries.size(); i++) {
        if (entries[i].getDate() == date) {
            result.push_back(entries[i]);
        }
    }
    return result;
}

vector<JournalEntry> EntryManager::getEntriesByTag(string tag) const {
    vector<JournalEntry> result;
    for (int i = 0; i < (int)entries.size(); i++) {
        if (entries[i].hasTag(tag)) {
            result.push_back(entries[i]);
        }
    }
    return result;
}


vector<JournalEntry> EntryManager::searchByKeyword(string keyword) const {
    vector<JournalEntry> result;
    for (int i = 0; i < (int)entries.size(); i++) {
        string title = entries[i].getTitle();
        string preview = entries[i].getPlainTextPreview(1000); 

        if (title.find(keyword) != string::npos || preview.find(keyword) != string::npos) {
            result.push_back(entries[i]);
        }
    }
    return result;
}



void EntryManager::sortByDateAscending() {
    sort(entries.begin(), entries.end());
}

void EntryManager::sortByDateDescending() {
    sort(entries.begin(), entries.end());
    reverse(entries.begin(), entries.end());
}

void EntryManager::sortByMood() {
    sort(entries.begin(), entries.end(), [](const JournalEntry& a, const JournalEntry& b) {
        return a.getMoodRating() < b.getMoodRating();
        });
}


int EntryManager::getTotalEntries() const {
    return (int)entries.size();
}


int EntryManager::dateToNumber(string date) const {
    string yearPart = date.substr(0, 4);
    string monthPart = date.substr(5, 2);
    string dayPart = date.substr(8, 2);
    return stoi(yearPart) * 10000 + stoi(monthPart) * 100 + stoi(dayPart);
}


bool EntryManager::isOneDayApart(string laterDate, string earlierDate) const {
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


int EntryManager::getCurrentStreak() const {
    if (entries.empty()) return 0;

   
    vector<string> uniqueDates;
    for (int i = 0; i < (int)entries.size(); i++) {
        string d = entries[i].getDate();
        bool found = false;
        for (int j = 0; j < (int)uniqueDates.size(); j++) {
            if (uniqueDates[j] == d) { found = true; break; }
        }
        if (!found) uniqueDates.push_back(d);
    }

    
    sort(uniqueDates.begin(), uniqueDates.end(), [this](const string& a, const string& b) {
        return dateToNumber(a) > dateToNumber(b);
        });

    int streak = 1;
    for (int i = 0; i < (int)uniqueDates.size() - 1; i++) {
        if (isOneDayApart(uniqueDates[i], uniqueDates[i + 1])) {
            streak++;
        }
        else {
            break;
        }
    }
    return streak;
}

double EntryManager::getAverageMood() const {
    if (entries.empty()) return 0.0;
    int total = 0;
    for (int i = 0; i < (int)entries.size(); i++) {
        total += entries[i].getMoodRating();
    }
    return (double)total / entries.size();
}



bool EntryManager::saveToFile() const {
    ofstream file(filePath);
    if (!file.is_open()) {
        cout << "Error: could not open file for saving: " << filePath << endl;
        return false;
    }
    for (int i = 0; i < (int)entries.size(); i++) {
        file << entries[i].toFileString() << endl;
    }
    file.close();
    return true;
}

bool EntryManager::loadFromFile() {
    ifstream file(filePath);
    if (!file.is_open()) {
      
        return false;
    }

    entries.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        entries.push_back(JournalEntry::fromFileString(line));
    }
    file.close();
    return true;
}


void EntryManager::displayAll() const {
    cout << "===== All Journal Entries (" << entries.size() << ") =====" << endl;
    for (int i = 0; i < (int)entries.size(); i++) {
        entries[i].display();
    }
}