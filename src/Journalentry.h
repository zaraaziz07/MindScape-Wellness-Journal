#ifndef JOURNALENTRY_H
#define JOURNALENTRY_H

#include <string>
#include <vector>
using namespace std;

class JournalEntry {
private:
    int id;                      
    string date;                
    string title;                
    string contentHtml;          
    int moodRating;              
    vector<string> tags;         
    vector<string> stickerPaths; 

public:
   
    JournalEntry();
    JournalEntry(int id, string date, string title, string contentHtml, int moodRating);

   
    int getId() const;
    string getDate() const;
    string getTitle() const;
    string getContentHtml() const;
    int getMoodRating() const;
    vector<string> getTags() const;
    vector<string> getStickerPaths() const;

    
    void setDate(string newDate);
    void setTitle(string newTitle);
    void setContentHtml(string newContentHtml);
    void setMoodRating(int newMood);

   
    void addTag(string tag);
    void removeTag(string tag);
    bool hasTag(string tag) const;

   
    void addSticker(string imagePath);
    void removeSticker(string imagePath);

   
    string getPlainTextPreview(int maxLength = 60) const; 
    string toFileString() const;                         
    static JournalEntry fromFileString(string line);      

  
    bool operator<(const JournalEntry& other) const;  
    bool operator==(const JournalEntry& other) const; 

    void display() const; 
};

#endif
