#include <iostream>
#include <stdexcept>
using namespace std;

class Stack {
private:
    static const int CAPACITY = 10;
    int data[CAPACITY];
    int topIndex;

public:
    Stack();
    bool empty() const;
    bool full() const;
    int size() const;
    void push(int value);
    int pop();
    int top() const;
};

Stack::Stack() : topIndex(-1) {}

bool Stack::empty() const {
    return topIndex == -1;
}

bool Stack::full() const {
    return topIndex == CAPACITY - 1;
}

int Stack::size() const {
    return topIndex + 1;
}

void Stack::push(int value) {
    if (full()) {
        throw overflow_error("Stack overflow");
    }

    data[++topIndex] = value;
}

int Stack::pop() {
    if (empty()) {
        throw underflow_error("Stack underflow");
    }

    int value = data[topIndex];
    --topIndex;
    return value;
}

int Stack::top() const {
    if (empty()) {
        throw underflow_error("Stack underflow");
    }

    return data[topIndex];
}

int main() {
    Stack s;

    cout << boolalpha;
    cout << "Stack initially empty: " << s.empty() << endl;

    cout << "\nPushing 10, 20, 30, 40, 50..." << endl;
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);

    cout << "Size: " << s.size() << endl;
    cout << "Top: " << s.top() << endl;

    cout << "\nPopping two values:" << endl;
    cout << "pop() -> " << s.pop() << endl;
    cout << "pop() -> " << s.pop() << endl;

    cout << "New top: " << s.top() << endl;
    cout << "New size: " << s.size() << endl;

    cout << "\nRemoving remaining values:" << endl;
    while (!s.empty()) {
        cout << "pop() -> " << s.pop() << endl;
    }

    cout << "Stack empty: " << s.empty() << endl;

    cout << "\nTesting underflow:" << endl;
    try {
        s.pop();
    } catch (const underflow_error& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    cout << "\nFilling stack to capacity:" << endl;
    int value = 10;
    while (!s.full()) {
        s.push(value);
        cout << "push(" << value << "), size = " << s.size() << endl;
        value += 10;
    }

    cout << "Stack full: " << s.full() << endl;
    cout << "Top: " << s.top() << endl;

    cout << "\nTesting overflow:" << endl;
    try {
        s.push(110);
    } catch (const overflow_error& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    return 0;
}
