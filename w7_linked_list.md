## P1

head
 |
 v
[ 7 | next] -> [13 | next] -> [21 | nullptr]
1st            2nd             3rd

1. No, head doesn't not hold 7 itself.
2. Head stores the memory address of the first node
3. first -> next store the adresses of the second
4. third ->  next is nullptr
5. Losing the head and having no other pointer to the nodes means I would lose access to them. That could cause a memory leak.

## P2

For head -> 10  -> 20 ->  30 -> 40 -> nullptr:
|Iteration|' temp->data'| Where 'temp->next' leads|
|---------|-------------|-------------------------|
|1        |10           |Node containing 20
|2        |20           |Node containing 30
|3        |30           |Node containing 40 
|4        |40           |'nullptr

The loops stops because  after visiting 40, temp becomes nullptr, making  the loop condition false. Going through the whole list O(N) since the loop has to visit every node.

## P3

I made my own Node and LinkedList using pointers instead of std::list or std::forward_list. The class contains head, a constructor, empty, display, search, insertFront, insertBack, insertAfter, remove, and a destructor. The separate C++ file includes the full implementation and tests. I also turned off copying because copying the pointers could make two lists try to delete the same nodes.

## P4

The constructor sets head to nullptr. empty() checks whether head == nullptr. This makes sense because an empty list does not have a first node.

## P5


Before: head -> 10 -> 20 -> 30 -> nullptr
After:  head ->  5 -> 10 -> 20 -> 30 -> nullptr

The new node must point to the old first node **before** `head` is updated. If I replace `head` first without keeping the old address, I can lose access to the rest of the list. This is **O(1)** because I only change a couple pointers. I do not have to go through the list.

## P6

When the list is empty, the new node becomes head. Otherwise I start at head, follow next until I find the final node, and attach the new node there. This also works for a one-node list. With just head, this is **O(N)** because I have to go through the list to find the end. Keeping a tail pointer would make insertion at the end **O(1)**.

## P7

I compare each node's data to the requested value. Finding the first value takes **O(1)** (best case). Finding the last value, or confirming a missing value, takes **O(N)** (worst case). My tests cover values at the beginning, middle, end, and absent from the list.

## P8


Before: 10 -> 20 -> 30 -> 40 -> nullptr
After:  10 -> 20 -> 25 -> 30 -> 40 -> nullptr


After finding the target node, I first set the new node's next to the target's original next, then set the target's next to the new node. That preserves the rest of the list. Changing the pointers is **O(1)**, but looking for the target can take **O(N)**. If the target is missing, the function returns false without changing the list.

## P9


Before: 10 -> 20 -> 30 -> 40 -> nullptr
After:  10 -> 20 ------> 40 -> nullptr


Deleting the head needs special handling because head must move to the second node. For other nodes, I find the previous node, connect it to the deleted node's successor, then call delete. I save the node address until the links have been repaired. A **memory leak** occurs when allocated memory becomes unreachable without being freed. Accessing a node after delete is unsafe because that pointer is dangling and the memory is no longer owned by the program. Empty lists and missing values return false.

## P10

I compiled and ran the program. The output below is what I got when I ran the program. It shows the list after the changes. `true` and `false` show whether searches, insertions, and removals succeeded.

```text
Initial list: (empty)
Empty? true
Remove 10 from empty: false
Search 10 in empty: false
Insert after 10 in empty: false
After insertFront(30, 20, 10): 10 -> 20 -> 30 -> nullptr
After insertBack(40, 50): 10 -> 20 -> 30 -> 40 -> 50 -> nullptr
Search beginning (10): true
Search middle (30): true
Search end (50): true
Search missing (99): false
Insert after 20 (25): true
After middle insertion: 10 -> 20 -> 25 -> 30 -> 40 -> 50 -> nullptr
Insert after missing 99: false
After failed insertion: 10 -> 20 -> 25 -> 30 -> 40 -> 50 -> nullptr
Remove first (10): true
After removing first: 20 -> 25 -> 30 -> 40 -> 50 -> nullptr
Remove middle (30): true
After removing middle: 20 -> 25 -> 40 -> 50 -> nullptr
Remove last (50): true
After removing last: 20 -> 25 -> 40 -> nullptr
Remove missing (99): false
Final list: 20 -> 25 -> 40 -> nullptr
```

## P11

Every new allocation must eventually be matched with delete. The destructor walks through the remaining list, saves the current node, moves head to the next node, and deletes the saved node. If a program repeatedly allocates nodes without freeing them, unreachable allocations accumulate and waste memory. This matters with raw pointers because the nodes do not get freed just because the head pointer goes out of scope.

## P12

| Operation | Big-O | Reason |
|---|---|---|
| Access element at position i | O(N) | Follow links from the head up to position i; worst case is near the end. |
| Search | O(N) | May examine every node to find a value or determine it is absent. |
| Insert at beginning | O(1) | Change head and one next link without traversal. |
| Insert at end | O(N) | Walk from head to the final node because there is no tail. |
| Insert after specified value | O(N) | Search for the target; linking the new node itself is O(1). |
| Delete first node | O(1) | Move head and delete the former first node. |
| Delete specified value | O(N) | May have to search through the whole list before reconnecting links. |
| Traverse entire list | O(N) | Visit each of the N nodes exactly once. |

These are mostly worst-case times. Searching can finish in O(1) if the value is at the head.

## P13

| Comparison | Array / vector | Singly linked list |
|---|---|---|
| Access index N/2 | O(1), direct indexing | O(N), follow links |
| Insert at beginning | O(N), shift elements | O(1), update head |
| Remove first | O(N), shift elements | O(1), update head |
| Search for value | O(N) if unsorted | O(N) |
| Memory layout | Contiguous elements | Separate nodes connected by pointers |
| Dynamic growth | Fixed array cannot resize; vector resizes by reallocating | Allocate individual nodes as needed |
| Extra memory | Array: no pointer per element; vector: possible unused capacity | One next pointer per node, plus allocation overhead |

A linked list can change connections without moving every element, but reaching an arbitrary position still requires following links from `head`. That is why random access is not O(1). A vector is usually better when I need to access items by index.

## P14
1. insertBack becomes significantly faster.
2. It changes from O(N) to **O(1)** because the final node is directly accessible.
3. No. Searching still requires following nodes and is O(N) in the worst case.
4. No. Deleting the last node by value still takes **O(N)** in the worst case.
5. Even with tail, I cannot move backward to find the previous node. I must traverse from head to locate the node before the last one, then update tail and delete the old last node.

## P15

1. prev stores the address of the preceding node.
2. The next and prev pointers let me move forward or backward.
3. A doubly linked list needs an extra pointer per node, increasing memory usage.
4. If I already have a pointer to a node, I can use prev and next to reconnect its neighbors without searching for the predecessor (assuming the list's boundary pointers are handled correctly). That can make deletion O(1).

## P16

1. `while (temp != nullptr)` would never stop in a nonempty circular list because the last node points back to head.
2. I can stop when the traversal returns to head, after visiting each node once; an empty list must be checked separately.
3. Circular lists naturally repeat through the same sequence without restarting from a null end.
4. A round-robin scheduler is one example: after processing the final task, it returns to the first task.

## A&R

Linked lists do not need contiguous memory because each node stores a pointer to the next node. The head pointer is the starting point for accessing the list, so losing it can make every node unreachable. Traversal takes O(N) because I must visit nodes one by one. In my implementation, inserting at the beginning is O(1) because I only connect a new node to the old head and update head. Inserting at the end is O(N) without a tail because I must follow the links to find the last node.

Deletion requires careful pointer changes so the remaining list stays connected. The tests show that removing the first, middle, and last nodes leaves the expected sequence. Allocated nodes also need to be deleted to avoid leaks, which is why I implemented the destructor. Binary search is not efficient on a linked list like it is on an indexed array because I cannot jump directly to the middle node; reaching it already requires traversal.

I would choose a linked list when I need frequent insertions or deletions near the front or at nodes I already have pointers to. I would choose an array or vector when I need fast indexing, less memory overhead, or efficient sequential access. The part I had to pay the most attention to was the order of the pointer changes. If I change the wrong link first, I could lose part of the list.
