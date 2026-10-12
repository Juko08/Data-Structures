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
// Part 10: Display all nodes in the list
void LinkedList::display() const {
    Node* temp = head;

    if (temp == nullptr) {
        cout << "List is empty" << endl;
        return;
    }

    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }

    cout << "nullptr" << endl;
}
// Part 11: Delete all remaining nodes
LinkedList::~LinkedList() {
    Node* temp = head;

    while (temp != nullptr) {
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    head = nullptr;
}
// Part 10: Required operation tests
int main() {
    cout << boolalpha;
    LinkedList list;
    cout << "Initially empty: " << list.empty() << endl;
    list.display();

    list.insertFront(10);
    cout << "After insertFront(10): "; list.display();
    list.insertFront(20);
    cout << "After insertFront(20): "; list.display();
    list.insertFront(30);
    cout << "After insertFront(30): "; list.display();

    list.insertBack(40);
    cout << "After insertBack(40): "; list.display();
    list.insertBack(50);
    cout << "After insertBack(50): "; list.display();

    cout << "Search head (30): " << list.search(30) << endl;
    cout << "Search middle (20): " << list.search(20) << endl;
    cout << "Search tail (50): " << list.search(50) << endl;
    cout << "Search missing (99): " << list.search(99) << endl;

    cout << "Insert 25 after 20: " << list.insertAfter(20, 25) << endl;
    list.display();
    cout << "Insert after missing 99: " << list.insertAfter(99, 100) << endl;
    list.display();

    cout << "Remove head (30): " << list.remove(30) << endl;
    list.display();
    cout << "Remove middle (25): " << list.remove(25) << endl;
    list.display();
    cout << "Remove tail (50): " << list.remove(50) << endl;
    list.display();
    cout << "Remove missing (99): " << list.remove(99) << endl;
    list.display();

    LinkedList emptyList;
    cout << "Remove from empty list: " << emptyList.remove(5) << endl;
    emptyList.insertBack(7);
    cout << "InsertBack into empty list: "; emptyList.display();
    cout << "Final main list: "; list.display();
    return 0;