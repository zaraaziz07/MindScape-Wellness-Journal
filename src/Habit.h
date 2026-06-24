#ifndef HABIT_H
#define HABIT_H

#include <string>
using namespace std;

class Habit {
private:
    int id;
    string name;
    string icon;
    bool isActive;

public:
    Habit();
    Habit(int id, string name, string icon);

    int getId() const;
    string getName() const;
    string getIcon() const;
    bool getIsActive() const;

    void setName(string newName);
    void setIcon(string newIcon);
    void setActive(bool value);

    string toFileString() const;
    static Habit fromFileString(string line);

    bool operator==(const Habit& other) const;

    void display() const;
};

#endif
