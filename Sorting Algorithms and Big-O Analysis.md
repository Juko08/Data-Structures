1.  4N + 16 -> O(N)
Big -O focuses on how the number of operations grows as the input gets larger. Constant multipliers(4) and constant terms(16) are ignored when determining the final Big-O classification(N). 
2. Big-O: O(N^2)
as N increases, the number of operations increases by the square of N.
N= 10 -> 2(10^2) = 200 operations
As the the input gets larger, the number of operations grows much faster. The 2 is a constant and is ignored in Big-O notation, leaving O(N^2)
3. First Loop: N times
   Second Loop: N times
   Total: N+ N = 2N
   Final: O(N)
   The loops are sequential, not nested, so their work is added rather than multiplied
4. Loop executes N times
   Each iteration performs 3 constant-time operations
   Total: 3N
   Final: O(N)
   The 3 is a constant and is ignored
5. Outer Loop: N times
   index.even? is true about N/2 times.
   Inner Loop: N times each time it is reached
   Total: (N/2) * N = N^2 / 2
   Final: O(N^2)
   Processing only half of elements doesn't change the Big-O because 1/2 is a constant
Aanalysis/Reflection
Constants are ignored because they don't change the overall growth rate.
O(N) grows linearly with the input size
O(N^2) grows much faster because the input size is squared
Sequential loops has their work added like N+N += 2N -> O(N)
Nested loops: has work multiplied  N*N = N^2 -> O(N^2)
As datasets become larger, inefficient algorithms can require significantly more operations and take much longer to run 
