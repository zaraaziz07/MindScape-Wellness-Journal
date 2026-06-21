#include "Journalentry.h"
#include <iostream>
#include <sstream>
using namespace std;



JournalEntry::JournalEntry() {
    id = 0;
    date = "";
    title = "";
    contentHtml = "";
    moodRating = 5; 
}

JournalEntry::JournalEntry(int id, string date, string title, string contentHtml, int moodRating) {
    this->id = id;
    this->date = date;
    this->title = title;
    this->contentHtml = contentHtml;
    this->moodRating = moodRating;
}



int JournalEntry::getId() const {
    return id;
}

string JournalEntry::getDate() const {
    return date;
}

string JournalEntry::getTitle() const {
    return title;
}

string JournalEntry::getContentHtml() const {
    return contentHtml;
}

int JournalEntry::getMoodRating() const {
    return moodRating;
}

vector<string> JournalEntry::getTags() const {
    return tags;
}

vector<string> JournalEntry::getStickerPaths() const {
    return stickerPaths;
}



void JournalEntry::setDate(string newDate) {
    date = newDate;
}

void JournalEntry::setTitle(string newTitle) {
    title = newTitle;
}

void JournalEntry::setContentHtml(string newContentHtml) {
    contentHtml = newContentHtml;
}

void JournalEntry::setMoodRating(int newMood) {
    if (newMood < 1) newMood = 1;
    if (newMood > 10) newMood = 10;
    moodRating = newMood;
}



void JournalEntry::addTag(string tag) {
    if (!hasTag(tag)) {
        tags.push_back(tag);
    }
}

void JournalEntry::removeTag(string tag) {
    for (int i = 0; i < (int)tags.size(); i++) {
        if (tags[i] == tag) {
            tags.erase(tags.begin() + i);
            return;
        }
    }
}

bool JournalEntry::hasTag(string tag) const {
    for (int i = 0; i < (int)tags.size(); i++) {
        if (tags[i] == tag) return true;
    }
    return false;
}



void JournalEntry::addSticker(string imagePath) {
    stickerPaths.push_back(imagePath);
}

void JournalEntry::removeSticker(string imagePath) {
    for (int i = 0; i < (int)stickerPaths.size(); i++) {
        if (stickerPaths[i] == imagePath) {
            stickerPaths.erase(stickerPaths.begin() + i);
            return;
        }
    }
}


string JournalEntry::getPlainTextPreview(int maxLength) const {
    string plain = "";
    bool insideTag = false;

    for (int i = 0; i < (int)contentHtml.size(); i++) {
        char c = contentHtml[i];
        if (c == '<') {
            insideTag = true;
        }
        else if (c == '>') {
            insideTag = false;
        }
        else if (!insideTag) {
            plain += c;
        }
    }

    if ((int)plain.size() > maxLength) {
        plain = plain.substr(0, maxLength) + "...";
    }
    return plain;
}


string JournalEntry::toFileString() const {
    stringstream ss;
    ss << id << "|" << date << "|" << title << "|" << contentHtml << "|" << moodRating << "|";

    for (int i = 0; i < (int)tags.size(); i++) {
        ss << tags[i];
        if (i != (int)tags.size() - 1) ss << "~";
    }
    ss << "|";

    for (int i = 0; i < (int)stickerPaths.size(); i++) {
        ss << stickerPaths[i];
        if (i != (int)stickerPaths.size() - 1) ss << "~";
    }

    return ss.str();
}


JournalEntry JournalEntry::fromFileString(string line) {
    vector<string> parts;
    stringstream ss(line);
    string segment;

    while (getline(ss, segment, '|')) {
        parts.push_back(segment);
    }

    JournalEntry entry;
    if (parts.size() >= 5) {
        entry.id = stoi(parts[0]);
        entry.date = parts[1];
        entry.title = parts[2];
        entry.contentHtml = parts[3];
        entry.moodRating = stoi(parts[4]);
    }

    if (parts.size() >= 6 && parts[5] != "") {
        stringstream tagStream(parts[5]);
        string tag;
        while (getline(tagStream, tag, '~')) {
            entry.tags.push_back(tag);
        }
    }

    if (parts.size() >= 7 && parts[6] != "") {
        stringstream stickerStream(parts[6]);
        string sticker;
        while (getline(stickerStream, sticker, '~')) {
            entry.stickerPaths.push_back(sticker);
        }
    }

    return entry;
}



bool JournalEntry::operator<(const JournalEntry& other) const {
    return date < other.date; 
}

bool JournalEntry::operator==(const JournalEntry& other) const {
    return id == other.id;
}


void JournalEntry::display() const {
    cout << "------------------------------" << endl;
    cout << "ID: " << id << endl;
    cout << "Date: " << date << endl;
    cout << "Title: " << title << endl;
    cout << "Mood: " << moodRating << "/10" << endl;
    cout << "Preview: " << getPlainTextPreview() << endl;

    cout << "Tags: ";
    for (int i = 0; i < (int)tags.size(); i++) {
        cout << "#" << tags[i] << " ";
    }
    cout << endl;

    cout << "Stickers attached: " << stickerPaths.size() << endl;
    cout << "------------------------------" << endl;
}