#include "Habit.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

Habit::Habit() {
    id = 0;
    name = "";
    icon = "";
    isActive = true;
}

Habit::Habit(int id, string name, string icon) {
    this->id = id;
    this->name = name;
    this->icon = icon;
    this->isActive = true;
}

int Habit::getId() const {
    return id;
}

string Habit::getName() const {
    return name;
}

string Habit::getIcon() const {
    return icon;
}

bool Habit::getIsActive() const {
    return isActive;
}

void Habit::setName(string newName) {
    name = newName;
}

void Habit::setIcon(string newIcon) {
    icon = newIcon;
}

void Habit::setActive(bool value) {
    isActive = value;
}

string Habit::toFileString() const {
    stringstream ss;
    ss << id << "|" << name << "|" << icon << "|" << (isActive ? 1 : 0);
    return ss.str();
}

Habit Habit::fromFileString(string line) {
    vector<string> parts;
    stringstream ss(line);
    string segment;

    while (getline(ss, segment, '|')) {
        parts.push_back(segment);
    }

    Habit h;
    if (parts.size() >= 3) {
        h.id = stoi(parts[0]);
        h.name = parts[1];
        h.icon = parts[2];
    }
    if (parts.size() >= 4) {
        h.isActive = (stoi(parts[3]) == 1);
    }

    return h;
}

bool Habit::operator==(const Habit& other) const {
    return id == other.id;
}

void Habit::display() const {
    cout << "------------------------------" << endl;
    cout << "ID: " << id << endl;
    cout << "Name: " << icon << " " << name << endl;
    cout << "Active: " << (isActive ? "Yes" : "No") << endl;
    cout << "------------------------------" << endl;
}