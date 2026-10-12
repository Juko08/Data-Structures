#include <iostream>
using namespace std;

// Part 3: Node structure
struct Node {
    int data;
    Node* next;
};

// Part 3: LinkedList class
class LinkedList {
private:
    Node* head;

public:
    LinkedList();

    bool empty() const;
    void display() const;
    bool search(int value) const;

    void insertFront(int value);
    void insertBack(int value);
    bool insertAfter(int target, int value);

    bool remove(int value);

    ~LinkedList();
};

// Part 4: Constructor
LinkedList::LinkedList() {
    head = nullptr;
}

// Part 4: Check if the list is empty
bool LinkedList::empty() const {
    return head == nullptr;
}