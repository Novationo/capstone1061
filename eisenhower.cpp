// code for eisenhower matrix to display tasks in different quadrants
// important and urgent (1), important but not urgent (2), not important but
// urgent (3), and not important and not urgent (4)

#include "EisenhowerMatrix.h"
#include <iomanip>

EisenhowerMatrix::EisenhowerMatrix() {}

// Add task to the correct quadrant
void EisenhowerMatrix::addTask(ImportantTask *task) {
  int q = task->getQuadrant();
  switch (q) {
  case 1:
    quad1.pushBack(task);
    break;
  case 2:
    quad2.pushBack(task);
    break;
  case 3:
    quad3.pushBack(task);
    break;
  case 4:
    quad4.pushBack(task);
    break;
  }
}

// Remove task
bool EisenhowerMatrix::removeTask(int taskId) {
  // Search all 4 quadrants
  for (int qNum = 1; qNum <= 4; qNum++) {
    LinkedList<ImportantTask *> &list = getQuad(qNum);
    for (int i = 0; i < list.getSize(); i++) {
      if (list.get(i)->getId() == taskId) {
        list.removeAt(i);
        return true;
      }
    }
  }
  return false;
}

// find specific quadrant
LinkedList<ImportantTask *> &EisenhowerMatrix::getQuad(int quadNum) {
  switch (quadNum) {
  case 1:
    return quad1;
  case 2:
    return quad2;
  case 3:
    return quad3;
  default:
    return quad4;
  }
}

// display full matrix
void EisenhowerMatrix::displayMatrix() const {
  string line(60, '-');

  cout << "\n"
       << string(25, '=') << " EISENHOWER MATRIX " << string(25, '=') << endl;
  cout << endl;

  // Urgent & Important
  cout << "  URGENT & IMPORTANT (Do First)" << endl;
  cout << "  " << line << endl;
  if (quad1.getSize() == 0) {
    cout << "    (empty)" << endl;
  } else {
    for (int i = 0; i < quad1.getSize(); i++) {
      cout << "    " << (i + 1) << ". " << *(quad1.get(i)) << endl;
    }
  }
  cout << endl;

  // Important, Not Urgent
  cout << "  IMPORTANT, NOT URGENT (Schedule)" << endl;
  cout << "  " << line << endl;
  if (quad2.getSize() == 0) {
    cout << "    (empty)" << endl;
  } else {
    for (int i = 0; i < quad2.getSize(); i++) {
      cout << "    " << (i + 1) << ". " << *(quad2.get(i)) << endl;
    }
  }
  cout << endl;

  // Urgent, Not Important
  cout << "  URGENT, NOT IMPORTANT (Delegate)" << endl;
  cout << "  " << line << endl;
  if (quad3.getSize() == 0) {
    cout << "    (empty)" << endl;
  } else {
    for (int i = 0; i < quad3.getSize(); i++) {
      cout << "    " << (i + 1) << ". " << *(quad3.get(i)) << endl;
    }
  }
  cout << endl;

  // Not Urgent, Not Important
  cout << "  NOT URGENT, NOT IMPORTANT (Eliminate)" << endl;
  cout << "  " << line << endl;
  if (quad4.getSize() == 0) {
    cout << "    (empty)" << endl;
  } else {
    for (int i = 0; i < quad4.getSize(); i++) {
      cout << "    " << (i + 1) << ". " << *(quad4.get(i)) << endl;
    }
  }

  cout << "\n" << string(69, '=') << endl;
}

// create one list
LinkedList<ImportantTask *> EisenhowerMatrix::getAllTasks() const {
  LinkedList<ImportantTask *> all;
  for (int i = 0; i < quad1.getSize(); i++)
    all.pushBack(quad1.get(i));
  for (int i = 0; i < quad2.getSize(); i++)
    all.pushBack(quad2.get(i));
  for (int i = 0; i < quad3.getSize(); i++)
    all.pushBack(quad3.get(i));
  for (int i = 0; i < quad4.getSize(); i++)
    all.pushBack(quad4.get(i));
  return all;
}

// Clear all quadrants
void EisenhowerMatrix::clearAll() {
  quad1.clear();
  quad2.clear();
  quad3.clear();
  quad4.clear();
}

// re-add tasks from a list
void EisenhowerMatrix::rebuild(LinkedList<ImportantTask *> &allTasks) {
  clearAll();
  for (int i = 0; i < allTasks.getSize(); i++) {
    addTask(allTasks.get(i));
  }
}