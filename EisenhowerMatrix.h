#ifndef EISENHOWER_H
#define EISENHOWER_H

#include "LinkedList.h"
#include "Task.h"

using namespace std;

// take form uml diagram
// all 4 quads use linked lists
class EisenhowerMatrix {
private:
  LinkedList<ImportantTask *> quad1; // Urgent & Important
  LinkedList<ImportantTask *> quad2; // Important, Not Urgent
  LinkedList<ImportantTask *> quad3; // Urgent, Not Important
  LinkedList<ImportantTask *> quad4; // Not Urgent, Not Important

public:
  EisenhowerMatrix();

  void addTask(ImportantTask *task);

  bool removeTask(int taskId);

  LinkedList<ImportantTask *> &getQuad(int quadNum);

  // display full matrix
  void displayMatrix() const;

  // all in one list
  LinkedList<ImportantTask *> getAllTasks() const;

  void clearAll();

  void rebuild(LinkedList<ImportantTask *> &allTasks);
};

#endif
