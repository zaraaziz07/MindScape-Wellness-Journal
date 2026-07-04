#ifndef ENTRYMANAGER_H
#define ENTRYMANAGER_H

#include <string>
#include <vector>
#include "Journalentry.h"
using namespace std;

class EntryManager {
private:
    vector<JournalEntry> entries;
    
    string filePath;
    int nextId;          

public:
    
    EntryManager(string filePath = "data/entries.txt");

   
    int addEntry(string date, string title, string contentHtml, int moodRating);
    bool deleteEntry(int id);
    bool updateEntry(int id, string newTitle, string newContentHtml, int newMood);
    JournalEntry* getEntryById(int id); 

    
    vector<JournalEntry> getAllEntries() const;
    vector<JournalEntry> getEntriesByDate(string date) const;
    vector<JournalEntry> getEntriesByTag(string tag) const;
    vector<JournalEntry> searchByKeyword(string keyword) const; 

   
    void sortByDateAscending();
    void sortByDateDescending();
    void sortByMood();

    int getTotalEntries() const;
    int getCurrentStreak() const; 
    double getAverageMood() const;

private:
    
    int dateToNumber(string date) const;
    bool isOneDayApart(string laterDate, string earlierDate) const;

public:

    
    bool saveToFile() const;
    bool loadFromFile();

    
    void displayAll() const;
};

#endif