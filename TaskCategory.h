#ifndef TASKCATEGORY_H
#define TASKCATEGORY_H

#include <string>
#include "Task.h"
#include "LinkedList.h"

using namespace std;

// ============================================================
// TaskCategory (taskCatagories from UML)
// Holds a linked list of tasks for one category (e.g., "School", "Work")
// Supports sorting alphabetically, by priority, or by date
// ============================================================
class TaskCategory {
private:
    string categoryName;
    LinkedList<ImportantTask*> tasks;
    SortType sortOrder;

    // Recursive search helper
    ImportantTask* searchTasksHelper(const string& query, int index);

public:
    TaskCategory();
    TaskCategory(string name);

    string getCategoryName() const;
    void setCategoryName(const string& name);

    void addTask(ImportantTask* task);
    bool removeTask(int index);
    LinkedList<ImportantTask*>& getTasks();

    // Sorting methods (custom insertion sort implementations)
    void sortAlpha();
    void sortPriority();
    void sortDate();

    // Recursive search
    ImportantTask* searchTasks(const string& query);

    // Display
    void displayTasks() const;
};

#endif
