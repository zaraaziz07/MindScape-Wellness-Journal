#include "QuoteManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

QuoteManager::QuoteManager(string quotesFilePath, string favoritesFilePath) {
    this->quotesFilePath = quotesFilePath;
    this->favoritesFilePath = favoritesFilePath;
    nextId = 1;

    srand((unsigned int)time(0));

    loadQuotesFromFile();
    loadFavoritesFromFile();

    for (int i = 0; i < (int)quotes.size(); i++) {
        if (quotes[i].getId() >= nextId) {
            nextId = quotes[i].getId() + 1;
        }
    }
}

int QuoteManager::addQuote(string text, string author, string category) {
    Quote newQuote(nextId, text, author, category);
    quotes.push_back(newQuote);
    int assignedId = nextId;
    nextId++;
    return assignedId;
}

Quote QuoteManager::getRandomQuote() const {
    if (quotes.empty()) {
        return Quote();
    }
    int randomIndex = rand() % quotes.size();
    return quotes[randomIndex];
}

Quote QuoteManager::getRandomQuoteByCategory(string category) const {
    vector<Quote> filtered = getQuotesByCategory(category);
    if (filtered.empty()) {
        return Quote();
    }
    int randomIndex = rand() % filtered.size();
    return filtered[randomIndex];
}

Quote* QuoteManager::getQuoteById(int id) {
    for (int i = 0; i < (int)quotes.size(); i++) {
        if (quotes[i].getId() == id) {
            return &quotes[i];
        }
    }
    return nullptr;
}

bool QuoteManager::markFavorite(int id) {
    Quote* q = getQuoteById(id);
    if (q == nullptr) return false;
    q->setFavorite(true);
    saveFavoritesToFile();
    return true;
}

bool QuoteManager::unmarkFavorite(int id) {
    Quote* q = getQuoteById(id);
    if (q == nullptr) return false;
    q->setFavorite(false);
    saveFavoritesToFile();
    return true;
}

vector<Quote> QuoteManager::getFavorites() const {
    vector<Quote> result;
    for (int i = 0; i < (int)quotes.size(); i++) {
        if (quotes[i].getIsFavorite()) {
            result.push_back(quotes[i]);
        }
    }
    return result;
}

vector<Quote> QuoteManager::getAllQuotes() const {
    return quotes;
}

vector<Quote> QuoteManager::getQuotesByCategory(string category) const {
    vector<Quote> result;
    for (int i = 0; i < (int)quotes.size(); i++) {
        if (quotes[i].getCategory() == category) {
            result.push_back(quotes[i]);
        }
    }
    return result;
}

int QuoteManager::getTotalQuotes() const {
    return (int)quotes.size();
}

bool QuoteManager::loadQuotesFromFile() {
    ifstream file(quotesFilePath);
    if (!file.is_open()) {
        cout << "Warning: could not open quotes file: " << quotesFilePath << endl;
        return false;
    }

    quotes.clear();
    string line;
    int currentId = 1;

    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<string> parts;
        stringstream ss(line);
        string segment;
        while (getline(ss, segment, '|')) {
            parts.push_back(segment);
        }

        if (parts.size() >= 3) {
            Quote q(currentId, parts[0], parts[1], parts[2]);
            quotes.push_back(q);
            currentId++;
        }
    }

    file.close();
    return true;
}

bool QuoteManager::saveFavoritesToFile() const {
    ofstream file(favoritesFilePath);
    if (!file.is_open()) {
        cout << "Error: could not open file for saving: " << favoritesFilePath << endl;
        return false;
    }
    for (int i = 0; i < (int)quotes.size(); i++) {
        if (quotes[i].getIsFavorite()) {
            file << quotes[i].getId() << endl;
        }
    }
    file.close();
    return true;
}

bool QuoteManager::loadFavoritesFromFile() {
    ifstream file(favoritesFilePath);
    if (!file.is_open()) {
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        int favId = stoi(line);
        Quote* q = getQuoteById(favId);
        if (q != nullptr) {
            q->setFavorite(true);
        }
    }

    file.close();
    return true;
}

void QuoteManager::displayAll() const {
    cout << "===== All Quotes (" << quotes.size() << ") =====" << endl;
    for (int i = 0; i < (int)quotes.size(); i++) {
        quotes[i].display();
    }
}