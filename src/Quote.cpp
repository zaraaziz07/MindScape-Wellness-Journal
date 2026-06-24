#include "Quote.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

Quote::Quote() {
    id = 0;
    text = "";
    author = "";
    category = "";
    isFavorite = false;
}

Quote::Quote(int id, string text, string author, string category) {
    this->id = id;
    this->text = text;
    this->author = author;
    this->category = category;
    this->isFavorite = false;
}

int Quote::getId() const {
    return id;
}

string Quote::getText() const {
    return text;
}

string Quote::getAuthor() const {
    return author;
}

string Quote::getCategory() const {
    return category;
}

bool Quote::getIsFavorite() const {
    return isFavorite;
}

void Quote::setFavorite(bool value) {
    isFavorite = value;
}

string Quote::toFileString() const {
    stringstream ss;
    ss << id << "|" << text << "|" << author << "|" << category << "|" << (isFavorite ? 1 : 0);
    return ss.str();
}

Quote Quote::fromFileString(string line) {
    vector<string> parts;
    stringstream ss(line);
    string segment;

    while (getline(ss, segment, '|')) {
        parts.push_back(segment);
    }

    Quote q;
    if (parts.size() >= 4) {
        q.id = stoi(parts[0]);
        q.text = parts[1];
        q.author = parts[2];
        q.category = parts[3];
    }
    if (parts.size() >= 5) {
        q.isFavorite = (stoi(parts[4]) == 1);
    }

    return q;
}

void Quote::display() const {
    cout << "------------------------------" << endl;
    cout << "ID: " << id << endl;
    cout << "\"" << text << "\"" << endl;
    cout << "- " << author << " (" << category << ")" << endl;
    cout << "Favorite: " << (isFavorite ? "Yes" : "No") << endl;
    cout << "------------------------------" << endl;
}