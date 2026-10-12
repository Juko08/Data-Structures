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

