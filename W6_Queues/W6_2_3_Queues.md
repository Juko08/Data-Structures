# W6>2/3 Queues

## Part 1 — Trace Queue Operations

Starting with an empty queue:

| Operation | Value Returned | Logical Queue (front → rear) | Front | Size |
|---|---:|---|---:|---:|
| `enqueue(10)` | — | `10` | 10 | 1 |
| `enqueue(20)` | — | `10, 20` | 10 | 2 |
| `enqueue(30)` | — | `10, 20, 30` | 10 | 3 |
| `dequeue()` | 10 | `20, 30` | 20 | 2 |
| `enqueue(40)` | — | `20, 30, 40` | 20 | 3 |
| `enqueue(50)` | — | `20, 30, 40, 50` | 20 | 4 |
| `dequeue()` | 20 | `30, 40, 50` | 30 | 3 |
| `enqueue(60)` | — | `30, 40, 50, 60` | 30 | 4 |

Final front: `30`  
Final size: `4`  
Removal order: `30, 40, 50, 60`

This demonstrates FIFO because the values are removed in the same order in which they entered the queue.

## Part 2 — Why Not Shift the Array?

If a queue contains `N` elements, a shifting implementation may move approximately `N - 1` elements during one dequeue. Therefore, one dequeue is `O(N)`.

If all `N` elements are removed this way, the work can be approximately:

`(N-1) + (N-2) + ... + 1 = O(N²)`

Advancing `frontIndex` avoids moving the remaining elements. Only one index changes, so dequeue can be `O(1)`.

## Part 3 — Circular Queue

The complete implementation is in `queue.cpp`. It does not use `std::queue`.

The queue maintains:

- `frontIndex` — location of the next element to remove.
- `rearIndex` — location where the next element is inserted.
- `count` — number of elements currently stored.

## Part 4 — Queue State and Invariants

The empty queue starts with:

```text
frontIndex = 0
rearIndex = 0
count = 0
```

`count == 0` means the queue contains no elements.

`count == CAPACITY` means the queue is full.

`frontIndex == rearIndex` can represent either an empty or full queue because the indices wrap around independently. `count` removes this ambiguity by explicitly storing the number of elements.

## Part 5 — enqueue()

The implementation stores the value at `rearIndex`, advances the index using modulo, and increases `count`:

```cpp
data[rearIndex] = value;
rearIndex = (rearIndex + 1) % CAPACITY;
++count;
```

If the queue is full, it throws:

```text
Queue overflow
```

Simply doing `++rearIndex` is not sufficient because eventually `rearIndex` would become `CAPACITY`, which is outside the array. Modulo sends it back to index `0`.

## Part 6 — dequeue()

The implementation saves the value at `frontIndex`, advances `frontIndex` with modulo, decreases `count`, and returns the value.

If the queue is empty, it throws:

```text
Queue underflow
```

Advancing `frontIndex` is preferable to shifting because no other stored elements need to be moved.

## Part 7 — front()

`front()` returns the oldest element without removing it.

`dequeue()` returns the oldest element and removes it.

Both access the front directly, but only `dequeue()` changes the queue state.

## Part 8 — Circular Wraparound

For a capacity-5 circular queue, consider:

| Operation | frontIndex | rearIndex | count | Logical Queue |
|---|---:|---:|---:|---|
| Initial | 0 | 0 | 0 | empty |
| `enqueue(10)` | 0 | 1 | 1 | 10 |
| `enqueue(20)` | 0 | 2 | 2 | 10 → 20 |
| `enqueue(30)` | 0 | 3 | 3 | 10 → 20 → 30 |
| `dequeue()` | 1 | 3 | 2 | 20 → 30 |
| `enqueue(40)` | 1 | 4 | 3 | 20 → 30 → 40 |
| `enqueue(50)` | 1 | 0 | 4 | 20 → 30 → 40 → 50 |
| `dequeue()` | 2 | 0 | 3 | 30 → 40 → 50 |
| `enqueue(60)` | 2 | 1 | 4 | 30 → 40 → 50 → 60 |

Wraparound occurs when `rearIndex` advances from physical index `4` to index `0`.

The next position after the final array index is index `0` because:

```text
(4 + 1) % 5 = 0
```

Physical array order can differ from logical queue order because the queue can continue inserting at the beginning of the array after reaching the end. The logical order is determined by `frontIndex` and the circular progression, not by simply reading the array from index 0.

## Part 9 — Logical Position vs. Physical Position

Given:

```text
CAPACITY = 8
frontIndex = 6
count = 4
```

Use:

```text
(frontIndex + i) % CAPACITY
```

| Logical Position | Calculation | Physical Index |
|---:|---|---:|
| 0 | `(6 + 0) % 8` | 6 |
| 1 | `(6 + 1) % 8` | 7 |
| 2 | `(6 + 2) % 8` | 0 |
| 3 | `(6 + 3) % 8` | 1 |

This allows the logical queue to cross the physical end of the array without moving existing elements.

## Part 10 — Complete Circular Queue Test

`queue.cpp` demonstrates:

- Initially empty queue
- Multiple enqueue operations
- FIFO removal
- `front()`
- `size()`
- Multiple dequeue operations
- Circular wraparound
- Reuse of vacated positions
- Underflow
- Overflow

### Expected Test Results

```text
Queue initially empty: true

Enqueue 10, 20, 30, 40, 50...
Front: 10, Size: 5

FIFO removal order:
dequeue() -> 10
dequeue() -> 20
Front: 30, Size: 3

Testing circular wraparound:
Queue size after reusing positions: 8
...
Queue empty: true

Testing underflow:
Caught exception: Queue underflow

Testing overflow:
Queue full: true
Caught exception: Queue overflow

Demonstrating wraparound with a sequence:
dequeue() -> 10
Logical FIFO order after wraparound: 20 -> 30 -> 40 -> 50 -> 60
```

## Part 11 — Complexity Analysis

| Operation | Big-O | Explanation |
|---|---|---|
| `enqueue()` | O(1) | Stores one value, advances `rearIndex`, and increments `count`. |
| `dequeue()` | O(1) | Reads one value, advances `frontIndex`, and decrements `count`. |
| `front()` | O(1) | Directly accesses `data[frontIndex]`. |
| `empty()` | O(1) | Checks whether `count == 0`. |
| `full()` | O(1) | Checks whether `count == CAPACITY`. |
| `size()` | O(1) | Returns the stored `count`. |

The amount of stored data does not change the amount of work for these operations because the implementation does not scan or shift the queue.

### Circular vs. Shifting Queue

Implementation A, which shifts elements during every dequeue, takes `O(N)` for one dequeue because up to `N-1` elements may be moved.

Removing all `N` elements can therefore take `O(N²)` total time.

Implementation B advances `frontIndex` using modulo. One dequeue takes `O(1)`, so removing all `N` elements takes `O(N)` total time.

## Part 12 — FIFO Correctness

Given:

```text
enqueue(5)
enqueue(10)
enqueue(15)
enqueue(20)
```

The four dequeue operations return:

```text
5
10
15
20
```

In general:

```text
enqueue(x1), enqueue(x2), ..., enqueue(xN)
```

must be followed by:

```text
x1, x2, ..., xN
```

This is a correctness test because a queue is defined by FIFO behavior. If the values are not returned in arrival order, the implementation is not correctly implementing a queue.

## Part 13 — Queue Applications

### Scenario A — Print Server

**FIFO:** Yes  
**Queue appropriate:** Yes.

Print jobs should normally be processed in the order they arrive.

### Scenario B — Server Requests

**FIFO:** Yes  
**Queue appropriate:** Yes.

Requests waiting for a worker are generally handled in arrival order.

### Scenario C — Undo

**LIFO:** Yes  
**Queue appropriate:** No.

Undo should remove the most recent operation first, so a stack is appropriate.

### Scenario D — Breadth-First Search

**FIFO:** Yes  
**Queue appropriate:** Yes.

Vertices discovered earlier should be processed before later-discovered vertices. A queue causes BFS to explore the graph level by level.

### Scenario E — Function Calls

**LIFO:** Yes  
**Queue appropriate:** No.

The most recently called unfinished function must complete before the calling function resumes, which is LIFO behavior.

## Part 14 — Queue and Breadth-First Search

For the graph:

```text
      A
     / \
    B   C
   / \   \
  D   E   F
```

Starting at `A` and processing neighbors left to right, the BFS visit order is:

```text
A → B → C → D → E → F
```

### Queue Trace

| Step | Vertex Processed | Vertices Added | Queue After Step |
|---|---|---|---|
| Start | — | A | A |
| 1 | A | B, C | B → C |
| 2 | B | D, E | C → D → E |
| 3 | C | F | D → E → F |
| 4 | D | — | E → F |
| 5 | E | — | F |
| 6 | F | — | empty |

FIFO behavior causes BFS to finish processing vertices at the current level before moving to the next level.

### BFS Complexity

With an adjacency-list graph, BFS has time complexity:

```text
O(V + E)
```

Each vertex is visited at most once, giving `O(V)`. Each adjacency-list edge is examined as the algorithm processes the vertices, giving `O(E)`. Together this gives `O(V + E)`.

The queue's worst-case auxiliary space is `O(V)` because, in the worst case, it may contain a number of vertices proportional to the total number of vertices.

# Analysis and Reflection

A queue is an Abstract Data Type because it defines FIFO behavior and queue operations without requiring one specific physical representation. It can be implemented using different underlying structures while preserving the same interface and behavior.

FIFO means the first item inserted is the first item removed. LIFO, used by stacks, means the last item inserted is the first item removed.

Circular indexing is preferable to shifting because advancing an index requires constant work while shifting can require moving many elements. `frontIndex` identifies the next item to remove, `rearIndex` identifies where the next item will be inserted, and `count` records how many elements are currently stored.

Modular arithmetic is necessary for wraparound because it sends an index back to zero after it reaches the last valid physical array position.

`frontIndex == rearIndex` can be ambiguous because both an empty and a full circular queue can eventually have the same index relationship. Maintaining `count` solves this by explicitly distinguishing `0` elements from `CAPACITY` elements.

Properly implemented `enqueue()` and `dequeue()` are `O(1)` because they only update a constant number of variables and array positions.

Queues are appropriate for systems that process work in arrival order because FIFO preserves that arrival order. The same FIFO behavior makes queues useful for BFS, where earlier-discovered vertices must be processed before later-discovered vertices.
