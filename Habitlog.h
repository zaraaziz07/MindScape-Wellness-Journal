#ifndef HABITLOG_H
#define HABITLOG_H

#include <string>
using namespace std;

class HabitLog {
private:
    int habitId;
    string date;
    bool completed;

public:
    HabitLog();
    HabitLog(int habitId, string date, bool completed);

    int getHabitId() const;
    string getDate() const;
    bool getCompleted() const;

    void setCompleted(bool value);

    string toFileString() const;
    static HabitLog fromFileString(string line);

    void display() const;
};

#endif
