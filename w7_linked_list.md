P1
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

P2