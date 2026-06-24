#ifndef QUOTE_H
#define QUOTE_H

#include <string>
using namespace std;

class Quote {
private:
    int id;
    string text;
    string author;
    string category;
    bool isFavorite;

public:
    Quote();
    Quote(int id, string text, string author, string category);

    int getId() const;
    string getText() const;
    string getAuthor() const;
    string getCategory() const;
    bool getIsFavorite() const;

    void setFavorite(bool value);

    string toFileString() const;
    static Quote fromFileString(string line);

    void display() const;
};

#endif
