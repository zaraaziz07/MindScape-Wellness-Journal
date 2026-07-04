#pragma once
#ifndef QUOTEMANAGER_H
#define QUOTEMANAGER_H

#include <string>
#include <vector>
#include "Quote.h"
using namespace std;

class QuoteManager {
private:
    vector<Quote> quotes;
    string quotesFilePath;
    string favoritesFilePath;
    int nextId;

public:
    QuoteManager(string quotesFilePath = "data/quotes.txt", string favoritesFilePath = "data/favorites.txt");

    int addQuote(string text, string author, string category);
    Quote getRandomQuote() const;
    Quote getRandomQuoteByCategory(string category) const;
    Quote* getQuoteById(int id);

    bool markFavorite(int id);
    bool unmarkFavorite(int id);
    vector<Quote> getFavorites() const;

    vector<Quote> getAllQuotes() const;
    vector<Quote> getQuotesByCategory(string category) const;
    int getTotalQuotes() const;

    bool loadQuotesFromFile();
    bool saveFavoritesToFile() const;
    bool loadFavoritesFromFile();

    void displayAll() const;
};

#endif