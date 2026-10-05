# W6>1/3 Stacks

## Objective

The objective of this assignment is to implement a stack from scratch in C++ and apply the Last-In, First-Out (LIFO) principle to a practical problem. The assignment requires an array-based stack with `push()`, `pop()`, `top()`, `empty()`, `full()`, and `size()`, followed by a balanced-delimiter application.

---

# Part 1 — Trace Stack Operations

Starting with an empty stack:

| Operation | Value Returned | Stack After Operation (bottom → top) | Top Element | Stack Size |
|---|---:|---|---:|---:|
| `push(10)` | — | `[10]` | 10 | 1 |
| `push(20)` | — | `[10, 20]` | 20 | 2 |
| `push(30)` | — | `[10, 20, 30]` | 30 | 3 |
| `pop()` | 30 | `[10, 20]` | 20 | 2 |
| `push(40)` | — | `[10, 20, 40]` | 40 | 3 |
| `push(50)` | — | `[10, 20, 40, 50]` | 50 | 4 |
| `pop()` | 50 | `[10, 20, 40]` | 40 | 3 |
| `push(60)` | — | `[10, 20, 40, 60]` | 60 | 4 |

### Analysis

**1. What is the final top element?**

The final top element is `60`.

**2. What is the final stack size?**

The final stack size is `4`.

**3. In what order would the remaining elements be removed?**

They would be removed in this order:

`60, 40, 20, 10`

**4. How does the result demonstrate LIFO behavior?**

LIFO means Last-In, First-Out. The most recently pushed value is the first value removed. For example, `60` was the last value pushed, so it is removed first.

---

# Part 2 — Implement an Array-Based Stack

The complete implementation is in `stack.cpp`.

The stack uses a fixed array:

```cpp
static const int CAPACITY = 10;
int data[CAPACITY];
int topIndex;
```

The assignment specifically prohibits using `std::stack` for this part, so the stack operations are implemented directly with the array.

---

# Part 3 — Maintaining `topIndex`

The constructor initializes:

```cpp
topIndex = -1;
```

This represents an empty stack.

The relationship is:

| `topIndex` | Number of Elements |
|---:|---:|
| `-1` | 0 |
| `0` | 1 |
| `1` | 2 |
| `2` | 3 |

Therefore:

```text
size = topIndex + 1
```

### Analysis

**Why should `topIndex` initially be `-1` rather than `0`?**

An empty stack contains zero elements, so there is no valid array index representing its top. Using `-1` clearly indicates that the stack has no elements. When the first value is pushed, `topIndex` increases from `-1` to `0`, which is the first valid array position.

**Why is the stack size `topIndex + 1`?**

Array indexes start at zero. If the top index is `0`, there is one element. If it is `1`, there are two elements. Therefore, the number of elements is always one greater than `topIndex`.

**What value of `topIndex` indicates that the stack is full?**

With a capacity of 10, the last valid array index is `9`. Therefore, `topIndex == 9` means the stack is full.

---

# Part 4 — Implement `push()`

The implementation checks whether the stack is full before writing to the array:

```cpp
void Stack::push(int value) {
    if (full()) {
        throw overflow_error("Stack overflow");
    }

    data[++topIndex] = value;
}
```

The operation first verifies that there is room. It then increases `topIndex` and stores the new value at that position.

### Stack Overflow

Writing beyond:

```cpp
data[CAPACITY - 1]
```

would be incorrect because `CAPACITY - 1` is the final valid array index. For a capacity of 10, valid indexes are `0` through `9`. Writing to index `10` would go outside the array boundary and could cause undefined behavior or corrupt other memory.

---

# Part 5 — Implement `pop()`

The implementation is:

```cpp
int Stack::pop() {
    if (empty()) {
        throw underflow_error("Stack underflow");
    }

    int value = data[topIndex];
    --topIndex;
    return value;
}
```

The current top value is saved first. Then `topIndex` is decreased so that the element is no longer part of the stack.

### Stack Underflow

If the stack is empty, `pop()` throws:

```cpp
throw underflow_error("Stack underflow");
```

Accessing `data[topIndex]` when `topIndex == -1` is invalid because `-1` is not a valid array index. The underflow check prevents the program from attempting this invalid access.

---

# Part 6 — Implement `top()`

The implementation is:

```cpp
int Stack::top() const {
    if (empty()) {
        throw underflow_error("Stack underflow");
    }

    return data[topIndex];
}
```

`top()` returns the value at the top without removing it.

### Difference Between `top()` and `pop()`

`top()` only looks at the top element and leaves the stack unchanged. `pop()` returns the top element and removes it by decreasing `topIndex`.

---

# Part 7 — Test the Complete Stack

The `main()` function in `stack.cpp` demonstrates:

1. Creating an empty stack.
2. Checking `empty()`.
3. Pushing five values.
4. Displaying the size.
5. Displaying the top.
6. Popping two values.
7. Displaying the new top and size.
8. Removing all remaining values.
9. Demonstrating underflow.
10. Filling the stack to capacity.
11. Demonstrating overflow.

### Expected Test Output

```text
Stack initially empty: true

Pushing 10, 20, 30, 40, 50...
Size: 5
Top: 50

Popping two values:
pop() -> 50
pop() -> 40
New top: 30
New size: 3

Removing remaining values:
pop() -> 30
pop() -> 20
pop() -> 10
Stack empty: true

Testing underflow:
Caught exception: Stack underflow

Filling stack to capacity:
push(10), size = 1
push(20), size = 2
push(30), size = 3
push(40), size = 4
push(50), size = 5
push(60), size = 6
push(70), size = 7
push(80), size = 8
push(90), size = 9
push(100), size = 10
Stack full: true
Top: 100

Testing overflow:
Caught exception: Stack overflow
```

---

# Part 8 — Complexity Analysis

| Operation | Big-O Complexity | Explanation |
|---|---|---|
| `push()` | O(1) | It checks `full()`, increments `topIndex`, and stores one value. It does not need to examine the other elements. |
| `pop()` | O(1) | It checks `empty()`, reads the current top element, decreases `topIndex`, and returns the value. |
| `top()` | O(1) | It directly accesses `data[topIndex]`, so only one element is examined. |
| `empty()` | O(1) | It compares `topIndex` with `-1`. |
| `full()` | O(1) | It compares `topIndex` with `CAPACITY - 1`. |
| `size()` | O(1) | It calculates `topIndex + 1`. |

The number of elements currently stored does not change the amount of work required by these operations. Each operation uses the maintained `topIndex` instead of searching through the stack.

### One Million Elements

Even if a stack contained 1,000,000 elements, removing the top element would not require examining the previous 999,999 elements. `pop()` only accesses the element at `data[topIndex]` and then decreases `topIndex`.

Maintaining `topIndex` makes this possible because it always identifies the current top position directly.

---

# Part 9 — Stack Correctness

Given:

```text
push(5)
push(10)
push(15)
push(20)
```

Four consecutive `pop()` operations return:

```text
20
15
10
5
```

In general:

```text
push(x1), push(x2), ..., push(xN)
```

followed by repeated pops should return:

```text
xN, x(N-1), ..., x2, x1
```

This tests correctness because a stack must follow LIFO behavior. If the values are returned in the same order they were inserted, or in some other order, the stack implementation is not correctly following LIFO.

---

# Part 10 — Balanced Delimiters

A stack is useful for delimiter matching because the most recently encountered opening delimiter must be matched first.

For example:

```text
{(a+b)*[c-d]}
```

is balanced because the delimiters are correctly nested.

The expression:

```text
{(a+b]*[c-d)}
```

is not balanced because the closing delimiter types do not match the corresponding opening delimiters.

The pairs are:

```text
( )
[ ]
{ }
```

---

# Part 11 — Implement the Balanced-Delimiter Algorithm

The complete implementation is in `balanced.cpp`.

The algorithm processes the expression from left to right.

- Opening delimiters `(`, `[`, and `{` are pushed.
- Closing delimiters `)`, `]`, and `}` are checked against the current top.
- A closing delimiter with no opening delimiter returns `false`.
- A mismatched delimiter pair returns `false`.
- A correctly matched pair is popped.
- After the complete expression is processed, the expression is balanced only if the stack is empty.

`std::stack<char>` is used here because the assignment specifically allows it for this application.

### Test Results

| Expression | Balanced |
|---|---|
| `{(a+b)*[c-d]}` | `true` |
| `{(a+b]*c}` | `false` |
| `((a+b))` | `true` |
| `((a+b)` | `false` |
| `[a+b]` | `true` |
| `{[()]}` | `true` |
| `{[(])}` | `false` |

### Expected Program Output

```text
Expression: {(a+b)*[c-d]}
Balanced: true

Expression: {(a+b]*c}
Balanced: false

Expression: ((a+b))
Balanced: true

Expression: ((a+b)
Balanced: false

Expression: [a+b]
Balanced: true

Expression: {[()]}
Balanced: true

Expression: {[(])}
Balanced: false
```

---

# Part 12 — Analyze Delimiter Matching

Assume the expression contains `N` characters.

Each character is examined once while the algorithm moves from left to right through the expression.

An opening delimiter is pushed onto the stack at most once. A closing delimiter causes at most one pop because it is matched with the opening delimiter at the top of the stack.

Therefore, the amount of work grows linearly with the number of characters:

```text
Time complexity: O(N)
```

The algorithm may store many opening delimiters in the stack. In the worst case, all `N` characters could be opening delimiters, so the stack could contain `N` elements.

Therefore:

```text
Worst-case space complexity: O(N)
```

---

# Part 13 — Stack Applications

## Scenario A — Undo

**Behavior:** LIFO

**Stack appropriate:** Yes.

The most recent editing operation needs to be undone first. A stack naturally stores operations so the newest operation is removed first.

## Scenario B — Function Calls

**Behavior:** LIFO

**Stack appropriate:** Yes.

A program must return from the most recently called function before returning to the function that called it. This follows LIFO behavior.

## Scenario C — Browser Back Navigation

**Behavior:** LIFO

**Stack appropriate:** Yes.

The most recently visited previous page should be returned to first. A stack can store previous pages and remove the most recent one when Back is selected.

## Scenario D — Depth-First Search

**Behavior:** LIFO

**Stack appropriate:** Yes.

Depth-first search continues down the most recently discovered path before returning to earlier alternatives. A stack provides this LIFO behavior.

## Scenario E — Customer Service Line

**Behavior:** FIFO

**Stack appropriate:** No.

Customers should normally be served in the same order they arrived. This is First-In, First-Out rather than Last-In, First-Out, so a queue is more appropriate.

---

# Analysis and Reflection

## Why is a stack an Abstract Data Type rather than a specific physical data structure?

A stack describes the behavior and operations that are allowed rather than requiring one particular physical implementation. A stack can be implemented using an array, a linked structure, or another underlying representation while still following the same LIFO rules.

## Why is access intentionally restricted to the top?

Restricting access to the top preserves the LIFO behavior. The newest element is the first one available for removal or inspection. Allowing arbitrary access would make the structure behave differently from the intended stack abstraction.

## How does maintaining `topIndex` make stack operations efficient?

`topIndex` directly identifies the current top position. Therefore, `push()`, `pop()`, and `top()` can access the needed location immediately instead of searching through the elements.

## What is the difference between stack overflow and stack underflow?

Stack overflow occurs when an attempt is made to push onto a full fixed-capacity stack. Stack underflow occurs when an attempt is made to remove or access an element from an empty stack.

## Why do array-based stacks have a fixed capacity?

The array has a fixed number of positions allocated when the stack is created. In this assignment, the capacity is 10. A larger or dynamically growing storage method would be required to allow the stack to grow beyond that fixed capacity.

## Why do stacks naturally support undo, recursion, backtracking, and delimiter matching?

All of these applications involve returning to the most recently added item first. That is exactly the LIFO behavior provided by a stack.

## Why is a stack not appropriate when elements must be processed in arrival order?

A stack removes the newest item first. When items must be processed in the same order they arrived, FIFO behavior is required, so a queue is more appropriate.

Overall, the key property connecting these applications is LIFO: the last item added is the first item removed.

---

# Files Included

- `stack.cpp` — complete array-based Stack implementation and tests.
- `balanced.cpp` — balanced-delimiter implementation and test cases.
- `W6_1_3_Stacks.md` — complete written assignment responses, traces, analysis, complexity, and reflection.
