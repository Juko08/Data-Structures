#include <iostream>
#include <stdexcept>
using namespace std;

class Queue {
private:
    static const int CAPACITY = 10;
    int data[CAPACITY];
    int frontIndex;
    int rearIndex;
    int count;

public:
    Queue();
    bool empty() const;
    bool full() const;
    int size() const;
    void enqueue(int value);
    int dequeue();
    int front() const;
};

Queue::Queue() : frontIndex(0), rearIndex(0), count(0) {}

bool Queue::empty() const {
    return count == 0;
}

bool Queue::full() const {
    return count == CAPACITY;
}

int Queue::size() const {
    return count;
}

void Queue::enqueue(int value) {
    if (full()) {
        throw overflow_error("Queue overflow");
    }

    data[rearIndex] = value;
    rearIndex = (rearIndex + 1) % CAPACITY;
    ++count;
}

int Queue::dequeue() {
    if (empty()) {
        throw underflow_error("Queue underflow");
    }

    int value = data[frontIndex];
    frontIndex = (frontIndex + 1) % CAPACITY;
    --count;
    return value;
}

int Queue::front() const {
    if (empty()) {
        throw underflow_error("Queue underflow");
    }

    return data[frontIndex];
}

void printState(const Queue& q) {
    cout << "Front: " << q.front() << ", Size: " << q.size() << endl;
}

int main() {
    cout << boolalpha;

    Queue q;
    cout << "Queue initially empty: " << q.empty() << endl;

    cout << "\nEnqueue 10, 20, 30, 40, 50..." << endl;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);
    printState(q);

    cout << "\nFIFO removal order:" << endl;
    cout << "dequeue() -> " << q.dequeue() << endl;
    cout << "dequeue() -> " << q.dequeue() << endl;
    printState(q);

    cout << "\nTesting circular wraparound:" << endl;
    q.enqueue(60);
    q.enqueue(70);
    q.enqueue(80);
    q.enqueue(90);
    q.enqueue(100);
    cout << "Queue size after reusing positions: " << q.size() << endl;

    cout << "Removing values:" << endl;
    while (!q.empty()) {
        cout << "dequeue() -> " << q.dequeue() << endl;
    }

    cout << "Queue empty: " << q.empty() << endl;

    cout << "\nTesting underflow:" << endl;
    try {
        q.dequeue();
    } catch (const underflow_error& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    cout << "\nTesting overflow:" << endl;
    for (int i = 1; i <= 10; ++i) {
        q.enqueue(i * 10);
    }
    cout << "Queue full: " << q.full() << endl;

    try {
        q.enqueue(110);
    } catch (const overflow_error& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    cout << "\nDemonstrating wraparound with a sequence:" << endl;
    Queue wrap;
    wrap.enqueue(10);
    wrap.enqueue(20);
    wrap.enqueue(30);
    cout << "dequeue() -> " << wrap.dequeue() << endl;
    wrap.enqueue(40);
    wrap.enqueue(50);
    wrap.enqueue(60);
    cout << "Logical FIFO order after wraparound: ";
    while (!wrap.empty()) {
        cout << wrap.dequeue();
        if (!wrap.empty()) cout << " -> ";
    }
    cout << endl;

    return 0;
}
