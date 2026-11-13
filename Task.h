#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>

using namespace std;

// Simple date struct for due dates
struct Date {
    int month;
    int day;
    int year;

    Date() : month(0), day(0), year(0) {}
    Date(int m, int d, int y) : month(m), day(d), year(y) {}

    // Compare dates for sorting by due date
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator==(const Date& other) const {
        return month == other.month && day == other.day && year == other.year;
    }

    string toString() const {
        return to_string(month) + "/" + to_string(day) + "/" + to_string(year);
    }
};

// Enum for sort type used in TaskCategory
enum SortType { ALPHA, PRIORITY, DATE };

// ============================================================
// Abstract base class: Task
// Demonstrates: Abstract class, Polymorphism, Overloaded operators
// ============================================================
class Task {
protected:
    int id;
    string title;
    string desc;
    Date date;
    bool priority;  // true = important
    bool urgency;   // true = urgent
    bool done;

public:
    Task()
        : id(0), title(""), desc(""), date(), priority(false),
          urgency(false), done(false) {}

    Task(int id, string title, string desc, Date date,
         bool priority, bool urgency)
        : id(id), title(title), desc(desc), date(date),
          priority(priority), urgency(urgency), done(false) {}

    virtual ~Task() {}

    // ---- Pure virtual methods (makes Task abstract) ----
    virtual void display() const = 0;
    virtual int compare(const Task& other) const = 0;
    virtual string getType() const = 0;

    // ---- Getters ----
    int getId() const { return id; }
    string getTitle() const { return title; }
    string getDesc() const { return desc; }
    Date getDate() const { return date; }
    bool getPriority() const { return priority; }
    bool getUrgency() const { return urgency; }
    bool isDone() const { return done; }

    // ---- Setters ----
    void setTitle(const string& t) { title = t; }
    void setDesc(const string& d) { desc = d; }
    void setDate(const Date& d) { date = d; }
    void setPriority(bool p) { priority = p; }
    void setUrgency(bool u) { urgency = u; }

    // ---- markDone (from UML) ----
    void markDone() { done = true; }

    // ---- Determine which Eisenhower quadrant (1-4) ----
    int getQuadrant() const {
        if (priority && urgency)  return 1; // Urgent & Important
        if (priority && !urgency) return 2; // Important, Not Urgent
        if (!priority && urgency) return 3; // Urgent, Not Important
        return 4;                           // Not Urgent, Not Important
    }

    // ============================================================
    // Overloaded Operators (requirement: minimum of 3)
    // ============================================================

    // Operator 1: << for output
    friend ostream& operator<<(ostream& os, const Task& t) {
        os << "[" << t.id << "] " << t.title;
        if (t.done) os << " (DONE)";
        os << "\n     " << t.desc
           << "\n     Due: " << t.date.toString()
           << " | Priority: " << (t.priority ? "Yes" : "No")
           << " | Urgent: " << (t.urgency ? "Yes" : "No");
        return os;
    }

    // Operator 2: == compare by id
    bool operator==(const Task& other) const {
        return id == other.id;
    }

    // Operator 3: < compare by date (used in sorting)
    bool operator<(const Task& other) const {
        return date < other.date;
    }
};

// ============================================================
// Derived class: ImportantTask
// Demonstrates: Inheritance, Polymorphism
// ============================================================
class ImportantTask : public Task {
public:
    ImportantTask()
        : Task() {}

    ImportantTask(int id, string title, string desc, Date date,
                  bool priority, bool urgency)
        : Task(id, title, desc, date, priority, urgency) {}

    // ---- Implement pure virtual methods ----
    void display() const override {
        cout << "=== " << getType() << " ===" << endl;
        cout << *this << endl;
    }

    int compare(const Task& other) const override {
        // Compare by priority first, then urgency, then date
        if (priority != other.getPriority())
            return priority ? -1 : 1;
        if (urgency != other.getUrgency())
            return urgency ? -1 : 1;
        if (date < other.getDate()) return -1;
        if (other.getDate() < date) return 1;
        return 0;
    }

    string getType() const override {
        return "Important Task";
    }
};

#endif
