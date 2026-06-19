#ifndef JOURNALENTRY_H
#define JOURNALENTRY_H

#include <string>
#include <vector>
using namespace std;

class JournalEntry {
private:
    int id;                      // unique id for this entry (used for file storage / searching)
    string date;                 // format: "2026-06-17"
    string title;                // short title of the entry
    string contentHtml;          // rich text content stored as HTML (Qt's QTextEdit gives/takes HTML directly)
    int moodRating;              // 1 to 10, linked with MoodEntry later
    vector<string> tags;         // e.g. "grateful", "study", "family"
    vector<string> stickerPaths; // file paths of stickers/images placed inside the entry

public:
    // ---------- Constructors ----------
    JournalEntry();
    JournalEntry(int id, string date, string title, string contentHtml, int moodRating);

    // ---------- Getters ----------
    int getId() const;
    string getDate() const;
    string getTitle() const;
    string getContentHtml() const;
    int getMoodRating() const;
    vector<string> getTags() const;
    vector<string> getStickerPaths() const;

    // ---------- Setters ----------
    void setDate(string newDate);
    void setTitle(string newTitle);
    void setContentHtml(string newContentHtml);
    void setMoodRating(int newMood);

    // ---------- Tag management ----------
    void addTag(string tag);
    void removeTag(string tag);
    bool hasTag(string tag) const;

    // ---------- Sticker management ----------
    void addSticker(string imagePath);
    void removeSticker(string imagePath);

    // ---------- Utility ----------
    string getPlainTextPreview(int maxLength = 60) const; // short preview for history list (strips HTML tags)
    string toFileString() const;                          // serialize entry into one line for saving to file
    static JournalEntry fromFileString(string line);      // rebuild a JournalEntry object from a saved line

    // ---------- Operator overloads ----------
    bool operator<(const JournalEntry& other) const;  // lets us sort entries by date
    bool operator==(const JournalEntry& other) const; // compare by id

    void display() const; // quick console print for testing before Qt is connected
};

#endif
