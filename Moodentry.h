#ifndef MOODENTRY_H
#define MOODENTRY_H

#include <string>
using namespace std;

class MoodEntry {
private:
    int id;
    string date;
    int moodRating;
    string note;

public:
    MoodEntry();
    MoodEntry(int id, string date, int moodRating, string note);

    int getId() const;
    string getDate() const;
    int getMoodRating() const;
    string getNote() const;
    string getMoodLabel() const;
    string getMoodEmoji() const;

    void setMoodRating(int newMood);
    void setNote(string newNote);

    string toFileString() const;
    static MoodEntry fromFileString(string line);

    bool operator<(const MoodEntry& other) const;
    bool operator==(const MoodEntry& other) const;

    void display() const;
};

#endif