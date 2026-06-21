#include "MoodEntry.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

MoodEntry::MoodEntry() {
    id = 0;
    date = "";
    moodRating = 3;
    note = "";
}

MoodEntry::MoodEntry(int id, string date, int moodRating, string note) {
    this->id = id;
    this->date = date;
    this->moodRating = moodRating;
    this->note = note;
}

int MoodEntry::getId() const {
    return id;
}

string MoodEntry::getDate() const {
    return date;
}

int MoodEntry::getMoodRating() const {
    return moodRating;
}

string MoodEntry::getNote() const {
    return note;
}

string MoodEntry::getMoodLabel() const {
    if (moodRating == 1) return "Low";
    if (moodRating == 2) return "Meh";
    if (moodRating == 3) return "Good";
    if (moodRating == 4) return "Great";
    if (moodRating == 5) return "Amazing";
    return "Unknown";
}

string MoodEntry::getMoodEmoji() const {
    if (moodRating == 1) return "😔";
    if (moodRating == 2) return "😕";
    if (moodRating == 3) return "😊";
    if (moodRating == 4) return "😄";
    if (moodRating == 5) return "🤩";
    return "❓";
}

void MoodEntry::setMoodRating(int newMood) {
    if (newMood < 1) newMood = 1;
    if (newMood > 5) newMood = 5;
    moodRating = newMood;
}

void MoodEntry::setNote(string newNote) {
    note = newNote;
}

string MoodEntry::toFileString() const {
    stringstream ss;
    ss << id << "|" << date << "|" << moodRating << "|" << note;
    return ss.str();
}

MoodEntry MoodEntry::fromFileString(string line) {
    vector<string> parts;
    stringstream ss(line);
    string segment;

    while (getline(ss, segment, '|')) {
        parts.push_back(segment);
    }

    MoodEntry entry;
    if (parts.size() >= 3) {
        entry.id = stoi(parts[0]);
        entry.date = parts[1];
        entry.moodRating = stoi(parts[2]);
    }

    if (parts.size() >= 4) {
        entry.note = parts[3];
    }

    return entry;
}

bool MoodEntry::operator<(const MoodEntry& other) const {
    return date < other.date;
}

bool MoodEntry::operator==(const MoodEntry& other) const {
    return id == other.id;
}

void MoodEntry::display() const {
    cout << "------------------------------" << endl;
    cout << "ID: " << id << endl;
    cout << "Date: " << date << endl;
    cout << "Mood: " << getMoodEmoji() << " " << getMoodLabel() << " (" << moodRating << "/5)" << endl;

    if (!note.empty()) {
        cout << "Note: " << note << endl;
    }

    cout << "------------------------------" << endl;
}