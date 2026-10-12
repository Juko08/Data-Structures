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
