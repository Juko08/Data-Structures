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
// Part 5: Insert a node at the beginning
void LinkedList::insertFront(int value) {
    Node* newNode = new Node{value, head};
    head = newNode;
}

// Part 6: Insert a node at the end
void LinkedList::insertBack(int value) {
    Node* newNode = new Node{value, nullptr};

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;

    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;
}
// Part 7: Search for a value in the list
bool LinkedList::search(int value) const {
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == value) {
            return true;
        }

        temp = temp->next;
    }

    return false;
}
// Part 8: Insert a new node after a target value
bool LinkedList::insertAfter(int target, int value) {
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == target) {
            Node* newNode = new Node{value, temp->next};
            temp->next = newNode;
            return true;
        }

        temp = temp->next;
    }

    return false;
}
// Part 9: Remove the first node containing a value
bool LinkedList::remove(int value) {
    if (head == nullptr) {
        return false;
    }

    // Check if the first node needs to be removed
    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node* current = head;

    // Find the node before the one we want to remove
    while (current->next != nullptr) {
        if (current->next->data == value) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            return true;
        }

        current = current->next;
    }

    return false;
}