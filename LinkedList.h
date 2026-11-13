#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>

using namespace std;

// ============================================================
// Node template for doubly linked list
// ============================================================
template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

// ============================================================
// Class Template: LinkedList (doubly linked list)
// Demonstrates: Class template, Data structure (List)
// Pointer-based implementation as noted in tasklist.cpp comments
// ============================================================
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    // Add to the back of the list
    void pushBack(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    // Add to the front of the list
    void pushFront(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    // Remove node at a given index (0-based)
    bool removeAt(int index) {
        if (index < 0 || index >= size) return false;

        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        if (current->prev != nullptr)
            current->prev->next = current->next;
        else
            head = current->next;

        if (current->next != nullptr)
            current->next->prev = current->prev;
        else
            tail = current->prev;

        delete current;
        size--;
        return true;
    }

    // Get element at index (0-based)
    T& get(int index) {
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Const version
    const T& get(int index) const {
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    int getSize() const { return size; }

    bool isEmpty() const { return size == 0; }

    Node<T>* getHead() const { return head; }
    Node<T>* getTail() const { return tail; }

    // Clear all nodes
    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    // ============================================================
    // Swap two nodes' data (helper for sorting)
    // ============================================================
    void swapData(Node<T>* a, Node<T>* b) {
        T temp = a->data;
        a->data = b->data;
        b->data = temp;
    }
};

#endif
